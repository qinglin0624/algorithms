// Last modified: April 17, 2021
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
using namespace std;
// Reference:
// I learn the functions for large number multiplication and division from 
// https://leetcode-cn.com/problems/multiply-strings/solution/da-shu-xiang-cheng-by-liyiping/



// assume that order_1 is better than order_2
//    order_1       order_2
//     a0 b0         a0 b0
//     a1 b1         a2 b2
//     a2 b2         a1 b1
// then we have: a0*a1/a2 < a0*a2/b1
// that is, a1b1 < a2b2
// continue inferring this way, we can conclude that the pair with small a*b comes first
// if two pairs have same a*b value, the one with small b comes first

bool comp_pair(pair<int,int> i, pair<int,int> j){
    if (i.first * i.second < j.first * j.second) return true;
    else if (i.first * i.second > j.first * j.second) return false;
    else return (i.second < j.second);
}

// compare two string of number: judge whether the left is smaller
// we need to do this because c++ considers "10" < "1"
bool left_small(string s1, string s2){
    if (s1.size() < s2.size()) return true;
    else if (s1.size() == s2.size()) return (s1<s2);
    else return false;
}

string mul(string large_number, string multiplier) 
{ 
    int L1 = large_number.size(); 
    int L2 = multiplier.size(); 
    if (L1*L2 == 0) return "0";
  
    // result stores the digits in reverse order 
    int result[L1+L2]={0};
  
    // two indexes used to find positions in result
    int idx1 = 0;  
    int idx2 = 0;  
      
    // look at the large_number from right to left
    for (int i=L1-1; i>=0; i--) 
    { 
        int carry = 0; 
        int d1 = large_number[i] - '0'; 
  
        // to shift left after every digit multiplication in multiplier 
        idx2 = 0;  
          
        // right to left in multiplier           
        for (int j=L2-1; j>=0; j--)
        { 
            // current digit of multiplier
            int d2 = multiplier[j] - '0'; 
   
            int sum = d1*d2 + result[idx1 + idx2] + carry; 
  
            // carry for next iteration 
            carry = sum/10; 
            result[idx1 + idx2] = sum % 10; 
            idx2++; 
        } 
        // add carry to next position 
        if (carry > 0) 
            result[idx1 + idx2] += carry; 
  
        // shift to left after every digit multiplication in large_number
        idx1++; 
    } 
  
    // ignore '0' from the right
    int i = L1 + L2 - 1;
    while (i>=0 && result[i] == 0) 
    i--; 
  
    // if all are '0', mul result is 0
    if (i == -1) 
    return "0"; 
  
    string s = ""; 
        
    while (i >= 0) 
       { s += to_string(result[i--]); 
     } 
    return s; 
} 

string div(string large_number, int divisor) 
{ 
    string result; 
    int idx = 0;
    int temp = large_number[idx] - '0'; 
    while (temp < divisor){
            temp = temp * 10 + (large_number[++idx] - '0'); 
        }
    while (large_number.size() > idx) {  
        result += (temp / divisor) + '0'; 
        temp = (temp % divisor) * 10 + large_number[++idx] - '0'; 
    } 
    if (result.length() == 0) 
        return "0"; 
    return result; 
} 


int main(){
    int n;
    cin >> n;
    int a;
    int b;
    cin >> a;
    cin >> b;
    vector<pair<int,int>> A(n);
    for (int i=0; i<n; i++){
        pair<int,int> p;
        cin >> p.first;
        cin >> p.second;
        A[i] = p;
    }
    sort(A.begin(), A.end(), comp_pair);

    // after sorting the pairs in the way described above,
    // find the largest S, which will be the S_{min} we are looking for
    string S_max = "0";
    string accum = to_string(a);
    for (int i=0; i<n; i++){
        string temp = div(accum, A[i].second);
        if (left_small(S_max,temp)){
            S_max = temp;
        }
        accum = mul(accum, to_string(A[i].first));
    }
    cout << S_max;
    return 0;
}
