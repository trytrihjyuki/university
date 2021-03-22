
#include <bits/stdc++.h> 
using namespace std; 
  
// Function to return the largest sum 
int largest_sum(int arr[], int n) 
{ 
    map<int, int> m; 
  
    for (int i = 0; i < n; i++) { 
        m[arr[i]]++; 
    } 
  
    for (auto j : m) { 
  
        if (j.second > 1) { 
  
            m[2 * j.first] 
                = m[2 * j.first] 
                  + j.second / 2; 
  
            if (2 * j.first > maximum) 
                maximum = 2 * j.first; 
        } 
    } 
  
    return maximum; 
} 


int main()
{ 
    ll m,n,d;
    cin >> m;
    map<int, int> m; 
    for (int i = 0; i < m; ++i)
    {
        cin >> d >> n;
        map[d] = n;
    }
    int elm = n;

    while (elm)
    {
        for (auto s : m) { 
            if (s.second == 1)
            { 
                m[2 * s.first] += s.second / 2; 
            } 
        }
    }

    return 0; 
} 