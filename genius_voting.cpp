// Last modified: April 04, 2021
#include <iostream>
#include <cmath>
using namespace std;

// by induction:
// n  remaining award
// 2     2       1/2
// 3     2       1/2
// 4     4       1/4
// 5     4       1/4
// 6     4       1/4
// 7     4       1/4
// 8     8       1/8
// ...   ...     ...
// Therefore, the number of remaining people is the largest 2^k that is <= n.

int main(){
    int n;
    cin >> n;
    int result = 1;

    while (result <= n){
        result = result * 2;
    }
    cout << result / 2;
    return 0;
}
