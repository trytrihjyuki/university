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

bool compare(sznurek s1, sznurek s2)
{
    return s1.val > s2.val;
}

vector < sznurek> sznurki;
// int heap = [maxm];
int ans = 0;
class max_heap
{
public:
    int size;
    sznurek *elements;

    max_heap()
    {
        size = 1;
        elements = new sznurek[maxm];
    }

    void down(int index)
    {
        int left = 2*index;
        int right = 2*index + 1;

        int curr_idx = index;

        if (left < size and elements[left].val < elements[curr_idx].val) curr_idx = left;
        if (right < size and elements[right].val < elements[curr_idx].val) curr_idx = right;

        if (curr_idx != index)
        {
            swap(elements[index], elements[curr_idx]);
            down(curr_idx);
        }
    }

    void add_element(sznurek s)
    {
        int idx = size++;
        elements[idx] = s;

        while (idx > 1 and elements[idx].val < elements[idx/2].val)
        {
            swap(elements[idx],elements[idx/2]);
            idx/=2;
        }
    }

    sznurek get_min()
    {
        return elements[1];
    }

    void pop()
    {
        int left = 2;
        int right = 3;

        if (left < size and elements[left].val == elements[1].val)
        {
            elements[1].quantity += elements[left].quantity;
            size--;
            elements[left] = elements[size];
            down(left);
        }
        if (right < size and elements[right].val == elements[1].val)
        {
            elements[1].quantity += elements[right].quantity;
            size--;
            elements[right] = elements[size];
            down(right);
        }
        if(elements[1].quantity % 2 == 1) ans++;
        sznurek s;
        s.val = elements[1].val * 2;
        s.quantity = elements[1].quantity / 2;

        if(s.quantity)
        {
            elements[1] = s;
            down(1);
        }
        else
        {
            elements[1] = elements[size-1];
            size--;
            down(1);
        }
    }

    bool empty()
    {
        return size == 1;
    }
};
int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

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

    // sort(sznurki.begin(), sznurki.end(), compare);

    max_heap kopiec;

    for (auto s: sznurki)   kopiec.add_element(s);

    while(!kopiec.empty())
    {
        kopiec.pop();
    }

    printf("%d",ans);
    return 0;
}