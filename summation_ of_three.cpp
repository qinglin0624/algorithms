// Last modified: April 17, 2021
#include <iostream>
#include <vector>
using namespace std;


// I find that defining it in main() and passing it to functions "insert" and "find" cannot 
// have it modified, so I have to define it here. The reason for that is to be learned.

// 5000 numbers at most -> 12502500 distinct sum_of_two_number at most -> vector has size 13000000
vector<int> sum_of_two(13000000,2e9+1);

// use double hashing, choose m' = m - 1
int func(int k, int i){
    if (k<0) k=-k;
    return ((k%13000000) + i * (1 + (k%12999999))) % 13000000;
}

void insert(int key){
    int i=0;
    while (true){
        int idx = func(key,i);
        if (sum_of_two[idx]==key) return;
        if (sum_of_two[idx]==2e9+1){
            sum_of_two[idx]=key;
            return;
        }
        else i++;
    }
}


bool find(int key){
    int i=0;
    while (true){
        int idx = func(key,i);
        if (sum_of_two[idx]==2e9+1) return false;
        else if (sum_of_two[idx]==key) {
            return true;
        }
        else i++;
    }
}


int main(){
    int num_good = 0;

    int N;
    cin >> N;
    int A[N];
    for (int i=0; i<N; i++){
        int a;
        cin >> a;
        A[i] = a;

        // check good integer or not:
        // a = number_1 + sum_of_two_number
        // try different number_1 and see whether the corressponding sum_of_two_number exist
        for (int j=0; j<i; j++){
            int diff = a - A[j];
            if (find(diff)){
                num_good++;
                break;
            }
        }

        // store its sum with the preceding numbers (including itself) for future use
        for (int j=0; j<i+1; j++){
            insert(A[j]+a);
        }
    }
    cout << num_good;
    return 0;
}
