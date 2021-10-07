// Last modified: March 24, 2021
#include <iostream>

using namespace std;

int costReference[] = {6,2,5,5,4,5,6,3,7,6,6};

int getCost(int num){
    // return the cost of each digit of the number
    if (num < 10) return costReference[num];
    if (num < 100) return (costReference[(num/10)%10] + costReference[num%10]);
    else return (costReference[(num/100)%10] + costReference[(num/10)%10] + costReference[num%10]);
}

int main(){
    int power;
    cin >> power;
    power -= 4; // minus the power used by + and =
    int foundEquations = 0;

    // since the largest usuable power will be 20, it A and B can only be three-digit numbers.
    // It can be verified by the equation 1111 + 1 = 1112, whose cost is 21. It gives the smallest
    // cost for an equation involving a four-digit number.

    for (int i=0; i<1000; i++){
        for (int j=0; j<1000; j++){
            int cost = getCost(i) + getCost(j) + getCost(i+j); // cost of A + cost of B + cost of C
            if (cost==power) foundEquations++;
        }
    }
    cout << foundEquations;
    return 0;
}
