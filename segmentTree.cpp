#include<bits/stdc++.h>
using namespace std;

// building segment tree
void build(int idx , int low , int high , vector<int>&arr,vector<int>&seg){
    if(low==high){
        seg[idx]=arr[low];
        return;
    }
    int mid = (low+high)/2;
    build(2*idx+1 , low , mid,arr,seg);
    build(2*idx+2 , mid+1 , high , arr,seg);
    seg[idx]=min(seg[2*idx+1],seg[2*idx+2]);
}
// query is in form of (l,r);
int query(int l , int r , int low , int high , int idx,vector<int>&seg){
    // query's range is out of range
    if(l>high or r<low){
        return INT_MAX;
    }
    //if whole portion lie in query's range  i.e fully overlapping
    // the portion of array lie in , (l,r)
    else if(low>=l and  high<=r){
        return seg[idx];
    }
    else{
        int mid =   (low+high)/2;
        int left =  query(l,r,low,mid,2*idx+1,seg);
        int right = query(l,r,mid+1,high,2*idx+2,seg);
        return min(left,right);
    }
    return 0;
}
int main(){
    vector<int>arr{1,3,2,0,4,5};
    vector<int>seg(4*arr.size(),-1);
    build(0,0,arr.size()-1,arr,seg);
    int l,r;
    cin>>l>>r;
    cout<<query(l,r,0,arr.size()-1,0,seg);
    return 0;
}