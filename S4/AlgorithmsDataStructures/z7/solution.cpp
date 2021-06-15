#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
#define MAXN 1000006

int a,b,c,n,m,ans=MAXN;
int net = 1;
int tab[MAXN][2];
vector < pair <int, pair <int, int > > > input;

int findd(int i)
{
    if(tab[i][0]!=i) tab[i][0] = findd(tab[i][0]);
    return tab[i][0];
}

void unionn(int a, int b)
{
    int x=findd(a);
    int y=findd(b);
    if(x!=y)
    {
        if(tab[x][1]>tab[y][1])
        {
            tab[y][0]=x;
            tab[x][1]=tab[y][1]+tab[x][1];
            net = max(net, tab[x][1]);
        }
        else
        {
            tab[x][0]=y;
            tab[y][1]=tab[y][1]+tab[x][1];
            net = max(net, tab[y][1]);
        }
    }
}

int main() {
    scanf("%d %d",&n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d",&a, &b, &c);
        input.pb(mp(-c,mp(a,b)));
    }
    sort(input.begin(),input.end());

    for(int i=1; i<=n; i++)
    {
        tab[i][0]=i;
        tab[i][1]=1;
    }

    for (int i = 0; i < m; i++)
    {
        a = input[i].second.first;
        b = input[i].second.second;
        if(findd(a)!=findd(b))
        {
            unionn(a,b);
            ans = -input[i].first;
        }

        if (net==n) break;
    }

    printf("%d",ans);

    return 0;
}
