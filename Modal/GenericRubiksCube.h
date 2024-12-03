//
// Created by Harshit Kumar Yadav on 01/12/24.
//

#ifndef GENERICRUBICSCUBE_H
#define GENERICRUBICSCUBE_H
#include<iostream>
#include <vector>
using namespace std;

enum class COLOR{
    WHITE,
    GREEN,
    RED,
    BLUE,
    ORANGE,
    YELLOW
};
enum class FACE {
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    UP = 4,
    DOWN = 5
};
enum class MOVE {
    L, LPRIME, L2,
    R, RPRIME, R2,
    U, UPRIME, U2,
    D, DPRIME, D2,
    F, FPRIME, F2,
    B, BPRIME, B2
};

// abstract class to define the generic Rubik'sCube class
class GenericRubiksCube {
    public:
    //virtual destructor
    virtual ~GenericRubiksCube()= default;
    //Pure virtual function to make it Abstract class.
    //used unsigned to tell the compiler the variable can only store non-negative values
    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0; // virtual hai to usko derived class m implement krenge

    static  char getColorLetter(COLOR color);

    virtual bool isSolved() const =0;

    static string getMove(MOVE ind);

    void printCube() const;

    GenericRubiksCube &move(MOVE ind);

    vector<MOVE> randomShuffleCube(unsigned int times);

    GenericRubiksCube &invert(MOVE ind);

    //Moves
    //We have to mak changes in the same cube, that's why we are passing it as a reference
    virtual GenericRubiksCube& f() =0; // Front clockwise
    virtual GenericRubiksCube& fPrime() = 0;  // Front counter-clockwise
    virtual GenericRubiksCube& f2() =0; // Front 180-degree turn

    virtual GenericRubiksCube& u() = 0; //Up clockwise
    virtual GenericRubiksCube& uPrime() = 0; //Up counter-Clockwise
    virtual GenericRubiksCube& u2() =0; // Up 180-degree turn

    virtual GenericRubiksCube& l() =0; //left clockwise
    virtual GenericRubiksCube& lPrime() = 0; //left - counter-clockwise
    virtual GenericRubiksCube& l2() =0; //left 180-degree turn

    virtual GenericRubiksCube& r() = 0;       // Right clockwise
    virtual GenericRubiksCube& rPrime() = 0;  // Right counter-clockwise
    virtual GenericRubiksCube& r2() = 0;      // Right 180-degree turn

    virtual GenericRubiksCube& b() = 0;       // Back clockwise
    virtual GenericRubiksCube& bPrime() = 0;  // Back counter-clockwise
    virtual GenericRubiksCube& b2() = 0;      // Back 180-degree turn

    virtual GenericRubiksCube& d() = 0;       // Down clockwise
    virtual GenericRubiksCube& dPrime() = 0;  // Down counter-clockwise
    virtual GenericRubiksCube& d2() = 0;      // Down 180-degree turn



};



#endif //GENERICRUBICSCUBE_H
