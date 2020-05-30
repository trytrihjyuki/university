#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1005;
const ll k = 25;
int n,t,c;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int max_msg_to_send = 0;
    int msg_to_send = 0;
    int cur_t = 0;
    for (int i = 0; i < n; i++)
    {
        cin>>t>>c;
        // sending old msg
        msg_to_send = max(0, msg_to_send - ( t-cur_t ) );
        // getting new msg
        msg_to_send += c;
        max_msg_to_send = max(max_msg_to_send, msg_to_send);
        cur_t = t;
    }
    cout<<cur_t+msg_to_send<<" "<<max_msg_to_send;
    return 0;
}