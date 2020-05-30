#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
const bool debug3 = 0;
const bool debug4 = 0;
const bool debug5 = 0;
const bool debug6 = 1;
const bool debug7 = 1;
bool debug2 = 0;
#define deb if(debug)
#define deb2 if(false)
#define deb3 if(debug3)
#define deb4 if(debug4)
#define deb5 if(debug5)
#define deb6 if(debug6)
#define deb7 if(debug7)
#define pb push_back
#define sz size()
#define mp make_pair
#define point pair <int, int>
#define x first
#define y second
#define TORPEDO 0
#define SONAR 1
#define SILENCE 2
#define MINE 3
const ll maxn = 15;
int width,height,ID;

bool board[maxn][maxn];
int visited[maxn][maxn];

bool mines[maxn][maxn];

vector <point> minesV;
vector <point> nonIsland;

int cooldowns[4];
int charges[4];

string dict[4];

int enemyCooldowns[4];
int enemyCharges[4];

point pos;

int myLife,oppLife;
int oppLifeDiff = 6;

int lastSonar = -1;
point lastMine = mp(-1,-1);

int news = 0;

bool trigger;

vector <point> myDMG;
vector <point> oppDMG;

vector <point> lastExplosions;
string opponentOrders;

vector <point> enemyPos;
int enemyProp[maxn][maxn];

set < set <point> > possiblePaths[maxn][maxn]; // do sprawdzania

point movePos(point p,char move)
{
    switch(move)
    {
        case 'N':
            return {p.x,p.y-1};
        case 'S':
            return {p.x,p.y+1};
        case 'W':
            return {p.x-1,p.y};
        case 'E':
            return {p.x+1,p.y};
    }
}

bool isIsland(point p)
{
    return board[p.y][p.x];
}
bool isValid(point p)
{
    if (isIsland(p))
        return false;
    if ((p.y < 15) && (p.y >= 0) && (p.x < 15) && (p.x >= 0))
        return true;
    return false;
}
bool isVisited(point p)
{
    return visited[p.y][p.x];
}
int getSector(point p)
{
    return (p.x/5 + 1 + (p.y/5) * 3);
}
vector <point> getValidNeighbours(point p, int range)
{
    vector <point> neighbours;
    for (int dx = -range; dx <= range; dx++){
        for (int dy = -(range-abs(dx)); dy <= (range-abs(dx)); dy++)
        {
            if (isValid(mp(p.x + dx, p.y + dy)))
                    neighbours.pb(mp(p.x + dx, p.y + dy));
        }
    }
    return neighbours;
}

bool isInRange(point p, point fired)
{
    bool boardTMP[height][width];
    queue < pair < point, int > > kolejka;
    for (int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
            boardTMP[y][x] = bool(board[y][x]);
    kolejka.push(mp(p,0));
    while (!kolejka.empty())
    {
        pair <point,int> t = kolejka.front();
        point vb = t.first;
        if (vb == fired)
            return true;
        int score = t.second;
        kolejka.pop();
        if (score <= 4)
        {
            boardTMP[vb.y][vb.x] = 1;
            for (auto u: getValidNeighbours(vb, 1))
            {
                if (!boardTMP[u.y][u.x]){
                    boardTMP[u.y][u.x] = 1;
                    kolejka.push(mp(u,score+1));
                }
            }
        }
    }
    return false;
}

int diffrentEnemySectors()
{
    bool sectors[10];
    for (int i = 0; i < 10; i++) sectors[i] = 0;
    for (auto s: enemyPos)
        sectors[getSector(s)] = 1;
    int tmp = 0;
    for (int i = 0; i < 10; i++) tmp+=sectors[i];
    return tmp;
}
int scorePosition(point p)
{
    if (!isValid(p) and !isVisited(p))
        return 0;
    bool boardTMP[height][width];
    queue <point> kolejka;
    for (int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
            boardTMP[y][x] = bool(visited[y][x] or board[y][x]);
    int score = 0;
    kolejka.push(p);
    while (!kolejka.empty())
    {
        point vb = kolejka.front();
        kolejka.pop();
        if (p != vb)
            score++;
        boardTMP[vb.y][vb.x] = 1;
        for (auto u: getValidNeighbours(vb, 1))
        {
            if (!boardTMP[u.y][u.x]){
                boardTMP[u.y][u.x] = 1;
                kolejka.push(u);
            }
        }
    }
    return score;
}
int manhattan(point p1, point p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
void clearPropBoard()
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            enemyProp[j][i] = 0;
}
void printBoard()
{
    // cerr<<"\nBOARD:\n";
    // for (int i = 0; i < height; i++)
    // {
    //     for(int j = 0; j < width; j++)
    //         cerr<<board[i][j]<<" ";
    //     cerr<<"\n";
    // }
    // cerr<<"\nVISITED:\n";
    // for (int i = 0; i < height; i++)
    // {
    //     for(int j = 0; j < width; j++)
    //         cerr<<visited[i][j]<<" ";
    //     cerr<<"\n";
    // }
    cerr<<"\nENEMY POS SIZE: "<<enemyPos.sz;
    cerr<<"\nENEMY PROP\n";
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            cerr<<enemyProp[i][j]<<" ";
        cerr<<"\n";
    }
    cerr<<"\nPATH LENG:\n";
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            cerr<<possiblePaths[i][j].sz<<" ";
        cerr<<"\n";
    }
    cerr<<"\n";
    // cerr<<"\nMINES\n";
    // for (int i = 0; i < height; i++)
    // {
    //     for(int j = 0; j < width; j++)
    //         cerr<<mines[i][j]<<" ";
    //     cerr<<"\n";
    // }
    // cerr<<"\n";
}


