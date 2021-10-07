// Last modified: April 02, 2021
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int N;
    cin >> N;
    int a;
    int b;
    // bucket sort
    // make B a new array
    vector<int> B[1001]={}; // since x_value<=1000
    for (int i=0; i<N; i++){
        scanf("%d %d",&a, &b);
        // put ys in the correct B[i] according to xs
        B[a].push_back(b);
    }
    // sort list B[i]
    for (int i=0; i<1001; i++){
        sort(B[i].begin(),B[i].end());
    }
    // print result
    for (int i=0; i<1001; i++){
        int change = 0;
        for (int j=0; j<B[i].size();j++){
            change = 1;
            cout << B[i][j];
            cout << ((j == B[i].size()-1) ? "\n"  : " ");
        }
    } 
    return 0;
}
