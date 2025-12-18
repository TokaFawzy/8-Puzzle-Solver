#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <chrono>
#include <iomanip>
#include<unordered_set>
using namespace std;

/* ---------- Global Variables ---------- */
vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

/* ---------- Check Goal State ---------- */
bool isGoal(vector<vector<int>> &state) {
    return state == goal;
}

/* ---------- Convert State to String ---------- */
string stateToString(vector<vector<int>> &state) {
    string s = "";
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            s += char(state[i][j] + '0');
    return s;
}

/* ---------- Find Blank Position ---------- */
pair<int,int> findBlank(vector<vector<int>> &state) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(state[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

/* ---------- Generate Children States ---------- */
vector<vector<vector<int>>> getChildren(vector<vector<int>> &state) {
    vector<vector<vector<int>>> children;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    pair<int, int> blank = findBlank(state);
    int x = blank.first;
    int y = blank.second;

    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[nx][ny]);
            children.push_back(newState);
        }
    }
    return children;
}

/* ---------- Depth Limited Search ---------- */
bool DLS(vector<vector<int>> state, int depth, int limit,
         vector<vector<vector<int>>> &path,
         unordered_set<string> &visited) {

    string key = stateToString(state);

    if(visited.count(key))
        return false;

    visited.insert(key);
    path.push_back(state);

    if(isGoal(state))
        return true;

    if(depth == limit) {
        path.pop_back();
        return false;
    }

    auto children = getChildren(state);
    for(auto child : children) {
        if(DLS(child, depth + 1, limit, path, visited))
            return true;
    }

    path.pop_back(); // Backtracking
    return false;
}

/* ---------- Iterative Deepening Search ---------- */
vector<vector<vector<int>>> IDS(vector<vector<int>> initial) {
    int limit = 0;

    while(true) {
        vector<vector<vector<int>>> path;
        unordered_set<string> visited;

        if(DLS(initial, 0, limit, path, visited))
            return path;

        limit++;
    }
}

/* ---------- Print State ---------- */
void printState(vector<vector<int>> &state) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(state[i][j] == 0)
                cout << ". ";
            else
                cout << state[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

/* ---------- Main ---------- */
int main() {
        auto start_time = chrono::high_resolution_clock::now();

    vector<vector<int>> initial = {
        {1, 2, 3},
        {0, 4, 6},
        {7, 5, 8}
    };

    auto solution = IDS(initial);

    cout << "Solution Steps:\n";
    for(auto state : solution)
        printState(state);

    cout << "Solution Depth = " << solution.size() - 1 << endl;
            auto end_time = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> duration = end_time - start_time;
            cout << "Time taken: " <<fixed << setprecision(2) <<duration.count() << " ms" << endl;
    return 0;
}