// Last modified: April 11, 2021

// The idea comes from: https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/solution/javacong-bao-li-kai-shi-you-hua-pei-tu-pei-zhu-shi/

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;


int max_vertically(int arr[], int n){
    int MAX = -128;
    // try different ranges of y1~y2
    for (int y1=0; y1<n; y1++){
        int sum = 0;
        for (int y2=y1; y2<n; y2++){
            // add the columns between y1 and y2 up
            sum += arr[y2];
            if (sum > MAX) MAX = sum;
        }
    }
    return MAX;
}


int main(){
    int N;
    cin >> N;
    int A[N][N];
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cin >> A[i][j];
        }
    }

    // max_horizontally, within which it is maximized vertically
    int MAX = -128;
    // try different ranges of x1~x2
    for (int x1=0; x1<N; x1++){
        int rowSum[N]={0};
        for (int x2=x1; x2<N; x2++){
            // add the rows between row x1 and x2 up
            for (int col=0; col<N; col++){
                rowSum[col] += A[x2][col];
            }
            // then maximize the summation by columns
            MAX = max(MAX, max_vertically(rowSum, N));
        }
    }
    cout << MAX;
}
