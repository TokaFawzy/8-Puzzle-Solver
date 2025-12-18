#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <map>
#include <chrono>
#include <iomanip>
using namespace std;

//A* Algorithm
const int N = 3;

vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

int target_x[9], target_y[9];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct Node {
    vector<vector<int>> state;
    int x, y, g, h, f;
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

int manhattan(const vector<vector<int>>& s) {
    int dist = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = s[i][j];
            if (val != 0) {
                // i/j --> invalid row/colum number (position in initial state)
                // target_x[val]/target_y[val] --> valid row/colum number (position in goal state)
                dist += abs(i - target_x[val]) + abs(j - target_y[val]);
            }
        }
    }
    return dist;
}

void printState(const vector<vector<int>>& s) {
    for (auto &row : s) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    cout << "------\n";
}

void AStar(vector<vector<int>> start, int x, int y) {
    auto start_time = chrono::high_resolution_clock::now();//start 
    //Save elements positions in goal state
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = goal[i][j];
            //go to val index and save position [i][j]=> val[i][j]
            target_x[val] = i;
            target_y[val] = j;
        }
    }
    //less f in the top
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    //prevent infinite loop
    set<vector<vector<int>>> visited; 
    //start point
    Node root = {start, x, y, 0, manhattan(start), 0};
    root.f = root.g + root.h;
    pq.push(root);

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        //check if current state not repeated
        if (visited.count(cur.state)) continue;
        visited.insert(cur.state);
        //goal test
        if (cur.h == 0) {
            auto end_time = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> duration = end_time - start_time;
            cout << "Goal Reached!\n";
            printState(cur.state);
            cout<<"Number of steps for reach g(n) = "<< cur.g << endl;
            cout << "Time taken: " << fixed << setprecision(2)<<duration.count() << " ms" << endl;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                //switch 0 with number (up-down-left-right)
                vector<vector<int>> next_state = cur.state;
                swap(next_state[cur.x][cur.y], next_state[nx][ny]);

                if (!visited.count(next_state)) {
                    int h = manhattan(next_state);
                    pq.push({next_state, nx, ny, cur.g + 1, h, cur.g + 1 + h}); //f(n)= new g(cur.g + 1) + h
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {0, 4, 6}, {7, 5, 8}};
    //{{8, 6, 7}, {2, 5, 4}, {3, 0, 1}}
    int x, y;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (start[i][j] == 0) { x = i; y = j; }
    AStar(start, x, y);
    return 0;
}