#include<bits/stdc++.h>
using namespace std;

vector<int>seg;
vector<int>lazy;
void build(int idx , int low , int high , vector<int>&arr){
    if(low==high){
        seg[idx]=arr[low];
        return;
    }
    int mid = (low+high)/2;
    build(2*idx+1 , low , mid,arr);
    build(2*idx+2 , mid+1 , high , arr);
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}
void case1(int idx,int aridx,int low , int high, vector<int>&arr){
    if(low==aridx){
        cout<<"robin given all money of amount"<<seg[idx]<<endl;
        seg[idx]=0;
        return;
    }
    int mid = (low+high)/2;
    if(aridx<=mid)case1(2*idx+1,aridx,low,mid,arr);
    if(aridx>mid){
        case1(2*idx+2,aridx,mid+1,high,arr);
    }
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}
void case2(int idx,int aridx,int low , int high, vector<int>&arr, int money){
    if(low==aridx){
        seg[idx]+=money;
        return;
    }
    int mid = (low+high)/2;
    if(aridx<=mid)case2(2*idx+1,aridx,low,mid,arr,money);
    if(aridx>mid){
        case2(2*idx+2,aridx,mid+1,high,arr,money);
    }
    seg[idx]=seg[2*idx+1]+seg[2*idx+2];
}
int case3(int idx,int l,int r, int low, int high , vector<int>&arr){
    if(low>r or high <l )return INT_MIN;
    if(low>= l and high<= r)return seg[idx];
        int mid = (low+high)/2;
        int left = case3(2*idx+1 , l,r,low,mid,arr);
        int right = case3(2*idx+1 , l,r,low,mid,arr);
        return left+right;
}

int main(){
    vector<int>arr{3,2,1,4,5};
    int n =arr.size();
    seg.resize(4*n,-1);
    lazy.resize(4*n,0);
    build(0,0,n,arr);
    case1(0,2,0,n,arr);
    case2(0,3,0,n,arr,4);
    cout<<"total money in this range is"<<case3(0,0,4,0,n,arr);
    return 0;
}