#ifndef DFSSOLVER_H
#define DFSSOLVER_H
#include <iostream>
#include <vector>
#include <unordered_set>
#include "../Modal/GenericRubiksCube.h"
using namespace std;

template <typename CubeType, typename HashMapType>
class DFSSolver {
public:
    CubeType rubiksCube;

private:
    vector<MOVE> moves;
    int max_initial_depth;
    unordered_set<CubeType, HashMapType> visited;

    // Helper method to convert move to string for debugging
    string moveToString(MOVE move) {
        switch(move) {
            case MOVE::F: return "F";
            case MOVE::F2: return "F2";
            case MOVE::FPRIME: return "F'";
            case MOVE::U: return "U";
            case MOVE::U2: return "U2";
            case MOVE::UPRIME: return "U'";
            case MOVE::R: return "R";
            case MOVE::R2: return "R2";
            case MOVE::RPRIME: return "R'";
            case MOVE::L: return "L";
            case MOVE::L2: return "L2";
            case MOVE::LPRIME: return "L'";
            case MOVE::B: return "B";
            case MOVE::B2: return "B2";
            case MOVE::BPRIME: return "B'";
            case MOVE::D: return "D";
            case MOVE::D2: return "D2";
            case MOVE::DPRIME: return "D'";
            default: return "Unknown";
        }
    }

    // DFS code to find the solution (helper function)
    bool dfs(int dep, int max_depth) {
        // If the cube is already solved, return true
        if (rubiksCube.isSolved()) {
            cout << "Solution found at depth " << dep << endl;
            return true;
        }

        // If the current depth exceeds the max depth, stop the search
        if (dep > max_depth) {
            return false;
        }

        // Avoid revisiting states
        if (visited.find(rubiksCube) != visited.end()) {
            return false;
        }
        visited.insert(rubiksCube);

        // Try all possible moves
        for (int i = 0; i < 18; i++) {
            MOVE currentMove = static_cast<MOVE>(i);

            // Apply the move
            rubiksCube.move(currentMove);
            moves.push_back(currentMove);

            // Recursively search
            if (dfs(dep + 1, max_depth)) {
                return true;
            }

            // Backtrack
            moves.pop_back();
            rubiksCube.invert(currentMove);
        }

        return false;
    }

public:
    // Constructor
    DFSSolver(CubeType& cube, int max_depth = 20) :
        rubiksCube(cube),
        max_initial_depth(max_depth) {}

    // Solve method with iterative deepening
    vector<MOVE> solve() {
        // Try increasing depths
        for (int depth = 1; depth <= max_initial_depth; depth++) {
            cout << "Trying depth: " << depth << endl;

            // Clear previous moves and visited states
            moves.clear();
            visited.clear();

            // Start DFS solving
            if (dfs(0, depth)) {
                // Print solution moves
                cout << "Solution found at depth " << depth << endl;
                cout << "Solution moves (" << moves.size() << " moves): ";
                for (MOVE move : moves) {
                    cout << moveToString(move) << " ";
                }
                cout << endl;

                return moves;
            }
        }

        std::cout << "No solution found within max depth of " << max_initial_depth << std::endl;
        return {};
    }
};

#endif // DFSSOLVER_H