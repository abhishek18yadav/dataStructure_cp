// SEGMENT TREE LAZY PRPAGATION
#include<bits/stdc++.h>
using namespace std;

vector<int>seg;
vector<int>lzy;
// building segment tree
void build(int idx,int low, int high,vector<int>&arr){
    if(low==high){
        seg[idx]= arr[low];
        return ;
    }
    int mid=(low+high)/2;
    build(2*idx+1,low,mid,arr);
    build(2*idx+2,mid+1,high,arr);
    seg[idx]= seg[2*idx+1]+ seg[2*idx+2];
}
void update(int idx, int low,int high, int l, int r, vector<int>&arr, int val){
    //update the previous update and and ask child to update itself whensoever
    if(lzy[idx]!=0){
        seg[idx]+=(high-low +1)*lzy[idx];
        if(low!=high){
            lzy[2*idx+1]+=val;
            lzy[2*idx+2]+=val;
        }
        lzy[idx]=0;
    }
    //non overlapping
    if(high<l or low>r)return;
    //full overlapping
    else if(low>=l and high<=r){
        seg[idx]+=(high-low +1)*val;
        if(low!=high){
            lzy[2*idx+1]+=val;
            lzy[2*idx+2]+=val;
        }
        return;
    }
    //partial overlapping
    else{
        int mid = (low+high)/2;
        update(2*idx+1,low,mid,l,r,arr,val);
        update(2*idx+2,mid+1,high,l,r,arr,val);
        seg[idx]= seg[2*idx+1]+ seg[2*idx+2];
    }
}
int query(int idx, int low, int high,int l, int r){
    //update if any updates are remaining
    if(lzy[idx]!=0){
        seg[idx]+=lzy[idx]*(high-low+1);
        if(low!=high){
            lzy[2*idx+1]=lzy[idx];
            lzy[2*idx+2]=lzy[idx];
        }
    }
    // if no overlapping of query(l,r) over array range [low,high];
    if(high<l or low>r)return 0;

    // if full overlapping
    else if(low>=l and high<= r){
        return seg[idx];
    }
    // partial overlapping
    else{
        int mid = (low+high)/2;
        int left=query(2*idx+1,low,mid,l,r);
        int right = query(2*idx+2,mid+1,high,l,r);
        return left + right;
    }
}
int main(){
    int n=4;
    seg.resize(4*n,-1);
    lzy.resize(4*n,0);
    vector<int>arr{1,2,3,4};
    build(0,0,n-1,arr);
    //yaha se replace 
    update(0,0,n-1,0,1,arr,1);

    cout<<query(0,0,n-1,0,3);
    /**
     * int q;
     * cin>>q;
     * while(q--){
     *    int type;
     *    cin>>type;
     *    if(type==1){
     *      int l,r;
     *      cin>>l>>r;
     *      cout<<query(0,0,n-1,l,r);
     *    }
     *   else{
     *      int l,r,val;
     *      cin>>l,r,val;
     *      update(0,0,n-1,r,val);
     *   }
     * }
    */
    
    return 0;
}
