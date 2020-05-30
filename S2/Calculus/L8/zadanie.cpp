#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

float dist(pair <int, int> a, pair <int, int> b)
{
    return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

int main() {


    vector < pair <int, int> > punkty;
    int n,x,y;
    cout<<"Wprowadź liczbę punktów:\n";
    cin>>n;
    cout<<"\n Teraz wprowadź kolejno punkty:";
    for(int i = 0; i < n ; i++)
    {
        cout<<"\nWprowadź "<<i+1<<"-ty punkty:\n";
        cin>>x>>y;
        punkty.push_back(make_pair(x,y));
    }

    sort(punkty.begin(), punkty.end());

    float bestScore = 10000;
    vector < pair <int, int> > bestPath;

    do {
        float currScore = 0;
        for (int i = 0; i < n-1; i++)
            currScore+=dist(punkty[i],punkty[i+1]);
    if (currScore < bestScore)
    {
        bestScore = currScore;
        bestPath = punkty;
    }
    } while (next_permutation(punkty.begin(),punkty.end()));

    cout<<"Najkrótsza ścieżka ma długość: "<<bestScore;
    cout<<"\nNajkrótsza ścieżka:\n";
    for(int i = 0; i < n ; i++)
        cout<<bestPath[i].first<<" "<<bestPath[i].second<<"\n";

    return 0;
}