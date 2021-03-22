#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxm = int(1e6) + 10;
const ll k = 25;

struct sznurek{
    ll val;
    ll quantity;
};

vector < sznurek> sznurki;
int ans = 0;

bool compare(sznurek s1, sznurek s2)
{
    return s1.val < s2.val;
}

void procesuj(sznurek s, int i)
{

        bool flag = false;
        // szukamy elementu zeby dodac
    while (s.quantity)
    {
        int l = i+1;
        int r = sznurki.sz - 1;
        while (l <= r)
        {
            int mid = l + (r-l)/2;
            if (sznurki[r].val < s.val*2)
            {
                // cout << "BREAK!\n";
                break;
            }
            // cout << sznurki[l].val << " zakres " << sznurki[r].val<<endl;
            // cout << sznurki[mid].val << "  --  "<< s.val*2<<'\n';
            if (sznurki[mid].val == s.val*2)
            {
                // cout << "ZNALEZIONY!\n";
                if (s.quantity%2 == 1) ans++;
                s.val*=2;
                sznurki[mid].quantity += s.quantity/2;
                s.quantity=0;
                flag = true;
                break;
            }
            else
            {
                if (sznurki[mid].val < s.val*2)
                    l = mid + 1;
                if (sznurki[mid].val > s.val*2)
                    r = mid - 1;
            }
        }
        // cout << "po dodaniu do kogoś:\nans=" << ans << "\ns.val=" << s.val <<"\ns.quantity="<<s.quantity<<endl<<endl;
        if (!flag)
        {
            if (s.quantity%2 == 1) ans++;
            s.quantity/=2;
            s.val*=2;
        }
        // cout << "samo polaczeniu:\nans=" << ans << "\ns.val=" << s.val <<"\ns.quantity="<<s.quantity<<endl<<endl;
    }


}
int main() {

    ll m,n,d;
    scanf("%lld",&m);

    for (int i = 0; i < m; ++i)
    {
        scanf("%lld%lld",&d,&n);
        sznurek s;
        s.val = d;
        s.quantity = n;
        sznurki.pb(s);
    }

    sort(sznurki.begin(), sznurki.end(), compare);

    for (int i = 0; i < sznurki.sz; i++)
    {
        procesuj(sznurki[i],i);
        // cout << i << ", ans:"<<ans<<endl;
    }
    
    printf("%d", ans);

    return 0;
}