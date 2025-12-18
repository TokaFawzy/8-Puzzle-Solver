#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <chrono>
#include <iomanip>
using namespace std;

int steps=0;
void printState(vector<int> s) {
    for (int i = 0; i < 9; i++) {
        cout << s[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    steps+=1;
    cout << "--------\n";
}

vector<vector<int>> getNextStates(vector<int> state) {
    vector<vector<int>> nextStates;

    int zeroPos;
    for (int i = 0; i < 9; i++)
        if (state[i] == 0)
            zeroPos = i;

    int row = zeroPos / 3;
    int col = zeroPos % 3;

    int dr[4] = {-1, 1, 0, 0}; // Up, Down
    int dc[4] = {0, 0, -1, 1}; // Left, Right

    for (int i = 0; i < 4; i++) {
        int newRow = row + dr[i];
        int newCol = col + dc[i];

        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            vector<int> newState = state;
            swap(newState[row * 3 + col],
                 newState[newRow * 3 + newCol]);
            nextStates.push_back(newState);
        }
    }

    return nextStates;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
    vector<int> start = {
        1, 2, 3,
        0, 4, 6,
        7, 5, 8
    };
    //{{8, 6, 7}, {2, 5, 4}, {3, 0, 1}}

    vector<int> goal = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
    };

    queue<vector<int>> q;
    set<vector<int>> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        vector<int> current = q.front();
        q.pop();

        printState(current);

        if (current == goal) {
            auto end_time = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> duration = end_time - start_time;
            cout << "Goal Reached!\n";
            cout<<"the number of steps is : "<<steps <<"\n";
            cout << "Time taken: " <<fixed << setprecision(2) <<duration.count() << " ms" << endl;
            return 0;
        }

        vector<vector<int>> nextStates = getNextStates(current);

        for (auto s : nextStates) {
            if (visited.find(s) == visited.end()) {
                visited.insert(s);
                q.push(s);
            }
        }
    }

    cout << "No Solution Found\n";
    return 0;
}