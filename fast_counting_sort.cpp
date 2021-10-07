// Last modified: April 01, 2021
#include <iostream>

using namespace std;


int main(){
    int N;
    cin >> N;
    int store[1000]={0};

    for (int i=0; i<N; i++){
        int num;
        cin >> num;
        store[num]++;
    }

    for (int i=0; i<1000; i++){
        for (int j=0; j<store[i]; j++){
            cout << i << " ";
        }
    }
    return 0;
}
