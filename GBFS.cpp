#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;

const int PUZZLE_SIZE = 3;

struct PuzzleNode {
    vector<vector<int>> state;
    int h_cost;
    int blank_row, blank_col;
    PuzzleNode* parent;
    string move;

    PuzzleNode(vector<vector<int>> s, int br, int bc, PuzzleNode* p = nullptr, string m = "")
        : state(s), blank_row(br), blank_col(bc), parent(p), move(m) {
        h_cost = calculate_misplaced_tiles();
    }

    int calculate_misplaced_tiles() const {
        int misplaced = 0;
        vector<vector<int>> goal = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };

        for (int i = 0; i < PUZZLE_SIZE; ++i) {
            for (int j = 0; j < PUZZLE_SIZE; ++j) {
                if (state[i][j] != 0 && state[i][j] != goal[i][j]) {
                    misplaced++;
                }
            }
        }
        return misplaced;
    }

    bool is_goal() const {
        return h_cost == 0;
    }
};

struct CompareNodes {
    bool operator()(const PuzzleNode* a, const PuzzleNode* b) {
        return a->h_cost > b->h_cost;
    }
};

void print_path(const PuzzleNode* goal_node) {
    if (goal_node == nullptr) return;

    vector<const PuzzleNode*> path;
    const PuzzleNode* current = goal_node;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    reverse(path.begin(), path.end());

    cout << "\n========================================" << endl;
    cout << "SOLVED (Greedy Best-First Search)" << endl;
    cout << "========================================" << endl;

    for (size_t i = 0; i < path.size(); ++i) {
        cout << "Step " << i << " (" << path[i]->move << ") | H=" << path[i]->h_cost << endl;
        for (int r = 0; r < PUZZLE_SIZE; ++r) {
            for (int c = 0; c < PUZZLE_SIZE; ++c) {
                if (path[i]->state[r][c] == 0) cout << setw(3) << "-";
                else cout << setw(3) << path[i]->state[r][c];
            }
            cout << endl;
        }
    }
    cout << "========================================" << endl;
    cout << "Total Steps: " << path.size() - 1 << endl;
}

void greedy_best_first_search(const vector<vector<int>>& initial_state, int br, int bc) {
    auto start_time = chrono::high_resolution_clock::now();

    priority_queue<PuzzleNode*, vector<PuzzleNode*>, CompareNodes> open_list;
    map<vector<vector<int>>, bool> visited_states;

    PuzzleNode* start_node = new PuzzleNode(initial_state, br, bc);
    open_list.push(start_node);
    visited_states[initial_state] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    string moves[] = {"UP", "DOWN", "LEFT", "RIGHT"};

    while (!open_list.empty()) {
        PuzzleNode* current_node = open_list.top();
        open_list.pop();

        if (current_node->is_goal()) {
            auto end_time = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> duration = end_time - start_time;
            
            print_path(current_node);
            cout << "Execution Time: " << fixed << setprecision(2) << duration.count() << " ms" << endl;
            return;
        }

        int r = current_node->blank_row;
        int c = current_node->blank_col;

        for (int i = 0; i < 4; ++i) {
            int new_r = r + dr[i];
            int new_c = c + dc[i];

            if (new_r >= 0 && new_r < PUZZLE_SIZE && new_c >= 0 && new_c < PUZZLE_SIZE) {
                vector<vector<int>> new_state = current_node->state;
                swap(new_state[r][c], new_state[new_r][new_c]);

                if (visited_states.find(new_state) == visited_states.end()) {
                    PuzzleNode* new_node = new PuzzleNode(new_state, new_r, new_c, current_node, moves[i]);
                    open_list.push(new_node);
                    visited_states[new_state] = true;
                }
            }
        }
    }
                auto end_time = chrono::high_resolution_clock::now();
            chrono::duration<double, std::milli> duration = end_time - start_time;
            cout << "Execution Time: " << fixed << setprecision(2) << duration.count() << " ms" << endl;

    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> initial_state = {
        {1, 2, 3},
        {0, 4, 6},
        {7, 5, 8}
    };;//{{8, 6, 7}, {2, 5, 4}, {3, 0, 1}}
    
    int blank_row = 1;
    int blank_col = 0; 

    greedy_best_first_search(initial_state, blank_row, blank_col);

    return 0;
}
