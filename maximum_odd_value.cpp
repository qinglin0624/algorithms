//Last modified: April 10, 2021
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void fill_four_array(vector<int> A, int largest_odd[], int largest_even[], int smallest_odd[], int smallest_even[], int n){

    // find the largest odd/even BEFORE the ith element
    largest_even[0] = -1;
    largest_odd[0] = -1;
    if (A[0]%2==0){
        largest_even[1] = A[0];
        largest_odd[1] = -1;
    }
    else{
        largest_odd[1] = A[0];
        largest_even[1] = -1;
    }
    for (int i=1; i<n-1; i++){
        if (A[i]%2==0){
        largest_even[i+1] = A[i];
        largest_odd[i+1] = largest_odd[i];
        }
        else{
        largest_odd[i+1] = A[i];
        largest_even[i+1] = largest_even[i];
        }
    }
    // find the smallest odd and even SINCE the ith element
    if (A[n-1]%2==0){
        smallest_even[n-1] = A[n-1];
        smallest_odd[n-1] = -1;
    }
    else{
        smallest_odd[n-1] = A[n-1];
        smallest_even[n-1] = -1;
    }
    for (int i=n-2; i>=0; i--){
        if (A[i]%2==0){
            smallest_even[i] = A[i];
            smallest_odd[i] = smallest_odd[i+1];
        }
        else{
            smallest_odd[i] = A[i];
            smallest_even[i] = smallest_even[i+1];
        }
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> A={};
    for (int i=0; i<n; i++){
        int a;
        cin >> a;
        A.push_back(a);
    }
    sort(A.begin(),A.end());

    int m;
    cin >> m;
    int B[m];
    for (int i=0; i<m; i++){
        int k;
        cin >> k;
        B[i]=k;
    }

    // sum of the k largest value: accumulate vi from the right
    long long int sum[n];
    sum[n-1] = A[n-1];
    for (int i=n-2; i>=0; i--){
        sum[i] = sum[i+1] + A[i];
    }


    int largest_odd[n];
    int largest_even[n];
    int smallest_odd[n];
    int smallest_even[n];
    fill_four_array(A, largest_odd, largest_even, smallest_odd, smallest_even, n);
    

    
    for (int i=0; i<m; i++){
        int k = B[i];
        // get the sum of the k largest values
        long long int k_sum = sum[n-k];
        if (k_sum%2==1){
            cout << k_sum << "\n";
        }
        else {
            long long int backup1;
            long long int backup2;
            bool backup1_flag = true;
            bool backup2_flag = true;
            int s_o = smallest_odd[n-k];
            int l_e = largest_even[n-k];
            int s_e = smallest_even[n-k];
            int l_o = largest_odd[n-k];

            // backup 1: substitute the smallest odd with the largest even
            if (s_o==-1 || l_e==-1) backup1_flag = false;
            else backup1 = k_sum - s_o + l_e;
            // backup 2: substitute the smallest even with the largest odd
            if (s_e==-1 || l_o==-1) backup2_flag = false;
            else backup2 = k_sum - s_e + l_o;

            // the superior backup wins
            if (backup1_flag && backup2_flag){
                if (backup1 > backup2) cout << backup1 << "\n";
                else cout << backup2 << "\n";
            }
            else{
                if (backup1_flag) cout << backup1 << "\n";
                else if (backup2_flag) cout << backup2 << "\n";
                else cout << -1 <<"\n";
            }
        }
    }
    return 0;
}
