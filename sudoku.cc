#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 9;

FILE *file;

int A[N][N];

bool candidate[N][N][10];

const int dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

const int dir[9][9] = {
{8, 7, 6, 8, 7, 6, 8, 7, 6},
{5, 4, 3, 5, 4, 3, 5, 4, 3},
{2, 1, 0, 2, 1, 0, 2, 1, 0},
{8, 7, 6, 8, 7, 6, 8, 7, 6},
{5, 4, 3, 5, 4, 3, 5, 4, 3},
{2, 1, 0, 2, 1, 0, 2, 1, 0},
{8, 7, 6, 8, 7, 6, 8, 7, 6},
{5, 4, 3, 5, 4, 3, 5, 4, 3},
{2, 1, 0, 2, 1, 0, 2, 1, 0}
};

void input_sudoku() {
    char buf[100];
    fscanf(file, "%s", buf);
    fscanf(file, "%s", buf);
    for (int i = 0; i < N; ++ i) {
        fscanf(file, "%s", buf);
        for (int j = 0; j < N; ++ j)
            A[i][j] = buf[j] - '0';
    }
}

typedef pair< pair<int, int>, int > Delta;
#define make_delta(X,Y,Z)   make_pair(make_pair((X),(Y)),(Z))

void find_candidate() {
    memset(candidate, true, sizeof(candidate));
    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y)
            if (A[x][y] == 0) {
                for (int i = 0; i < N; ++ i) {
                    candidate[x][y][A[x][i]] = false;
                    candidate[x][y][A[i][y]] = false;
                }
                int xx = x + dx[dir[x][y]];
                int yy = y + dy[dir[x][y]];
                for (int i = 0; i < 9; ++ i)
                    candidate[x][y][A[xx + dx[i]][yy + dy[i]]] = false;
            }
}

void update_candidate(const Delta &delta) {
    int x = delta.first.first;
    int y = delta.first.second;
    int k = delta.second;

    for (int i = 0; i < N; ++ i) {
        if (A[x][i] == 0)
            candidate[x][i][k] = false;
        if (A[i][y] == 0)
            candidate[i][y][k] = false;
    }
    int xx = x + dx[dir[x][y]];
    int yy = y + dy[dir[x][y]];
    for (int i = 0; i < 9; ++ i) {
        int xxx = xx + dx[i];
        int yyy = yy + dy[i];
        if (A[xxx][yyy] == 0)
            candidate[xxx][yyy][k] = false;
    }
}

Delta update_sudoku() {
    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y)
            if (A[x][y] == 0) {
                int count = 0;
                int k;
                for (int i = 1; i <= 9; ++ i)
                    if (candidate[x][y][i]) {
                        ++ count;
                        k = i;
                    }
                if (count == 1) {
                    A[x][y] = k;
                    return make_delta(x, y, k);
                }
            }
    return make_delta(-1, -1, -1);
}

void print_sudoku() {
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j)
            printf("%d", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

inline void recovery(const vector<Delta> &lst) {
    for (int i = 0; i < lst.size(); ++ i) {
        int x = lst[i].first.first;
        int y = lst[i].first.second;
        A[x][y] = 0;
    }
    find_candidate();
}

bool dfs() {
    // deduction
    vector<Delta> backtrack;
    find_candidate();
    while (1) {
        //print_sudoku();
        Delta k = update_sudoku();
        if (k.second == -1)
            break;
        else
            backtrack.push_back(k);
        update_candidate(k);
    }


    vector<int> C;
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (A[i][j] == 0) {
                for (int k = 1; k <= 9; ++ k)
                    if (candidate[i][j][k])
                        C.push_back(k);
                if (C.empty()) {
                    recovery(backtrack);
                    return false;
                }

                for (int k = 0; k < C.size(); ++ k) {
                    A[i][j] = C[k];
                    if (dfs()) return true;
                }

                A[i][j] = 0;
                recovery(backtrack);
                return false;
            }
    return true;
}

int solve_sudoku() {
    if (!dfs()) {
        printf("Error!\n");
        print_sudoku();
        return -1;
    }

    return A[0][0] * 100 + A[0][1] * 10 + A[0][2];
}

int main() {
    int test = 50;

    int ans = 0;

    file = fopen("sudoku.txt", "r");
    while (test --) {
        input_sudoku();
        ans += solve_sudoku();
    }
    fclose(file);

    cout << ans << endl;
    return 0;    
}