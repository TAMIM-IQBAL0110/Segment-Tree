#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
vector<int>a(N);
vector<int>seg(N*4+1);
int marge(int x,int y){
    return min(x,y);
}
void buildseg(int ind,int low,int high){//0 base indexing
    if(low==high){
        seg[ind]=a[low];
        return;
    }
    int mid=(high+low)/2;
    buildseg(2*ind+1,low,mid);
    buildseg(2*ind+2,mid+1,high);
    seg[ind]=marge(seg[2*ind+1],seg[2*ind+2]);
}
int query(int ind,int low,int high,int l,int r){
    if(high<l || r<low){ // completely outside
        return INT_MAX;// for finding min
        // return INT_MIN // for finding max
    }
    if(low>=l && high<=r) return seg[ind]; // completely inside
    else { // partial overlap
        int mid=(high+low)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2,mid+1,high,l,r);
        return marge(left,right);
    }
}
void update(int ind,int low,int high,int i,int val){
    if(high==low) {
        seg[ind]=val;
        return;
    }
    int mid=(low+high)/2;
    if(i<=mid) update(2*ind+1,low,mid,i,val);
    else update(2*ind+2,mid+1,high,i,val);
    seg[ind]=marge(seg[ind*2+1],seg[ind*2+2]);
}
int main(){

}