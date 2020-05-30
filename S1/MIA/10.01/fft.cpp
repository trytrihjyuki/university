#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const bool debug = 0;
const ld PI  = 3.141592653589793238463;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair

int T,n,a,b,pot2;

void wypisz( vector <complex <ld> > v){
    cout<<"\n\n";
    for(auto c:v) cout<<c<<" ";
    cout<<"\n\n";
}

vector < complex<ld> > DFT(vector < complex<ld> > current){
    int n = current.sz;
    vector < complex<ld> > ans(n);

    if(n == 1){
        ans.resize(0);
        ans.pb(current[0]);
        return ans;
    }

    //divide
    vector < complex<ld> > even;
    vector < complex<ld> > odd;
    for(int i=0; i<n; i+=2) even.pb(current[i]);
    for(int i=1; i<n; i+=2) odd.pb(current[i]);

    vector <complex<ld>> odd_DFT = DFT(odd);
    vector <complex<ld>> even_DFT = DFT(even);

    //conquer
    complex <ld> w(1,0),wn(cos(2.0*PI/n),sin(2.0*PI/n));
    for(int i=0;i<n/2;i++){
        ans[i]=even_DFT[i]+w*odd_DFT[i];
        ans[i+n/2]=even_DFT[i]-w*odd_DFT[i];
        w*=wn;
    }
     return ans;
}

vector < complex<ld> > reverse_DFT(vector < complex<ld> > current){
    int n = current.sz;
    vector < complex<ld> > ans(n);

    if(n == 1){
        return current;
    }

    //divide
    vector < complex<ld> > even;
    vector < complex<ld> > odd;
    for(int i=0; i<n; i+=2) even.pb(current[i]);
    for(int i=1; i<n; i+=2) odd.pb(current[i]);

    vector <complex<ld>> odd_DFT = reverse_DFT(odd);
    vector <complex<ld>> even_DFT = reverse_DFT(even);

    //conquer
    complex <ld> w(1,0),wn(cos(2.0*PI/n),sin(-2.0*PI/n));
    for(int i=0;i<n/2;i++){
        ans[i]=even_DFT[i]+w*odd_DFT[i];
        ans[i+n/2]=even_DFT[i]-w*odd_DFT[i];
        w*=wn;
    }
     return ans;
}

void FFT(vector < complex<ld> > p_A,vector < complex<ld> > p_B){
    //liczenie DFT obu vector
    vector < complex<ld> > DFT_A, DFT_B, DFT_C,answer;
    DFT_B.resize(0); DFT_A.resize(0); DFT_C.resize(0);
    DFT_A = DFT(p_A);
    DFT_B = DFT(p_B);

    for(int i=0; i<DFT_A.sz; i++)
        DFT_C.pb(DFT_A[i] * DFT_B[i]);
    answer = reverse_DFT(DFT_C);
    for(int i=0; i<2*n-1; i++) cout<<(round(real(answer[i]))/(pot2))<<" ";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        vector < complex<ld> > A;
        vector < complex<ld> > B;
        n++;
        A.resize(n); B.resize(n);
        for(int i=0; i<n; i++){
            cin>>A[i];
        }
        for(int i=0; i<n; i++){
            cin>>B[i];
        }
        //dopelniam zerami do potegi dwójki
        int tmp=1;
        while(tmp<=n) tmp<<=1;
        for(int i=n;i<tmp;i++){
            A.pb(0);
            B.pb(0);
        }
        tmp<<=1;
        for(int i=tmp>>1;i<tmp;i++){
            A.pb(0);
            B.pb(0);
        }
        pot2 = tmp;
        FFT(A,B);
        cout<<"\n";
    }
    return 0;
}