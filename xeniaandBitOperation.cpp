#include<bits/stdc++.h>
using namespace std;

int power(int size){
    if(size==2)return 1;
    return 1+power(size/2);
}
// building segment tree
void build(int idx , int low, int high , vector<int>&arr , vector<int>&seg, int count){
    if(low == high){
        seg[idx]=arr[low];
        return ;
    }
    int mid = (low+high)/2;
    build(2*idx+1,low,mid,arr,seg,!count);
    build(2*idx+2,mid+1,high,arr,seg,!count);
    seg[idx] = (count%2==0)?(seg[2*idx+1] ^ seg[2*idx+2]): (seg[2*idx+1] | seg[2*idx+2]) ;
}
int main(){
    vector<int>arr{1,6,3,5};
    vector<int>seg(4*arr.size());

    if(power(arr.size())%2==0){
    build(0,0,arr.size()-1,arr,seg,0);
    }
    else build(0,0,arr.size()-1,arr,seg,1);
    cout<<"value of v in while array is"<<seg[0];
    return 0;
}