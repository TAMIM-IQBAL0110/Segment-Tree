#include<bits/stdc++.h>
using namespace std;
int marge(int x,int y){
    return min(x,y);
}
class segTree{
    vector<int>seg;
    public:
    segTree(int n){
        seg.resize(4*n+1);
    }
    void buildseg(int ind,int low,int high ,vector<int>&a){//0 base indexing
        if(low==high){
            seg[ind]=a[low];
            return;
        }
        int mid=(high+low)/2;
        buildseg(2*ind+1,low,mid,a);
        buildseg(2*ind+2,mid+1,high,a);
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
};
void solve(){
    int n; cin>>n;
    segTree x(n);
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    x.buildseg(0,0,n-1,a);
    vector<int>b(n);
    int n2; cin>>n2; 
    for(int i=0;i<n2;i++) cin>>b[i];
    segTree y(n2);
    y.buildseg(0,0,n2-1,b);
    int q; cin>>q;
    while(q--){
        int type; cin>>type;
        if(type==1){
            int l1,r1,l2,r2; cin>>l1>>r1>>l2>>r2;
            int min1=x.query(0,0,n-1,l1,r1);
            int min2=y.query(0,0,n2-1,l2,r2);
            cout<<min(min1,min2)<<endl;
        }
        else {
            int setype,i,val; cin>>setype>>i>>val;
            if(setype==1){
                x.update(0,0,n-1,i,val);
                a[i]=val;
            }
            else {
                y.update(0,0,n2-1,i,val);
                b[i]=val;
            }
        }
    }
}

int main(){

}