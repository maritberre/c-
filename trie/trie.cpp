#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>
using namespace std;

const int ALPHABET_SUBSET = 10;

struct TrieNode
{
    int value; /* Used to mark leaf nodes */
    TrieNode *children[ALPHABET_SUBSET];
    
    TrieNode() {
        value = 0;
        for (int i = NULL; i < ALPHABET_SUBSET; i++) {
            children[i] = NULL;
        }
    }
};

int main() {

    int N;
    cin >> N;
    TrieNode *root = new TrieNode();
    
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        TrieNode *cur = root;
        bool issubset = true;
        cout << endl << "Processing string " << str << ":" << endl;
        for (auto it = str.begin() ; it < str.end(); it++) {
            assert(*it-97 >= 0);
            assert(*it-97 < ALPHABET_SUBSET);
            int idx = *it-97;
            cout << "idx is " << idx << ", letter is " << *it << ". ";
            if(cur->children[idx].value == 0) {
                cout << "Inserting new node as child of " << cur << endl;
                // insert this letter
                TrieNode *newNode = new TrieNode();
                cur->children[idx] = newNode;
                cur->children[idx].value++;
                cur = newNode; // for next iteration
                issubset = false;
            } else {
                cout << "Subset so far" << endl;
            }
        }
        if (issubset) {
            cout << "BAD SET" << endl;
            cout << str << endl;
            break;
        }
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}