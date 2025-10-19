#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+9;

ll a[N],n,t[N<<2],add[N<<2];

void update(int s,int e,int o,ll x){
    add[o]+=x;
    t[o]+=x*(e-s+1);
}

void pushup(int o){
    t[o]=t[o<<1]+t[o<<1|1];
}

void pushdown(int s,int e,int o){
    int mid=(s+e)>>1;
    update(s,mid,o<<1,add[o]);
    update(mid+1,e,o<<1|1,add[o]);
    add[o]=0;
}

void build(int s=1,int e=n,int o=1){
    add[o]=0;
    if(s==e) return t[o]=a[s],void();
    int mid=(s+e)>>1;
    build(s,mid,o<<1);
    build(mid+1,e,o<<1|1);
    pushup(o);
}

void modify(int l,int r,ll x,int s=1,int e=n,int o=1){
    if(l<=s&&e<=r) return update(s,e,o,x),void();
    int mid=(s+e)>>1;
    pushdown(s,e,o);
    if(mid>=l) modify(l,r,x,s,mid,o<<1);
    if(mid+1<=r) modify(l,r,x,mid+1,e,o<<1|1);
    pushup(o);
}

ll query(int l,int r,int s=1,int e=n,int o=1){
    if(l<=s&&e<=r) return t[o];
    int mid=(s+e)>>1;
    pushdown(s,e,o);
    ll res=0;
    if(mid>=l) res+=query(l,r,s,mid,o<<1);
    if(mid+1<=r) res+=query(l,r,mid+1,e,o<<1|1);
    return res;
}

int main(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build();
    while(m--){
        int op;
        cin>>op;
        ll l,r,x;
        if(op==1){
            cin>>l>>r>>x;
            modify(l,r,x);
        }else{
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}