// Last modified: May 2, 2021
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// The idea is to store the start and end of each series of consecutive integers. This way of storage ensures that
// when several serieses are expecting for the same 'next number', the series starts earlier (stored earlier) is longer
// -> first, sort the inputs. store the unique numbers and the number of times they appear
// second, let the smallest unique number(s) be the start(s)
// third, for each of the remaining unique number k, compare its value with that of the previous unique number k'
// if not consecutive, each k' is an end and each k is a start
// if consecutive, if num(k')>num(k), k' is an end for num(k')-num(k) times
// if num(k')<num(k), k is a head for num(k)-num(k') times
// fourth, let the largest unique number(s) be the end(s)

int main(){
    int n;
    cin >> n;
    vector<int> set(n,0);
    for (int i=0; i<n; i++){
        cin >> set[i];
    }
    sort(set.begin(),set.end());

    vector<int> unique; // unique numbers in set
    vector<int> occurence; // number of occurence of each unique number
    int idx=0;

    unique.push_back(set[0]); // add the first element in the set to unique
	occurence.push_back(1);

	for(int i=1; i<n; i++){
		if (set[i]!=set[i-1]){
			idx++;
			unique.push_back(set[i]);
			occurence.push_back(1);
		}
		else{
			occurence[idx]+=1;
		}
    }
    vector<int> head;
    vector<int> tail;

    // the smallest unique number k is head for num(k) times
    for (int o=0; o<occurence[0]; o++) head.push_back(unique[0]);

    for (int i=1; i<unique.size(); i++){
        // if next number is not consecutive
        if (unique[i]-unique[i-1]!=1){
            for (int o=0; o<occurence[i]; o++) head.push_back(unique[i]);
            for (int o=0; o<occurence[i-1]; o++) tail.push_back(unique[i-1]);
        }
        // if consecutive
        else{
            int diff = occurence[i] - occurence[i-1];
            if (diff>0){
                for (int j=0; j<diff; j++) head.push_back(unique[i]);
            }
            else{
                for (int j=0; j<-diff; j++) tail.push_back(unique[i-1]);
            }
        }
    }
    // the largest unique number k is end for num(k) times
    for (int o=0; o<occurence[occurence.size()-1]; o++) tail.push_back(unique[unique.size()-1]);
    
    // calculate the minimum length of the partitions
    int minL = n;
    for (int i=0; i<head.size(); i++){
        int l = tail[i] - head[i] + 1;
        if (l < minL) minL = l;
    }
    cout << minL;

    // for (int i: head){
    //     cout << i << " ";
    // }
    // cout << endl;
    // for (int i: tail){
    //     cout << i << " ";
    // }
    return 0;
}
