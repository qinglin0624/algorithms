// Last modified: May 1, 2021
#include <iostream>
using namespace std;

// The idea is to first use dfs to test whether all the plants can be irrigated. If not, print 0 directly.
// If so, then calculate the minimum number of necessary well.
// -> store the left most and right most plant each well can irrigate. Since each well can irrigate continuous
// plants, the range of each well's irrigation is a line segment. Then, this problem requires us to find the 
// optimal way of covering a line segment of length m given a set of line segments.
// reference: https://www.cnblogs.com/zbtrs/p/5718959.html

int n;
int m;

// (the arrays are not using the position of index 0 for easier programming)
int area[501][501]; // elevation level of each grid.
bool visited[501][501]; // whether a grid has been visited
int lm[501]; // left limit of each well's irrigation range
int rm[501]; // right limit of each well's irrigation range
int f[501];

void visit(int x,int y)
{
    if (visited[x][y]) return;
    visited[x][y] = true;
    if (x+1<=n && area[x][y] > area[x+1][y]) visit(x+1,y); // go down
    if (x-1>=1 && area[x][y] > area[x-1][y]) visit(x-1,y); // go up
    if (y+1<=m && area[x][y] > area[x][y+1]) visit(x,y+1); // go right
    if (y-1>=1 && area[x][y] > area[x][y-1]) visit(x,y-1); // go left
    return;
}

void find_lm(int plant, int x, int y){
    if (visited[x][y]) return;
    visited[x][y] = true;
    if (x==1) lm[y] = plant;

    if (x+1<=n && area[x][y] < area[x+1][y]) find_lm(plant,x+1,y); // go down
    if (x-1>=1 && area[x][y] < area[x-1][y]) find_lm(plant,x-1,y); // go up
    if (y+1<=m && area[x][y] < area[x][y+1]) find_lm(plant,x,y+1); // go right
    if (y-1>=1 && area[x][y] < area[x][y-1]) find_lm(plant,x,y-1); // go left
    return;
}

void find_rm(int plant, int x, int y){
    if (visited[x][y]) return;
    visited[x][y] = true;
    if (x==1) rm[y] = plant;
    
    if (x+1<=n && area[x][y] < area[x+1][y]) find_rm(plant,x+1,y); // go down
    if (x-1>=1 && area[x][y] < area[x-1][y]) find_rm(plant,x-1,y); // go up
    if (y+1<=m && area[x][y] < area[x][y+1]) find_rm(plant,x,y+1); // go right
    if (y-1>=1 && area[x][y] < area[x][y-1]) find_rm(plant,x,y-1); // go left
    return;
}

int main(){
    cin >> n;
    cin >> m;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> area[i][j];
        }
    }
    // initialize lm and f with a value > 500
    for (int i=0; i<501; i++){
        lm[i]=501;
        f[i]=501;
    }
    // first, starting from each well, test whether in the end all the plants are irrigated
    for (int i=1; i<=m; i++){
        visit(1,i);
    }
    int not_irrigatable = 0;
    for (int i=1; i<=m; i++){
         if (!visited[n][i]) not_irrigatable ++;
    }
    if (not_irrigatable != 0) {
        cout << 0 << endl << not_irrigatable;
        return 0;
    }

    // if all the plants are irrigatable
    // clear visited
    for (int i=0; i<=500; i++){
        for (int j=0; j<=500; j++){
            visited[i][j]=0;
        }
    }
    // find left limit
    for (int plant=1; plant<=m; plant++){
        find_lm(plant, n, plant);
    }
    // clear visited
    for (int i=0; i<=500; i++){
        for (int j=0; j<=500; j++){
            visited[i][j]=0;
        }
    }
    // find right limit
    for (int plant=m; plant>=1; plant--){
        find_rm(plant, n, plant);
    }

    f[0] = 0;
    for (int i=1; i<=m; i++){
         for (int j=1; j<=m; j++){
             if (lm[j]<=i && rm[j]>=i){ // if the plant i can be irrigated by well j
                f[i] = min(f[i], f[lm[j] - 1] + 1);
            }
        }
    }
    cout << 1 << endl << f[m];
    return 0;
}
