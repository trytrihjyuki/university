#include <bits/stdc++.h>
using namespace std;
int next_perm(int x) {
    return (x + 1) % (1 << 2);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,p,m;
    cin >> n >> p >> m;
    unordered_map <int, int> pattern; // forbidden patterns
    for (int i = 0; i < p; i++) {
        int x = 0;
        for (int j = 0; j < 3; j++) {
            string tmp;
            cin >> tmp;
            for (int z = 0; z < 3; z ++) {
                if (tmp[z] == 'x')
                    x ^= 1<<(8 - (j * 3) - z);
            }
        }
        pattern[x] = 1;
    }
    unordered_map <int, int > board; // all DISTINCT "good" coloring of board 3x5
    int x = 0, ans = 0;
    do {
        int y = 0;
        do {
            int z = 0;
            do {
                int w = 0;
                do {
                    int v = 0;
                    do {
                        board[((x << 1) << 12) + ((y << 1) << 9) + ((z << 1) << 6) + ((w << 1) << 3) + (v << 1)] += 1;
                        v = next_perm(v);
                    } while (v != 0);
                    w = next_perm(w);
                } while (w != 0);
                z = next_perm(z);
            } while (z != 0);
            y = next_perm(y);
        } while (y != 0);
        x = next_perm(x);
    } while (x != 0);


    unordered_map <int, vector<int> > generated;
    for (auto it = board.begin(); it != board.end(); it++) {
        for(int q = 0; q < 2; q++) {
            for(int w = 0; w < 2; w++) {
                for(int e = 0; e < 2; e++) {
                    for(int r = 0; r < 2; r++) {
                        for(int t = 0; t < 2; t++) {
                            int new_coloring = it->first + (q << 12) + (w << 9) + (e << 6) + (r << 3) + (t);
                            bool is_good = 1;
                            for (auto jt = pattern.begin(); jt != pattern.end(); jt++) {
                                if (jt->first == new_coloring / (2 << 5) ||
                                    jt->first == (new_coloring / (2 << 2)) % (2 << 8) || 
                                    jt->first == new_coloring % (2 << 8)) {
                                        is_good = 0;
                                        break;
                                    }
                            }
                            if (is_good) {
                                int gen_coloring = 0;
                                for (int i = 1; i <= 15; i ++) {
                                    if (i % 3 != 0) {
                                        gen_coloring += ((new_coloring % 2) << i);
                                    }
                                    new_coloring /= 2;
                                }
                                generated[it->first].push_back(gen_coloring);
                            }
                        }
                    }
                }
            }
        }
    }
    for (int _ = 2; _ < n; _ ++) {
        ans = 0;
        unordered_map <int , int> new_board;
        for (auto it = board.begin(); it != board.end(); it++) {
            vector<int> gd = generated[it->first]; 
            int g = gd.size();
            for (int i = 0; i < gd.size(); i++) {
                new_board[gd[i]] += (it->second)%m;
            }
            ans = (ans + ((g * it->second) % m)) % m;
        }
        board = new_board;
    }

    cout << ans << "\n";
    return 0;
}