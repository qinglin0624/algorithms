// Last modified: March 24, 2021
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int INF = numeric_limits<int>::max(); // the largest integer

void merge(int arr[], int s, int m, int e){
    // get the content of the first part
    int arr1[m-s+1];
    int idx1 = 0;
    for (int i=s; i<m; i++){
        arr1[idx1++] = arr[i];
    }
    arr1[m-s] = INF;
    // get the content of the second part
    int arr2[e-m+1];
    int idx2 = 0;
    for (int i=m; i<e; i++){
        arr2[idx2++] = arr[i];
    }
    arr2[e-m] = INF;
    // change values in the original array
    int *p1 = arr1;
    int *p2 = arr2;
    
    for(int i=s; i<e; i++){
        if (*p1 <= *p2){
            arr[i] = *p1;
            p1++;
        }
        else{
            arr[i] = *p2;
            p2++;
        }
    }
}

void mergeSort(int arr[], int s, int e){
    if (e-s>=2){
        int m = (s+e)/2;
        // merge the first and second part separately
        mergeSort(arr, s, m);
        mergeSort(arr, m, e);
        merge(arr, s, m, e);
    }
}


int main(){
    int N;
    cin >> N;
    int arr[N];
    for (int i=0; i<N; i++){
        cin >> arr[i];
    }

    mergeSort(arr, 0, N);

    for (int i=0; i<N; i++){
        cout << arr[i] << " ";
    }
    return 0;
}

