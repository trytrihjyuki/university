#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair

int LENGTH = 0;

class Node
{
    public:
    int val;
    int key;
    Node *left;
    Node *right;
    Node *parent;
    int height;


    int BF()
    {
        int left_h = 0, right_h = 0;
        if (left != NULL) left_h = left->height;
        if (right != NULL) right_h = right->height;
        return right_h - left_h;
    }
};

Node* getNewNode(int val, int key, Node* parent)
{
    Node* N = new Node();
    N->val = val;
    N->key = key;
    N->left = NULL;
    N->right = NULL;
    N->parent = parent;

    return N;
}

Node* insert(Node *N, int val, int key, Node* parent)
{
    /* BST insert */
    if (N == NULL) return getNewNode(val, key, parent);
    if (N->key > key) insert(N->right, val, key, N);
    else insert(N->left, val, key, N);
    

}


int main()
{
    return 0;
}