//BIERZE MANHATANA A NIE ROCKET ODLEGLOS
void updateEnemyTorpedo(point firedPos)
{
    deb cerr<<"Updating enemy: TORPEDO\n";;
    vector <point> newEnemyPos;
    for (auto p: enemyPos)
    {
        enemyProp[p.y][p.x] = 0;
        if(isInRange(p,firedPos))
        {
            newEnemyPos.pb(p);
            enemyProp[p.y][p.x] = 2;
        }
        else
        {
            possiblePaths[p.y][p.x].clear();
            enemyProp[p.y][p.x] = 0;
        }
    }
    enemyPos = newEnemyPos;
}
void updateEnemySector(int sector)
{
    deb6 cerr<<"Updating enemy: SURFACE\n";
    vector <point> newEnemyPos;
    deb6 cerr<<enemyPos.sz<<"\n";
    for (auto p: enemyPos)
    {
        enemyProp[p.y][p.x] = 0;
        if(getSector(p) == sector)
        {
            newEnemyPos.pb(p);
            enemyProp[p.y][p.x] = 2;
        }
        else
        {
            possiblePaths[p.y][p.x].clear();
            enemyProp[p.y][p.x] = 0;
        }
    }
    enemyPos = newEnemyPos;
    deb6 cerr<<enemyPos.sz<<"\n";
}
void updateEnemySectorWithNeighbours(int sector)
{
    vector <point> newEnemyPos;
    clearPropBoard();
    for (auto p: enemyPos)
    {
        bool flag = 0;
        if(getSector(p) == sector)
        {
            for (auto p2: getValidNeighbours(p,1))
            {
                if (enemyProp[p2.y][p2.x] == 0)
                {
                    newEnemyPos.pb(p2);
                    flag = 1;
                    enemyProp[p2.y][p2.x] = 2;
                }
                else
                {
                    possiblePaths[p2.y][p2.x].clear();
                    enemyProp[p.y][p.x] = 0;
                }
            }
        }
    }
    enemyPos = newEnemyPos;
    sort( enemyPos.begin(), enemyPos.end() );
    enemyPos.erase( unique( enemyPos.begin(), enemyPos.end() ), enemyPos.end() );
}

void updateEnemyMove(char direction)
{
    vector <point> newEnemyPos;
    set < set <point> >oldPossiblePaths[maxn][maxn];

    int sum = 0;
    int krotka = 0;
    for (auto p: enemyPos)
    {
        oldPossiblePaths[p.y][p.x] = possiblePaths[p.y][p.x];
        for (auto gowno: possiblePaths[p.y][p.x])
        {
            sum+=gowno.sz;
            krotka = max(krotka, int(gowno.sz));
        }
        possiblePaths[p.y][p.x].clear();
    }

    for (auto p: enemyPos)
    {
        if (sum <= 36000)
            break;
        int tmpik  = 0;
            for (auto gowno: oldPossiblePaths[p.y][p.x])
                tmpik+=gowno.sz;
        sum -= tmpik;
        oldPossiblePaths[p.y][p.x].clear();
        set <point> dupa;
        dupa.insert(p);
        oldPossiblePaths[p.y][p.x].insert(dupa);
    }

    deb6 cerr<<enemyPos.sz;
    deb7 cerr<<"\nUpdating move.\nSum: "<<sum<<" "<<krotka<<"\n";

    clearPropBoard();
    for (auto p: enemyPos)
    {
        point newPos = movePos(p, direction);
        if (isValid(newPos))
        {
            bool flag3 = 0;
            for (auto pathToP: oldPossiblePaths[p.y][p.x])
            {
                auto it = pathToP.find(newPos);
                if (it == pathToP.end())
                {
                    flag3 = 1;
                    set <point> tmp = pathToP;
                    tmp.insert(newPos);
                    possiblePaths[newPos.y][newPos.x].insert(tmp);
                }
            }
            if (flag3)
            {
                newEnemyPos.pb(newPos);
                enemyProp[newPos.y][newPos.x] = 2;
            }
        }
    }

    enemyPos = newEnemyPos;
    deb6 cerr<<enemyPos.sz;
    deb6 cerr<<"\nUpdated move.\n";
}

void updateEnemySilence()
{
    vector <point> newEnemyPos;
    set < set <point> > oldPossiblePaths[maxn][maxn];


    int sum = 0;
    int krotka = 0;
    for (auto p: enemyPos)
    {
        oldPossiblePaths[p.y][p.x] = possiblePaths[p.y][p.x];
        for (auto gowno: possiblePaths[p.y][p.x])
        {
            sum+=gowno.sz;
            krotka = max(krotka, int(gowno.sz));
        }
    }

    for (auto p: enemyPos)
    {
        if (sum <= 8000)
            break;
        int tmpik  = 0;
            for (auto gowno: oldPossiblePaths[p.y][p.x])
                tmpik+=gowno.sz;
        sum -= tmpik;
        oldPossiblePaths[p.y][p.x].clear();
        set <point> dupa;
        dupa.insert(p);
        oldPossiblePaths[p.y][p.x].insert(dupa);
    }

    clearPropBoard();

    deb6 cerr<<enemyPos.sz<<"\n";
    deb7 cerr<<"Updating enemy silence.\nSum: "<<sum<<" "<<krotka<<"\n";
    for (auto p: enemyPos)
    {
        newEnemyPos.pb(p); // can go with zero
        enemyProp[p.y][p.x] = 2;

        for (int i = 1; i <= 4; i++)
        {
            point newPos = (mp(p.x,p.y + i));
            if (isValid(newPos))
            {
                bool flag3 = 0;
                for (auto pathToP: oldPossiblePaths[p.y][p.x])
                {
                    auto it = pathToP.find(newPos);
                    if (it == pathToP.end())
                    {
                        flag3 = 1;
                        set <point> tmp = pathToP;
                        tmp.insert(newPos);
                        possiblePaths[newPos.y][newPos.x].insert(tmp);
                    }
                }
                if (flag3)
                {
                    newEnemyPos.pb(newPos);
                    enemyProp[newPos.y][newPos.x] = 2;
                }
                else
                    break;
            }
            else
                break;
        }
        for (int i = 1; i <= 4; i++)
        {
            point newPos = (mp(p.x,p.y - i));
            if (isValid(newPos))
            {
                bool flag3 = 0;
                for (auto pathToP: oldPossiblePaths[p.y][p.x])
                {
                    auto it = pathToP.find(newPos);
                    if (it == pathToP.end())
                    {
                        flag3 = 1;
                        set <point> tmp = pathToP;
                        tmp.insert(newPos);
                        possiblePaths[newPos.y][newPos.x].insert(tmp);
                    }
                }
                if (flag3)
                {
                    newEnemyPos.pb(newPos);
                    enemyProp[newPos.y][newPos.x] = 2;
                }
                else
                    break;
            }
            else
                break;
        }
        for (int i = 1; i <= 4; i++)
        {
            point newPos = (mp(p.x + i,p.y));
            if (isValid(newPos))
            {
                bool flag3 = 0;
                for (auto pathToP: oldPossiblePaths[p.y][p.x])
                {
                    auto it = pathToP.find(newPos);
                    if (it == pathToP.end())
                    {
                        flag3 = 1;
                        set <point> tmp = pathToP;
                        tmp.insert(newPos);
                        possiblePaths[newPos.y][newPos.x].insert(tmp);
                    }
                }
                if (flag3)
                {
                    newEnemyPos.pb(newPos);
                    enemyProp[newPos.y][newPos.x] = 2;
                }
                else
                    break;
            }
            else
                break;
        }
        for (int i = 1; i <= 4; i++)
        {
            point newPos = (mp(p.x - i,p.y));
            if (isValid(newPos))
            {
                bool flag3 = 0;
                for (auto pathToP: oldPossiblePaths[p.y][p.x])
                {
                    auto it = pathToP.find(newPos);
                    if (it == pathToP.end())
                    {
                        flag3 = 1;
                        set <point> tmp = pathToP;
                        tmp.insert(newPos);
                        possiblePaths[newPos.y][newPos.x].insert(tmp);
                    }
                }
                if (flag3)
                {
                    newEnemyPos.pb(newPos);
                    enemyProp[newPos.y][newPos.x] = 2;
                }
                else
                    break;
            }
            else
                break;
        }
    }

    // for (auto p: enemyPos)
    // {
    //     if (possiblePaths[p.y][p.x].sz)
    //         possiblePaths[p.y][p.x].erase(possiblePaths[p.y][p.x].begin(), possiblePaths[p.y][p.x].begin() + oldPossiblePathsSizes[p.y][p.x]);
    // }

    enemyPos = newEnemyPos;
    sort( enemyPos.begin(), enemyPos.end() );
    enemyPos.erase( unique( enemyPos.begin(), enemyPos.end() ), enemyPos.end() );
    deb6 cerr<<enemyPos.sz<<"\n";
    deb6 cerr<<"Updated enemy silence.\n";
}

