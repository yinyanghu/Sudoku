#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <utility>
#include <functional>
//#include <unordered_map>
//#include <unordered_set>

using namespace std;

/*
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

struct Point {
    int x, y;
    Point(): x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
*/


/*
struct DLX {
    int x, y;
    struct DLX  *left, *right;
};
        struct DLX  *dlx;
    dlx = new struct DLX;
    dlx->left = dlx->right = dlx;
    dlx->x = dlx->y = -1;
*/

const int n = 9;

class Solution {
    public:
        void solveSudoku(vector< vector<char> > &board);
    private:
        int B[n][n];
        vector< pair<int, int> > unknown;
        bool rowFlag[n][n];
        bool columnFlag[n][n];
        bool cellFlag[n][n];
        void dfs(int k);
        bool found;
};

void Solution::dfs(int k) {
    if (k == unknown.size()) {
        found = true;
        return;
    }
    int x = unknown[k].first;
    int y = unknown[k].second;
    int cell = (x / 3) * 3 + y / 3;
    for (int i = 0; i < n; ++ i)
        if (rowFlag[x][i] && columnFlag[y][i] && cellFlag[cell][i]) {
            B[x][y] = i;
            rowFlag[x][i] = columnFlag[y][i] = cellFlag[cell][i] = false;
            dfs(k + 1);
            if (found) return;
            rowFlag[x][i] = columnFlag[y][i] = cellFlag[cell][i] = true;
        }
}

void Solution::solveSudoku(vector< vector<char> > &board) {
    memset(rowFlag, true, sizeof(rowFlag));
    memset(columnFlag, true, sizeof(columnFlag));
    memset(cellFlag, true, sizeof(cellFlag));
    found = false;

    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            if (board[i][j] == '.')
                unknown.push_back(make_pair(i, j));
            else {
                B[i][j] = board[i][j] - '1';
                rowFlag[i][B[i][j]] = false;
                columnFlag[j][B[i][j]] = false;
                cellFlag[(i / 3) * 3 + j / 3][B[i][j]] = false;
            }
    dfs(0);
    if (!found)
        cout << "tina" << endl;
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            board[i][j] = (char)(49 + B[i][j]);
}

vector<char> convert(string s) {
    vector<char> ret;
    for (int i = 0; i < s.size(); ++ i)
        ret.push_back(s[i]);
    return ret;
}

Solution test;

int main() {
    vector< vector<char> > board;
    board.push_back(convert("53..7...."));
    board.push_back(convert("6..195..."));
    board.push_back(convert(".98....6."));
    board.push_back(convert("8...6...3"));
    board.push_back(convert("4..8.3..1"));
    board.push_back(convert("7...2...6"));
    board.push_back(convert(".6....28."));
    board.push_back(convert("...419..5"));
    board.push_back(convert("....8..79"));
    test.solveSudoku(board);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j)
            cout << board[i][j];
        cout << endl;
    }
    return 0;
}
