#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 1;
#define deb if(debug)
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
vector <point> nonIsland;
int cooldowns[4];
int charges[4];
int enemyCooldowns[4];
int enemyCharges[4];
point pos;
int myLife,oppLife;

vector <point> enemyPos;
int enemyProp[maxn][maxn];
int visited[maxn][maxn];

point target;

pair <int, int> movePos(point p,char move)
{
    switch(move)
    {
        case 'N':
            return {p.x,p.y-1};
        case 'S':
            return {p.x,p.y+1};
        case 'W':
            return {p.x+1,p.y};
        case 'E':
            return {p.x-1,p.y};
    }
}
bool isIsland(point p)
{
    return board[p.y][p.x];
}
int getSector(point p)
{
    return (p.x/5 + 1 + (p.y/5) * 3);
}
int manhattan(point p1, point p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
void clearPorpBoard()
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            enemyProp[j][i] = 0;

}
void updateEnemyMove(char direction)
{
    deb cerr<<"Updating enemy: MOVE\nPossible positions: "<<enemyPos.sz<<"\n";
    vector <point> newEnemyPos;
    for (auto p: enemyPos)
    {
        enemyProp[p.y][p.x] = 0;
        point newPos = movePos(p, direction);
        if ((newPos.x >= 0) && (newPos.x < width) && (newPos.y >= 0) && (newPos.y < height))
        {
            if(!isIsland(newPos))
            {
                newEnemyPos.pb(newPos);
                enemyProp[newPos.y][newPos.x] = 1;
            }
        }
    }
    enemyPos = newEnemyPos;
}
void updateEnemyTorpedo(point firedPos)
{
    deb cerr<<"Updating enemy: TORPEDO\n";
    vector <point> newEnemyPos;
    for (auto p: enemyPos)
    {
        enemyProp[p.y][p.x] = 0;
        if(manhattan(p,firedPos) <= 4)
        {
            newEnemyPos.pb(p);
            enemyProp[p.y][p.x] = 1;
        }
    }
    enemyPos = newEnemyPos;
}
void updateEnemySurface(int sector)
{
    deb cerr<<"Updating enemy: SURFACE\n";
    vector <point> newEnemyPos;
    for (auto p: enemyPos)
    {
        enemyProp[p.y][p.x] = 0;
        if(getSector(p) == sector)
        {
            newEnemyPos.pb(p);
            enemyProp[p.y][p.x] = 1;
        }
    }
    enemyPos = newEnemyPos;
}
void printBoard()
{
    cerr<<"\nBOARD:\n";
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            cerr<<board[i][j]<<" ";
        cerr<<"\n";
    }
    cerr<<"\nVISITED:\n";
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            cerr<<visited[i][j]<<" ";
        cerr<<"\n";
    }
    cerr<<"\n";
}
void handleOrders(string orders)
{
    deb cerr<<"ENEMY MOVES: "<<orders<<"\n";
    int itek = 0;
    while(itek < orders.sz)
    {
        switch(orders[itek])
        {
            case 'M':
            {
                enemyCharges[TORPEDO]++;
                itek+=5;
                deb cerr<<"Enemy is going "<<orders[itek]<<"\n";
                updateEnemyMove(orders[itek]);
                itek++;
                break;
            }
            case 'T':
            {
                enemyCharges[TORPEDO] = 0;
                itek+=8;
                point enemyTorpedo;
                enemyTorpedo.x = orders[itek] - '0';
                itek+=2;
                enemyTorpedo.y = orders[itek] - '0';
                deb cerr<<"Enemy has fired TORPEDO at "<<enemyTorpedo.x<<" "<<enemyTorpedo.y<<"\n";
                updateEnemyTorpedo(enemyTorpedo);
                itek++;
                break;
            }
            case 'S':
            {
                itek+=8;
                int enemySector = orders[itek] - '0';
                updateEnemySurface(enemySector);
                itek++;
                break;
            }
        }
        deb cerr<<"New possible positions: "<<enemyPos.sz<<"\n";
        itek++;
    }
}
vector <point> getValidNeighbours(point p, int range)
{
    vector <point> neighbours;
    for (int dx = -range; dx <= range; dx++){
        for (int dy = -(range-abs(dx)); dy <= (range-abs(dx)); dy++)
        {
            if ((p.x + dx >= 0) && (p.x + dx < width) && (p.y + dy >= 0) && (p.y + dy < height))
                    neighbours.pb({p.x + dx, p.y + dy});
        }
    }
    return neighbours;
}
int getDamage(point p, int range)
{
    int dmg = enemyProp[p.y][p.x];
    for (auto n: getValidNeighbours(p,range))
        dmg+=enemyProp[n.y][n.x];
    return dmg;
}
bool isRocketRange(point p, point fired)
{
    if (fired == make_pair(p.x,p.y+1))
        return true;
    if (fired == make_pair(p.x,p.y-1))
        return true;
    if (fired == make_pair(p.x-1,p.y))
        return true;
    if (fired == make_pair(p.x+1,p.y))
        return true;
    if (fired == make_pair(p.x+1,p.y+1))
        return true;
    if (fired == make_pair(p.x-1,p.y-1))
        return true;
    if (fired == make_pair(p.x-1,p.y+1))
        return true;
    if (fired == make_pair(p.x+1,p.y-1))
        return true;
    if (fired == make_pair(p.x,p.y))
        return true;
    return false;
}
pair <int, point> getBestShot(point p)
{
    vector <point> neighbours = getValidNeighbours(p,4);
    vector < pair <int, point> > possibleShots;
    for (auto n: neighbours)
    {
        if (not isRocketRange(p,n))
            possibleShots.pb(make_pair(getDamage(n,2),n));
    }
    sort(possibleShots.begin(), possibleShots.end());
    return possibleShots[possibleShots.sz - 1];
}
point getBestMove()
{
    deb cerr<<"Searching for best move from "<<pos.x<<" "<<pos.y<<"\n";
    int bestScore = 0;
    point bestMove = {-1,-1};
    vector <point> posNeighbours = getValidNeighbours(pos,1);
    for (int i = 0; i < posNeighbours.sz; i++)
    {
        if (!visited[posNeighbours[i].y][posNeighbours[i].x] && !board[posNeighbours[i].y][posNeighbours[i].x])
        {
            deb cerr<<"Candidate = "<<posNeighbours[i].x<<" "<<posNeighbours[i].y<<"\n";
            bool boardTMP[height][width];
            queue <point> kolejka;
            for (int x = 0; x < width; x++)
                for(int y = 0; y < height; y++)
                    boardTMP[y][x] = bool(visited[y][x] or board[y][x]);
            for (auto n: posNeighbours)
                boardTMP[n.y][n.x] = 1;
            int score = 0;
            kolejka.push(posNeighbours[i]);
            while (!kolejka.empty())
            {
                point vb = kolejka.front();
                if (vb == pos) score--;
                kolejka.pop();
                score++;
                for (auto u: getValidNeighbours(vb, 1))
                {
                    if (!boardTMP[u.y][u.x]){
                        boardTMP[u.y][u.x] = 1;
                        kolejka.push(u);
                    }
                }
            }
            if (bestScore < score)
            {
                bestScore = score;
                bestMove = posNeighbours[i];
            }
        }
    }
    deb cerr<<"Best move is to "<<bestMove.x<<" "<<bestMove.y<<" with score "<<bestScore<<"\n";
    return bestMove;
}
int main()
{
    srand(ll(new(int)));
    /* INPUT */
    cin>>width>>height>>ID; cin.ignore();
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line);
        for (int j = 0; j < width; j++)
        {
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
                nonIsland.pb({i,j});
                enemyPos.pb({i,j});
            }
        }
    }

    do {
        pos.x = rand()%width;
        pos.y = rand()%height;
    }
    while(isIsland(pos));
    deb cerr<<isIsland(pos);
    cout << pos.x << " " << pos.y << endl;

    /* GAME LOOP */
    while (true) {
        bool flag = 1;
        cin>>pos.x>>pos.y>>myLife>>oppLife>>cooldowns[TORPEDO]>>cooldowns[SONAR]>>cooldowns[SILENCE]>>cooldowns[MINE]; cin.ignore();
        visited[pos.y][pos.x] = 1;
        string sonarResult;
        cin >> sonarResult; cin.ignore();
        string opponentOrders;
        getline(cin, opponentOrders);
        deb cerr<<"\nHandle orders...\n";
        deb printBoard();
        if (opponentOrders != "NA")
            handleOrders(opponentOrders);

        deb cerr<<"\nDo action...\n";
        pair < int, point > bestShot1 = {-1,{0,0}};
        pair < int, pair <char ,point> > bestShot2 = {-1,{'a',{0,0}}};
        string output = "";
        bool fired = 0;
        if (charges[TORPEDO] == 3) /* Ready to shoot */
        {
            deb cerr<<"Ready to shot\n";
            bestShot1 = getBestShot(pos);
            if (bestShot1.first > min(7, max(int(enemyPos.sz) - 5,1)))
            {
                deb cerr<<"Shots fired at "<<bestShot1.second.first<<" "<<bestShot1.second.second<<"\n";
                output+="TORPEDO " + to_string(bestShot1.second.first) + " " + to_string(bestShot1.second.second) + "|";
                fired = 1;
                charges[TORPEDO] = 0;
            }
        }
        // if (charges[TORPEDO] == 2) TO DO
        point move = getBestMove();
        if (move.y - pos.y == 1)
            output+="MOVE S";
        if (move.y - pos.y == -1)
            output+="MOVE N";
        if (move.x - pos.x == 1)
            output+="MOVE E";
        if (move.x - pos.x == -1)
            output+="MOVE W";
        if (charges[TORPEDO] <= 2){
            output+=" TORPEDO";
            charges[TORPEDO]++;
        }
        if (move == make_pair(-1,-1) and bestShot1.first == -1)
        {
            deb cerr<<"!!!!!!!!!!!!!!!!Cannot do anything, SURFACE...\n";
            cout << "SURFACE\n";
            for (int i = 0; i < height; i++)
                for(int j = 0; j < width; j++)
                    visited[i][j] = 0;
            flag = 0;
            visited[pos.y][pos.x] = 1;
        }
        else
        {
            if(move != make_pair(-1,-1))
            {
                cout<<output<<"\n";
            }
            else
            {
                cerr<<move.x<<" "<<move.y<<endl;
                if (!fired)
                {
                    deb cerr<<"Shots fired at "<<bestShot1.second.first<<" "<<bestShot1.second.second<<"\n";
                    output+="TORPEDO " + to_string(bestShot1.second.first) + " " + to_string(bestShot1.second.second);
                    cout<<output<<"\n";
                    charges[TORPEDO] = 0;
                }
            }
        }
    }
}