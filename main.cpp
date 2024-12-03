#include <iostream>
#include <vector>
#include <unordered_map>
#include "Modal/GenericRubiksCube.h"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Modal/RubiksCube3dArray.h"

using namespace std;

int main() {
    RubiksCube3dArray object3DArray;

    cout<<"Initial Cube"<<endl;
    object3DArray.printCube();
    // Shuffle the cube and print the scramble moves
    vector<MOVE> shuffle_moves = object3DArray.randomShuffleCube(2);

    cout << "Scramble Moves: ";
    for (auto move : shuffle_moves) {
        cout << object3DArray.getMove(move) << " ";
    }
    cout << "\n";
    object3DArray.printCube();

    //DFS---------------------------------------------------------------------------------------------------------------
    // Initialize DFS Solver with RubiksCube3dArray and its hash function
    // DFSSolver<RubiksCube3dArray, RubiksCube3dArray::Hash3D> dfsSolver(object3DArray, 10);
    // auto solution = dfsSolver.solve();

    //BFS---------------------------------------------------------------------------------------------------------------
    BFSSolver<RubiksCube3dArray, RubiksCube3dArray::Hash3D> bfsSolver(object3DArray);
    auto  solution = bfsSolver.solve();


    // Apply the solution moves
    for (auto move : solution) {
        object3DArray.move(move);
    }

    // Print the solved cube
    cout << "\nSolved Cube:" << endl;
    object3DArray.printCube();

    // Verify if the cube is solved
    if (object3DArray.isSolved()) {
        cout << "Cube is successfully solved!" << endl;
    } else {
        cout << "Cube solving failed." << endl;
    }

    return 0;
}