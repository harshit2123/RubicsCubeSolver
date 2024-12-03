//
// Created by Harshit Kumar Yadav on 03/12/24.
//

#ifndef BFSSOLVER_H
#define BFSSOLVER_H
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include "../Modal/GenericRubiksCube.h"
using namespace std;

template<class CubeType, typename HashMap>
class BFSSolver {
public:
    CubeType rubiksCube;

private:
    vector<MOVE> moves; // List of moves required to solve the cube
    unordered_map<CubeType, bool, HashMap> visited; // To track visited cube states
    unordered_map<CubeType, MOVE, HashMap> move_done; // Back-pointer map for solving the cube
    // Function to convert MOVE enum to a string
    string moveToString(MOVE move) {
        switch (move) {
            case MOVE::L: return "L";
            case MOVE::LPRIME: return "L'";
            case MOVE::L2: return "L2";
            case MOVE::R: return "R";
            case MOVE::RPRIME: return "R'";
            case MOVE::R2: return "R2";
            case MOVE::U: return "U";
            case MOVE::UPRIME: return "U'";
            case MOVE::U2: return "U2";
            case MOVE::D: return "D";
            case MOVE::DPRIME: return "D'";
            case MOVE::D2: return "D2";
            case MOVE::F: return "F";
            case MOVE::FPRIME: return "F'";
            case MOVE::F2: return "F2";
            case MOVE::B: return "B";
            case MOVE::BPRIME: return "B'";
            case MOVE::B2: return "B2";
            default: return "";
        }
    }

    // bfs() -> performs breadth-first-search and returns a solved Rubik's Cube
    // move_done[] -> Back-Pointer map that stores how we reached each state
    int depth=0;
    CubeType bfs() {
        queue<pair<CubeType, int>> q;  // Queue to store Cube and its associated depth
        q.push({rubiksCube, 0}); // Initial cube with depth 0
        visited[rubiksCube] = true; // Mark the initial cube as visited

        while (!q.empty()) {
            CubeType node = q.front().first;
            int depth = q.front().second;  // Get the current depth
            q.pop();
            depth++;
           // cout << "At depth " << depth << ": "; // Output the current depth
           // node.printCube(); // Optionally print the cube at this depth

            if (node.isSolved()) {
                return node; // Return the solved cube
            }

            // Try all 18 possible moves
            for (int i = 0; i < 18; i++) {
                MOVE curr_move = static_cast<MOVE>(i);
                node.move(curr_move); // Apply the move

                // If the resulting state has not been visited yet
                if (visited.find(node) == visited.end()) {
                    visited[node] = true; // Mark as visited
                    move_done[node] = curr_move; // Store the move that led to this state
                    q.push({node, depth + 1}); // Add the new state with increased depth to the queue
                }

                node.invert(curr_move); // Undo the move
            }
        }

        return rubiksCube; // Return the initial cube if no solution is found
    }

public:
    // Constructor to initialize the cube
    BFSSolver(CubeType _rubiksCube) {
        rubiksCube = _rubiksCube;
    }

    // Solve method to find the solution path
    vector<MOVE> solve() {
        // Perform BFS to find the solved cube
        CubeType solved_cube = bfs();
        assert(solved_cube.isSolved()); // Ensure the solved cube is indeed solved

        CubeType curr_cube = solved_cube;
        while (curr_cube != rubiksCube) {
            MOVE curr_move = move_done[curr_cube]; // Get the move that led to this state
            moves.push_back(curr_move); // Record the move
            curr_cube.invert(curr_move);
        }

        reverse(moves.begin(), moves.end());

        cout << "Final Depth: "<<depth<<endl;
        cout << "Solution moves: "<<endl;
        for (MOVE move : moves) {
            // You can replace the following line with your preferred move-to-string function
            cout << moveToString(move) << " ";
        }
        cout << endl;

        return moves;
    }
};
#endif // BFSSOLVER_H