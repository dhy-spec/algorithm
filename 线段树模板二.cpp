#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+9;
//const int p=571373;

ll a[N],n,t[N<<2],add[N<<2],mul[N<<2],p;

void update(int s,int e,int o,ll k,ll x){
    add[o]=(add[o]*k%p+x)%p;
    mul[o]=mul[o]*k%p;
    t[o]=(t[o]*k%p+x*(e-s+1)%p)%p;
}

void pushup(int o){
    t[o]=(t[o<<1]+t[o<<1|1])%p;
}

void pushdown(int s,int e,int o){
    int mid=(s+e)>>1;
    update(s,mid,o<<1,mul[o],add[o]);
    update(mid+1,e,o<<1|1,mul[o],add[o]);
    add[o]=0,mul[o]=1;
}

void build(int s=1,int e=n,int o=1){
    add[o]=0,mul[o]=1;
    if(s==e) return t[o]=a[s],void();
    int mid=(s+e)>>1;
    build(s,mid,o<<1);
    build(mid+1,e,o<<1|1);
    pushup(o);
}

void modify(int l,int r,ll k,ll x,int s=1,int e=n,int o=1){
    if(l<=s&&e<=r) return update(s,e,o,k,x),void();
    int mid=(s+e)>>1;
    pushdown(s,e,o);
    if(mid>=l) modify(l,r,k,x,s,mid,o<<1);
    if(mid+1<=r) modify(l,r,k,x,mid+1,e,o<<1|1);
    pushup(o);
}

ll query(int l,int r,int s=1,int e=n,int o=1){
    if(l<=s&&e<=r) return t[o];
    int mid=(s+e)>>1;
    pushdown(s,e,o);
    ll res=0;
    if(mid>=l) res=(res+query(l,r,s,mid,o<<1))%p;
    if(mid+1<=r) res=(res+query(l,r,mid+1,e,o<<1|1))%p;
    return res;
}

int main(){
    int m;
    cin>>n>>m>>p;
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
            modify(l,r,x,0);
        }else if(op==2){
            cin>>l>>r>>x;
            modify(l,r,1,x);
        }else{
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<endl;
        }
    }
    return 0;
}