vector < pair < pair <char, int> , point> > getSilencePositions(point p)
{
    vector < pair <int, pair <point, pair <char, int > > > > silencePos;
    for (int i = 1; i <= 4; i++)
    {
        if (isValid(mp(p.x,p.y + i)) && !isVisited(mp(p.x,p.y + i)))
        {
            for (int y = p.y; y <= p.y + i; y++) visited[y][p.x] = 1;
            silencePos.pb(mp(scorePosition(mp(p.x,p.y + i)),mp(mp(p.x,p.y + i),mp('S',i))));
            for (int y = p.y; y <= p.y + i; y++) visited[y][p.x] = 0;
        }
        else
            break;
    }
    for (int i = 1; i <= 4; i++)
    {
        if (isValid(mp(p.x,p.y - i)) && !isVisited(mp(p.x,p.y - i)))
        {
            for (int y = p.y - i; y <= p.y; y++) visited[y][p.x] = 1;
            silencePos.pb(mp(scorePosition(mp(p.x,p.y - i)),mp(mp(p.x,p.y - i),mp('N',i))));
            for (int y = p.y - i; y <= p.y; y++) visited[y][p.x] = 0;
        }
        else
            break;
    }
    for (int i = 1; i <= 4; i++)
    {
        if (isValid(mp(p.x + i,p.y)) && !isVisited(mp(p.x + i,p.y)))
        {
            for (int x = p.x; x <= p.x + i; x++) visited[p.y][x] = 1;
            silencePos.pb(mp(scorePosition(mp(p.x + i,p.y)),mp(mp(p.x + i,p.y),mp('E',i))));
            for (int x = p.x; x <= p.x + i; x++) visited[p.y][x] = 0;
        }
        else
            break;
    }
    for (int i = 1; i <= 4; i++)
    {
        if (isValid(mp(p.x - i,p.y)) && !isVisited(mp(p.x - i,p.y)))
        {
            for (int x = p.x - i; x <= p.x; x++) visited[p.y][x] = 1;
            silencePos.pb(mp(scorePosition(mp(p.x - i,p.y)),mp(mp(p.x - i,p.y),mp('W',i))));
            for (int x = p.x - i; x <= p.x; x++) visited[p.y][x] = 0;
        }
        else
            break;
    }
    if (rand()%3 == 0)
        random_shuffle( silencePos.begin(), silencePos.end());
    else
        sort(silencePos.begin(), silencePos.end());
    vector < pair < pair <char, int> , point> > bestPos;
    for (auto p2: silencePos)
    {
        deb cerr<<"Can go silence to: "<<p2.second.first.x<<" "<<p2.second.first.y<<" with score:"<<p2.first<<" \n";
        bestPos.pb(mp(p2.second.second,p2.second.first));
    }

    return bestPos;
}
void handleOrders(string orders)
{
    deb5 cerr<<"ENEMY MOVES: "<<orders<<"\n";
    int itek = 0;
    while(itek < orders.sz)
    {
        switch(orders[itek])
        {
            case 'M':
            {
                itek++;
                if (orders[itek] == 'O')
                {
                    enemyCharges[TORPEDO]++;
                    itek+=4;
                    deb5 cerr<<"Enemy is going "<<orders[itek]<<"\n";
                    updateEnemyMove(orders[itek]);
                    itek++;
                }
                break;
            }
            case 'T':
            {
                if (orders[itek+1] == 'O')
                {
                    enemyCharges[TORPEDO] = 0;
                    itek+=8;
                    point enemyTorpedo;
                    enemyTorpedo.x = orders[itek] - '0';
                    itek++;
                    if (orders[itek] != ' ')
                    {
                        enemyTorpedo.x*=10;
                        enemyTorpedo.x+=orders[itek] - '0';
                        itek++;
                    }
                    itek++;
                    enemyTorpedo.y = orders[itek] - '0';
                    itek++;
                    if (itek < orders.sz && orders[itek] != '|')
                    {
                        enemyTorpedo.y*=10;
                        enemyTorpedo.y+=orders[itek] - '0';
                        itek++;
                    }
                    deb5 cerr<<"Enemy has fired TORPEDO at "<<enemyTorpedo.x<<" "<<enemyTorpedo.y<<"\n";
                    updateEnemyTorpedo(enemyTorpedo);
                }
                break;
            }
            case 'S':
            {
                itek++;
                if (orders[itek] == 'U')
                {
                    itek+=7;
                    int enemySector = orders[itek] - '0';
                    updateEnemySector(enemySector);
                    itek++;
                }
                if (orders[itek] == 'O')
                {
                    itek+=4;
                    int enemySectorGuess = orders[itek] - '0';
                }
                if (orders[itek] == 'I')
                {
                    itek+=5;
                    updateEnemySilence();
                }
                break;
            }
        }
        itek++;
    }
}
bool isRocketRange(point p, point fired)
{
    if (fired == mp(p.x,p.y+1))
        return true;
    if (fired == mp(p.x,p.y-1))
        return true;
    if (fired == mp(p.x-1,p.y))
        return true;
    if (fired == mp(p.x+1,p.y))
        return true;
    if (fired == mp(p.x+1,p.y+1))
        return true;
    if (fired == mp(p.x-1,p.y-1))
        return true;
    if (fired == mp(p.x-1,p.y+1))
        return true;
    if (fired == mp(p.x+1,p.y-1))
        return true;
    if (fired == mp(p.x,p.y))
        return true;
    return false;
}
int getDamage(point p)
{
    int dmg = 2*enemyProp[p.y][p.x];
    for (auto n: getValidNeighbours(p,2))
    {
        if (isRocketRange(n,p)){

            dmg+=enemyProp[n.y][n.x];
        }
    }
    return dmg;
}
bool clearShot(point p)
{
    if (myLife == 1)
        return false;
    if (oppLife == 1)
    {
        for (auto enemy: enemyPos)
            if (not isRocketRange(enemy,p))
                return false;
        return true;
    }
    if (enemyPos.sz == 1 && enemyPos[0] == p  && pos != p && oppLife <= myLife)
        return true;
    if (oppLife == 2 && myLife < 4)
    {
        if (enemyPos.sz == 1 && enemyPos[0] == p)
            return true;
        else
            return false;
    }
    if (oppLife == 2 && myLife >= 4)
    {
        return true;
    }
    if (oppLife < myLife)
        return true;
    return false;
}
vector <point> getRocketNeighbours(point p,int r)
{
    vector <point> tmp;
    bool boardTMP[height][width];
    queue <pair <point, int> > kolejka;
    for (int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
            boardTMP[y][x] = bool(board[y][x]);
    kolejka.push(mp(p,0));
    while (!kolejka.empty())
    {
        point vb = kolejka.front().first;
        int range = kolejka.front().second;
        kolejka.pop();
        if (range <= r)
        {
            boardTMP[vb.y][vb.x] = 1;
            for (auto u: getValidNeighbours(vb, 1))
            {
                if (!boardTMP[u.y][u.x]){
                    boardTMP[u.y][u.x] = 1;
                    kolejka.push(mp(u,range+1));
                }
            }
            tmp.pb(vb);
        }
    }
    return tmp;
}
vector < pair <int, point> > getBestShots(point p)
{
    vector <point> neighbours = getRocketNeighbours(p,4);
    vector < pair <int, point> > possibleShots;
    for (auto n: neighbours)
    {
        if (not isRocketRange(p,n) or clearShot(n))
            possibleShots.pb(mp(getDamage(n),n));
    }
    return possibleShots;
}
char putMine(point p)
{
    vector <char> moves2 = {'N','S','W','E'};
    for (auto m: moves2)
    {
        point newPos = movePos(p,m);
        if (isValid(movePos(p,m)) && !mines[newPos.y][newPos.x])
        {
            mines[newPos.y][newPos.x] = 1;
            return m;
        }
    }
    return '0';
}
vector < pair <int, point> > getBestMines(point p)
{
    vector < pair <int, point> > possibleMines;
    for (auto mine: minesV)
    {
        if ((not isRocketRange(p,mine) or clearShot(mine)) and lastMine != mine)
            possibleMines.pb(mp(getDamage(mine),mine));
    }
    sort(possibleMines.begin(), possibleMines.end());
    return possibleMines;
}
vector < pair <int, char> > getBestMoves(point p)
{
    deb cerr<<"Searching for best move from "<<pos.x<<" "<<pos.y<<"\n";
    vector <point> posNeighbours = getValidNeighbours(p,1);
    vector < pair <int, char> > bestmoves;
    visited[p.y][p.x] = 1;
    for (int i = 0; i < posNeighbours.sz; i++)
    {
        if (!visited[posNeighbours[i].y][posNeighbours[i].x] && !board[posNeighbours[i].y][posNeighbours[i].x])
        {
            int score = scorePosition(posNeighbours[i]);
            deb cerr<<"Candidate = "<<posNeighbours[i].x<<" "<<posNeighbours[i].y<<" with score "<<score<<"\n";
            char dir;
            if (posNeighbours[i].y - p.y == 1)
                dir = 'S';
            if (posNeighbours[i].y - p.y == -1)
                dir = 'N';
            if (posNeighbours[i].x - p.x == 1)
                dir = 'E';
            if (posNeighbours[i].x - p.x == -1)
                dir = 'W';
            if (score >= 1)
                bestmoves.pb(mp(score,dir));
        }
    }
    sort(bestmoves.begin(), bestmoves.end());
    if (bestmoves.sz)
        deb cerr<<"Best move is to "<<bestmoves[bestmoves.sz-1].second<<" with score "<<bestmoves[bestmoves.sz - 1].first<<"\n";
    return bestmoves;
}
void visitSilences(char dir, int l, point p)
{
    for (int i = 0; i <= l; i++)
    {
        visited[p.y][p.x] = 1;
        if (i != l)
           p = movePos(p, dir);
    }
    pos = p;
}
void visitSilences2(char dir, int l, point p)
{
    for (int i = 0; i <= l; i++)
    {
        visited[p.y][p.x] = 1;
        if (i != l)
           p = movePos(p, dir);
    }
}
void unVisitSilences(char dir, int l, point p)
{
    for (int i = 0; i <= l; i++)
    {
        if (i!=0)
            visited[p.y][p.x] = 0;
        if (i != l)
           p = movePos(p, dir);
    }
}
string doAction(string output)
{
    deb cerr<<"Curr position: "<<pos.x<<" "<<pos.y<<"\n";
    vector < pair < pair <char, int> , point> > bestSilences;
    if (charges[SILENCE] == 6) /* Ready to silence */
    {
        deb cerr<<"Ready to silence\n";
        bestSilences = getSilencePositions(pos);
        if (/* rand()%10 >= 4 && */bestSilences.sz)
        {
            if (output.sz)
                output+="|";
            char tmp = bestSilences[bestSilences.sz-1].first.first;
            visitSilences(bestSilences[bestSilences.sz-1].first.first, bestSilences[bestSilences.sz-1].first.second,pos);
            output+= "SILENCE ";
            output+=tmp;
            output+=string(" ");
            output+=to_string(bestSilences[bestSilences.sz-1].first.second);
            charges[SILENCE] = 0;
        }
    }
    if (charges[SONAR] == 4) /* Ready to Sonar */
    {
        deb cerr<<"Ready to sonar\n";
        vector < pair <int, int> > sectors;
        for (int i = 0; i < 9; i++)
            sectors.pb(mp(0,i+1));
        for (auto p: enemyPos)
            sectors[getSector(p)-1].first++;
        sort(sectors.begin(), sectors.end());
        if (sectors[5].first == 0)
        {
            deb cerr<<"LEQ then 3 sectors of enemys\n";
            deb cerr<<"Most in sector "<<sectors[8].second<<"\n";
            if (output.sz)
                output+="|";
            output+="SONAR " + to_string(sectors[8].second);
            charges[SONAR] = 0;
            lastSonar = sectors[8].second;
        }
    }
    if (charges[MINE] == 3) /* Ready to PUT mine */
    {
        deb cerr<<"Ready to put Mine\n";
        char m = putMine(pos);
        deb cerr<<"in direction: "<<m<<"\n";
        if (m != '0')
        {
            if (output.sz)
                output+="|";
            deb cerr<<"Put Mine\n";
            output+="MINE ";
            output+=m;
            charges[MINE] = 0;
            minesV.pb(movePos(pos,m));
            lastMine = movePos(pos,m);
        }
    }
    // if (charges[TORPEDO] == 3) /* Ready to shoot */
    // {
    //     vector < pair <int, point> > bestShots = getBestShots(pos);
    //     pair <int, point> bestShot;
    //     deb5 cerr<<"Ready to shot\n";
    //     if (bestShots.sz)
    //         bestShot = bestShots[bestShots.sz - 1];
    //     else
    //         bestShot =  mp(-1,mp(0,0));
    //     deb5 cerr<<"Best shot is at "<<bestShot.second.first<<" "<<bestShot.second.second<<" with dmg: "<<bestShot.first<<"\n";
    //     if (enemyPos.sz < 30 && bestShot.first >= max(int(2*ceil(3.0*float(enemyPos.sz)/5.0)),2))
    //     {
    //         if (output.sz)
    //             output+="|";
    //         deb5 cerr<<"Shots2 fired at "<<bestShot.second.first<<" "<<bestShot.second.second<<"\n";
    //         output+="TORPEDO " + to_string(bestShot.second.first) + " " + to_string(bestShot.second.second);
    //         deb5 cerr<<"GET DMG: "<<bestShot.second.x<<" "<<bestShot.second.y<<"\n";
    //         charges[TORPEDO] = 0;
    //         lastExplosions.pb(bestShot.second);
    //     }
    // }
    if (minesV.sz && !trigger) /* Checking to detonate mine */
    {
        pair < int, point > bestMine = mp(-1,mp(0,0));
        deb cerr<<"Ready to trigger mine\n";
        vector <pair < int, point > > bestMines = getBestMines(pos);
        if (bestMines.sz)
            bestMine = bestMines[bestMines.sz - 1];
        deb cerr<<"Best mine is at "<<bestMine.second.first<<" "<<bestMine.second.second<<" with dmg: "<<bestMine.first<<"\n";
        if(enemyPos.sz <= 6)
        {
            if (bestMine.first >= 2)
            {
                if (output.sz)
                    output+="|";
                deb cerr<<"Mine1 fired at "<<bestMine.second.first<<" "<<bestMine.second.second<<"\n";
                output+="TRIGGER " + to_string(bestMine.second.first) + " " + to_string(bestMine.second.second);
                deb cerr<<"GET DMG: "<<bestMine.second.x<<" "<<bestMine.second.y<<"\n";
                lastExplosions.pb(bestMine.second);
                point mine = bestMine.second;
                mines[mine.y][mine.x] = 0;
                vector <point> newMines;
                for(auto m: minesV)
                {
                    if(m!=mine)
                        newMines.pb(m);
                }
                minesV = newMines;
                trigger = true;
            }
        }
        else
        {
            if (enemyPos.sz < 50)
            {
                if (bestMine.first >= min(16, max(int(enemyPos.sz) - 5,1)))
                {
                    if (output.sz)
                        output+="|";
                    deb cerr<<"Mine2 fired at "<<bestMine.second.first<<" "<<bestMine.second.second<<"\n";
                    output+="TRIGGER " + to_string(bestMine.second.first) + " " + to_string(bestMine.second.second);
                    deb cerr<<"GET DMG: "<<bestMine.second.x<<" "<<bestMine.second.y<<"\n";
                    lastExplosions.pb(bestMine.second);
                    point mine = bestMine.second;
                    mines[mine.y][mine.x] = 0;
                    vector <point> newMines;
                    for(auto m: minesV)
                    {
                        if(m!=mine)
                            newMines.pb(m);
                    }
                    minesV = newMines;
                    trigger = true;
                }
            }
        }
    }
    return output;
}
void checkOppLife()
{
    deb6 cerr<<"Diff of lives is "<<oppLifeDiff<<"\n";
    deb6 cerr<<"Old enemy pos size: "<<enemyPos.sz<<"\n";
    if (opponentOrders.find("SURFACE") != string::npos)
    {
        oppLifeDiff--;
        for (auto p: enemyPos)
        {
            possiblePaths[p.y][p.x].clear();
            set <point> tmp;
            tmp.insert(p);
            possiblePaths[p.y][p.x].insert(tmp);
        }
        deb6 cerr<<"Enemy has surfaced so damgage taken from my torpedo or mine is "<<oppLifeDiff<<"\n";
    }
    deb6
    {
        cerr<<"explosions:\n";
        for (auto exp: lastExplosions)
            cerr<<exp.x<<" "<<exp.y<<",   ";
    }
    if (lastExplosions.sz)
    {
        if (oppLifeDiff == 2)
        {
            deb6 cerr<<"Enemy was in center of last torpedo or mine.\n";
            vector <point> newEnemyPos;
            clearPropBoard();
            for (auto exp: lastExplosions)
            {
                for (auto p: enemyPos)
                {
                    if (p == exp)
                    {
                        newEnemyPos.pb(p);
                        enemyProp[p.y][p.x] = 2;
                    }
                    else
                        possiblePaths[p.y][p.x].clear();
                }
            }
            enemyPos = newEnemyPos;
        }
        if (oppLifeDiff == 1)
        {
            deb6 cerr<<"Enemy was near the explosion\n";
            vector <point> newEnemyPos;
            clearPropBoard();
            for (auto exp: lastExplosions)
            {
                for (auto p: enemyPos)
                {
                    if (isRocketRange(p,exp) && p != exp)
                    {
                        newEnemyPos.pb(p);
                        enemyProp[p.y][p.x] = 2;
                    }
                    else
                        possiblePaths[p.y][p.x].clear();
                }
            }
            enemyPos = newEnemyPos;
        }
        if (oppLifeDiff == 0)
        {
            deb6 cerr<<"Enemy missed explosion\n";
            vector <point> newEnemyPos;
            clearPropBoard();
            for (auto exp: lastExplosions)
            {
                for (auto p: enemyPos)
                {
                    if (!isRocketRange(p,exp))
                    {
                        newEnemyPos.pb(p);
                        enemyProp[p.y][p.x] = 2;
                    }
                    else
                        possiblePaths[p.y][p.x].clear();
                }
            }
            enemyPos = newEnemyPos;
        }
    }
    deb6 cerr<<"New enemy pos size: "<<enemyPos.sz<<"\n\n";
}

int minimalDmg()
{
    max(int(2*ceil(3.0*float(enemyPos.sz)/5.0)),2);
}

int global_bestScore = -2;
string global_bestOutput = "";

void bestActionSeq(vector <string> options, int itek, point p, int score, string output)
{
    if (score >= global_bestScore && itek < options.sz)
    {
        global_bestScore = score;
        global_bestOutput = output;
    }
    if (itek >= options.sz) // dodać jakieś ucieczki gonitwy itp, czyli dodawać score jak fajnie spierdalam np.
    {
        bool flag = 1;
        if (enemyPos.sz <= 2)
        {
            for (int i = 0; i <= enemyPos.sz; i++)
            {
                if (manhattan(enemyPos[i],p) > 5)
                    flag = 0;
            }
        }
        if (enemyPos.sz == 1)
        {
            if (myLife == 1 && oppLife > 2 && manhattan(enemyPos[0],p) > 5)
                score+=10;
        }
        if (flag && oppLife > myLife + 1)
            score--;
        if (flag && oppLife < myLife)
            score++;
        if (!flag && oppLife < myLife)
            score--;
        if (!flag && oppLife > myLife + 1)
            score++;
        if (score >= global_bestScore)
        {
            global_bestScore = score;
            global_bestOutput = output;
        }
        return;
    }
    bool allCLose = 1;
    for (auto p2: enemyPos)
    {
        if(manhattan(p2,p) >= 6)
            allCLose = 0;
    }
    if (options[itek] == "TORPEDO" && charges[TORPEDO] == 3)
    {
        if (enemyPos.sz == 1 or allCLose)
        {
            vector < pair <int, point> > bestShots = getBestShots(p);
            for (auto shot: bestShots)
            {
                int currScore = score;
                string currOutput = output;
                if (shot.second == enemyPos[0])
                    deb4 cerr<<"CZY DZIAŁA?\n";
                if (shot.first >= 2)
                {
                    if (shot.second == enemyPos[0])
                        deb4 cerr<<shot.first<<"\n";
                    currScore = max(score, 0);
                    currScore += shot.first;
                    if (currOutput.sz)
                        currOutput+="|";
                    currOutput+= "TORPEDO " + to_string(shot.second.first) + " " + to_string(shot.second.second);
                    if (shot.second == enemyPos[0])
                    {
                        deb4 cerr<<"TAK\n";
                        deb4 cerr<<p.x<<" "<<p.y<<"\n";
                        deb4 cerr<<"deb: "<<currOutput<<"\n"<<currScore<<"\n";
                    }
                    charges[TORPEDO] = 0;
                    size_t found = output.find("MOVE");
                    if ((found != string::npos && shot.first > 2))
                        currScore+=5;
                    if (found == string::npos)
                        currScore+=4;
                    // deb6 cerr<<"MINIMALNY DMG: "<<int(2*ceil(4.0*float(enemyPos.sz)/5.0))+2<<"\n";
                    if ((shot.first >= max(int(2*ceil(4.0*float(enemyPos.sz)/5.0) + 2),2)) or (oppLife == 1 && enemyPos.sz <= 2))
                        bestActionSeq(options, itek + 1, p, currScore, currOutput);
                    charges[TORPEDO] = 3;
                }
            }
        }
    }
    if (options[itek] == "SILENCE"  && charges[SILENCE] == 6)
    {
            vector < pair < pair <char, int> , point> > positions = getSilencePositions(p);
            for (auto position: positions)
            {
                int currScore = score;
                string currOutput = output;
                if (currOutput.sz)
                    currOutput+="|";
                char tmp = position.first.first;
                currScore-=2;
                currOutput+="SILENCE ";
                currOutput+=tmp;
                currOutput+=string(" ");
                currOutput+=to_string(position.first.second);
                visitSilences2(tmp,position.first.second,p);
                charges[SILENCE] = 0;
                size_t found = output.find("MOVE");
                if (found == string::npos)
                    currScore++;
                bestActionSeq(options, itek + 1, position.second, currScore, currOutput);
                charges[SILENCE] = 6;
                unVisitSilences(tmp,position.first.second,p);
            }
    }
    if (options[itek] == "TRIGGER")
    {
        vector < pair <int, point> > bestMines = getBestMines(p);
        for (auto mine: bestMines)
        {
            int currScore = score;
            string currOutput = output;
            if (mine.first >= 2)
            {
                score = max(score, 0);
                currScore += mine.first;
                if (currOutput.sz)
                    currOutput+="|";
                    currOutput+= "TRIGGER " + to_string(mine.second.first) + " " + to_string(mine.second.second);
                    if ((mine.first >= max(int(2*ceil(3.0*float(enemyPos.sz)/5.0)),4)) or (oppLife == 1 && enemyPos.sz <= 2))
                        bestActionSeq(options, itek + 1, p, currScore, currOutput);
            }
        }
    }
    if (options[itek] == "MOVE")
    {
        vector < pair <int, char> > moves = getBestMoves(p);
        for (auto m: moves)
        {
            int currScore = max(score,-1);
            string currOutput = output;
            if (currOutput.sz)
                currOutput+="|";
            currOutput+="MOVE ";
            currOutput+=m.second;
            currOutput+=string(" ");
            vector < pair <int, int > > whatCharge;
            bool enemyClose = 1;
            if (enemyPos.sz <= 4)
            {
                for (int i = 0; i <= enemyPos.sz; i++)
                {
                    if (manhattan(enemyPos[i],p) > 11)
                        enemyClose = 0;
                }
            }
            if (myLife <= 2 && (oppLife - myLife >=2) && charges[TORPEDO] < 2)
            {
                deb5 cerr<<"elo1\n";
                if (!enemyClose)
                    if (charges[TORPEDO] < 3) whatCharge.pb(mp(TORPEDO,70));
                if (charges[SILENCE] < 6) whatCharge.pb(mp(SILENCE,100));
                if (charges[MINE] < 3) whatCharge.pb(mp(MINE,100));
            }
            else
            {
                if (!enemyClose)
                {
                    deb5 cerr<<"elo2\n";
                    if (charges[MINE] < 3) whatCharge.pb(mp(MINE,40));
                    if (charges[TORPEDO] < 3) whatCharge.pb(mp(TORPEDO,70));
                    if (charges[SILENCE] < 6) whatCharge.pb(mp(SILENCE,100));
                }
                else
                {
                    deb5 cerr<<"elo3\n";
                    if (charges[TORPEDO] < 3) whatCharge.pb(mp(TORPEDO,100));
                    if (charges[SILENCE] < 6) whatCharge.pb(mp(SILENCE,50));
                    if (charges[MINE] < 3) whatCharge.pb(mp(MINE,100));
                }
            }
            int tmp = rand()%100+1;
            bool flag2 = 0;
            deb cerr<<"Rand num to charge is "<<tmp<<"\n";
            string chargingSTR = "";
            int chargingINT = -1;
            for (int i = 0; i < whatCharge.sz; i++)
            {
                if (whatCharge[i].second >= tmp)
                {
                    deb4 cerr<<"Charging "<<whatCharge[i].first<<"\n";
                    chargingSTR = dict[whatCharge[i].first];
                    chargingINT = whatCharge[i].first;
                    flag2 = 1;
                    break;
                }
            }
            if (!flag2)
            {
                for (int i = 0; i < whatCharge.sz; i++)
                {
                    if (whatCharge[i].second >= 0)
                    {
                        deb4 cerr<<"Charging2 "<<whatCharge[i].first<<"\n";
                        chargingSTR = dict[whatCharge[i].first];
                        chargingINT = whatCharge[i].first;
                        flag2 = 1;
                        break;
                    }
                }
            }
            if (chargingINT != -1)
                charges[chargingINT]++;
            currOutput+=chargingSTR;

            point newPos = movePos(p,m.second);
            visited[newPos.y][newPos.x] = 1;
            bestActionSeq(options, itek + 1, newPos, currScore, currOutput);
            visited[newPos.y][newPos.x] = 0;

            if (chargingINT != -1)
                charges[chargingINT]--;
        }
    }
    if (options[itek] == "MINE" && charges[MINE] == 3)
    {
        char m = putMine(pos);
        if (m != '0')
        {
            int currScore = score;
            string currOutput = output;
            if (currOutput.sz)
                currOutput+="|";
            currOutput+="MINE ";
            currOutput+=m;
            charges[MINE] = 0;
            lastMine = movePos(pos,m);
            bestActionSeq(options, itek + 1, p, currScore, currOutput);
            mines[lastMine.y][lastMine.x] = 0;
            charges[MINE] = 3;
            lastMine = mp(-1,-1);
        }
    }
}
void process(string output)
{
    int itek = 0;
    while(itek < output.sz)
    {
        switch(output[itek])
        {
            case 'M':
            {
                itek++;
                if (output[itek] == 'O')
                {
                    itek+=4;
                    visited[pos.y][pos.x] = 1;
                    pos = movePos(pos, output[itek]);
                    visited[pos.y][pos.x] = 1;
                    itek+=2;
                    if (itek < output.sz)
                    {
                        if (output[itek] == 'T')
                        {
                            charges[TORPEDO]++;
                            itek+=6;
                        }
                        if (output[itek] == 'S')
                        {
                            charges[SILENCE]++;
                            itek+=6;
                        }
                        if (output[itek] == 'M')
                        {
                            charges[MINE]++;
                            itek+=3;
                        }
                    }
                }
                else
                {
                    if (output[itek] == 'I')
                    {
                        charges[MINE] = 0;
                        itek+=4;
                        point enemyTorpedo;
                        char dir = output[itek];
                        point minePos = movePos(pos, dir);
                        minesV.pb(minePos);
                        mines[minePos.y][minePos.x] = 1;
                    }
                }
                break;
            }
            case 'T':
            {
                if (output[itek+1] == 'O')
                {
                    charges[TORPEDO] = 0;
                    itek+=8;
                    point enemyTorpedo;
                    enemyTorpedo.x = output[itek] - '0';
                    itek++;
                    if (output[itek] != ' ')
                    {
                        enemyTorpedo.x*=10;
                        enemyTorpedo.x+=output[itek] - '0';
                        itek++;
                    }
                    itek++;
                    enemyTorpedo.y = output[itek] - '0';
                    itek++;
                    if (itek < output.sz && output[itek] != '|')
                    {
                        enemyTorpedo.y*=10;
                        enemyTorpedo.y+=output[itek] - '0';
                        itek++;
                    }
                    lastExplosions.pb(enemyTorpedo);
                    deb2 cerr<<"SHOTS has fired TORPEDO at "<<enemyTorpedo.x<<" "<<enemyTorpedo.y<<"\n";
                }
                if (output[itek+1] == 'R')
                {
                    itek+=8;
                    vector <point> newMinesV;
                    point enemyTorpedo;
                    enemyTorpedo.x = output[itek] - '0';
                    itek++;
                    if (output[itek] != ' ')
                    {
                        enemyTorpedo.x*=10;
                        enemyTorpedo.x+=output[itek] - '0';
                        itek++;
                    }
                    itek++;
                    enemyTorpedo.y = output[itek] - '0';
                    itek++;
                    if (itek < output.sz && output[itek] != '|')
                    {
                        enemyTorpedo.y*=10;
                        enemyTorpedo.y+=output[itek] - '0';
                        itek++;
                    }
                    for (auto mina: minesV)
                    {
                        if (mina.x != enemyTorpedo.x or mina.y != enemyTorpedo.y)
                            newMinesV.pb(mina);
                    }
                    lastExplosions.pb(enemyTorpedo);
                    minesV = newMinesV;
                    mines[enemyTorpedo.y][enemyTorpedo.y] = 0;
                    deb2 cerr<<"SHOTS has fired TORPEDO at "<<enemyTorpedo.x<<" "<<enemyTorpedo.y<<"\n";
                }
                break;
            }
            case 'S':
            {
                itek++;
                if (output[itek] == 'I')
                {
                    deb2 cerr<<"I used silence.\n";
                    itek+=7;
                    charges[SILENCE] = 0;
                    char direction = output[itek];
                    itek+=2;
                    int steps = output[itek] - '0';
                    visitSilences(direction,steps,pos);
                }
                break;
            }
        }
        itek++;
    }
}
string getBestMoveEnd()
{
    deb6 cerr<<"\nNowa funkcją generująca ruch.\n";
    int bestScore = -1;
    string bestMove = "";
    point oldPos = pos;
    vector <string> options = {"MOVE"};

    if (charges[SILENCE] >= 5) options.pb("SILENCE");
    if (minesV.sz) options.pb("TRIGGER");
    if (charges[MINE] >= 2 && enemyPos.sz == 1 && manhattan(enemyPos[0],pos) >= 10)
        options.pb("MINE");
    else
        if (charges[TORPEDO] >= 2)
            options.pb("TORPEDO");

    sort(options.begin(), options.end());
    do {
        global_bestScore = -2;
        global_bestOutput = "";
        bestActionSeq(options,0,pos,-2,"");
        int candidateScore = global_bestScore;
        string candidateMove = global_bestOutput;
        if (candidateScore >= bestScore)
        {
            bestScore = candidateScore;
            bestMove = candidateMove;
        }
        // deb4 cerr<<"Current best ruch is "<<global_bestOutput<<" with score "<<global_bestScore<<"\n";
    } while (next_permutation(options.begin(), options.end()));
    deb5 cerr<<"BEST:\n"<<bestMove<<"\nwith score: "<<bestScore<<"\n";
    pos = oldPos;
    process(bestMove);
    return bestMove;
}

int main()
{
    srand(ll(new(int)));
    /* INPUT */
    dict[TORPEDO] = "TORPEDO";
    dict[SILENCE] = "SILENCE";
    dict[SONAR] = "SONAR";
    dict[MINE] = "MINE";
    cin>>width>>height>>ID; cin.ignore();
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line);
        for (int j = 0; j < width; j++)
        {
            mines[i][j] = 0;
            visited[i][j] = 0;
            if (line[j] == 'x')
            {
                board[i][j] = 1;
                enemyProp[i][j] = 0;
            }
            else
            {
                board[i][j] = 0;
                enemyProp[i][j] = 1;
                enemyPos.pb(mp(j,i));
                set <point> tmp;
                tmp.insert(mp(j,i));
                possiblePaths[i][j].insert(tmp);
            }
        }
    }

    vector < pair <int, point> > startCandidates;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            startCandidates.pb(mp(scorePosition(mp(i,j)), mp(i,j)));
    sort(startCandidates.begin(), startCandidates.end());
    pos = startCandidates[startCandidates.sz - 1].second;
    cout << pos.x << " " << pos.y << endl;

    /* GAME LOOP */
    while (true)
    {
        int oldOppLife = oppLife;
        int torpedo_cooldown;
        int sonar_cooldown;
        int silence_cooldown;
        int mine_cooldown;
        scanf("%d%d%d%d%d%d%d%d",&pos.x,&pos.y,&myLife,&oppLife,&cooldowns[TORPEDO],&cooldowns[SONAR],&cooldowns[SILENCE],&cooldowns[MINE]);
        // cin>>pos.x>>pos.y>>myLife>>oppLife>>cooldowns[TORPEDO]>>cooldowns[SONAR]>>cooldowns[SILENCE]>>cooldowns[MINE]; cin.ignore()
        string sonar_result;

        oppLifeDiff = oldOppLife - oppLife;
        
        visited[pos.y][pos.x] = 1;
        
       cin>>sonar_result; cin.ignore();
        if (sonar_result == "Y")
            updateEnemySector(lastSonar);
        getline(cin, opponentOrders);
        if (opponentOrders != "NA")
        {
            checkOppLife();
            lastExplosions.clear();
            handleOrders(opponentOrders);
            deb6 printBoard();
            lastMine = mp(-1,-1);
        }

        deb6 cerr<<"Handled Orders!\n";

        trigger = false;
        string output;
        if (enemyPos.sz > 15)
        {
            output = doAction("");
            vector < pair <int, char> >  moves = getBestMoves(pos);
            if (moves.sz)
            {
            if (output.sz)
                output+="|";
            output+=string("MOVE ") + moves[moves.sz-1].second;
            pos = movePos(pos, moves[moves.sz-1].second);

            vector < pair <int, int > > whatCharge;

            if (diffrentEnemySectors() >= 3 && enemyPos.sz > 20) //start
            {
                if (charges[TORPEDO] < 3) whatCharge.pb(mp(TORPEDO,10));
                if (charges[MINE] < 3) whatCharge.pb(mp(MINE,50));
                if (charges[SILENCE] < 6) whatCharge.pb(mp(SILENCE,70));
                if (charges[SONAR] < 4) whatCharge.pb(mp(SONAR,100));
            }
            else //middle
            {
                if (charges[MINE] < 3) whatCharge.pb(mp(MINE,40));
                if (charges[TORPEDO] < 3) whatCharge.pb(mp(TORPEDO,60));
                if (charges[SILENCE] < 6) whatCharge.pb(mp(SILENCE,100));
            }
            int tmp = rand()%100+1;
            bool flag2 = 0;
            for (int i = 0; i < whatCharge.sz; i++)
            {
                if (whatCharge[i].second >= tmp)
                {
                    charges[whatCharge[i].first]++;
                    output+=string(" ") + dict[whatCharge[i].first];
                    flag2 = 1;
                    break;
                }
            }
            if (!flag2)
            {
                for (int i = 0; i < whatCharge.sz; i++)
                {
                    if (whatCharge[i].second >= 0)
                    {
                        deb cerr<<"Charging2 "<<whatCharge[i].first<<"\n";
                        charges[whatCharge[i].first]++;
                        output+=string(" ") + dict[whatCharge[i].first];
                        flag2 = 1;
                        break;
                    }
                }
            }
            if (flag2)
                output = doAction(output);
            }
        }
        else
            output = getBestMoveEnd();

        if (output.sz == 0)
        {
            cout << "SURFACE\n";
            for (int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                    visited[i][j] = 0;
            visited[pos.y][pos.x] = 1;
        }
        else
            cout<<output<<"|MSG "<<enemyPos.sz<<"\n";
    }
}