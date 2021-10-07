// Last modified: March 24, 2021
#include <iostream>

using namespace std;


void countingSort(int arr[], int N){
    int store[1000]={0};
    // store the time of appearances of a number
    for (int i=0; i<N; i++){
        store[arr[i]] += 1;
    }
    // change values in the original array
    int *p = arr;
    for (int i=0; i<1000; i++){
        for (int j=0; j<store[i]; j++){
            *p++ = i;
        }
    }
}

int main(){
    int N;
    cin >> N;
    int arr[N];
    for (int i=0; i<N; i++){
        cin >> arr[i];
    }
    countingSort(arr, N);

    for (int i=0; i<N; i++){
        cout << arr[i] << " ";
    }
    return 0;
}
