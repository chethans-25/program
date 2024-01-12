#include <iostream>
using namespace std;
int adj[8][2] = {{1,0}, {-1,0), (0, 1), (0, 1), (1,1), (1, 1), (-1,1), (-1,-1)); char grid[1001][1001];
string s;
int n,m;
int fun(int i,int j,int k, int p){

if (k==s.size())
{return 1;}
if((i<0) or (i>=n) or (j<0) or (j>=m))
{
return 0;
}
if(grid[i][j] != s[k])
return false;

int ans = 0;


int newx = i + adj[p][0];
int newy j + adj[p][1];
ans += fun(newx, newy, k+1, p);

return ans;
}


int countoccurrence(int n, string grid[], string word) {
int count=0;
// WRITE YOUR CODE HERE
return count;
}
int main()