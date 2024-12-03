//
// Created by Harshit Kumar Yadav on 01/12/24.
//

#ifndef RUBIKSCUBE3DARRAY_H
#define RUBIKSCUBE3DARRAY_H
#include<iostream>
using namespace std;
#include "GenericRubiksCube.h"


class RubiksCube3dArray : public GenericRubiksCube{
private:
    // x-face(0-5), y-(row-(0-2)), z-(column-(0-2))
    char cube[6][3][3]{};

    //Helper Function to rotate the face clockwise
    void rotateFace(int faceIndex) {
        char temp[3][3];
        // for (int i = 0; i < 3; i++) cube[ind][0][i] = temp_arr[2 - i][0];
        // for (int i = 0; i < 3; i++) cube[ind][i][2] = temp_arr[0][i];
        // for (int i = 0; i < 3; i++) cube[ind][2][2 - i] = temp_arr[i][2];
        // for (int i = 0; i < 3; i++) cube[ind][2 - i][0] = temp_arr[2][2 - i];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp[i][j] = cube[faceIndex][i][j];
            }
        }
        //Rotate the face
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                //first row - last col,
                //second - second,
                //third row - first col
                cube[faceIndex][i][2-i] = temp[i][j];
            }
        }
    }


    //Helper function to get color letter
    static char getColorLetter(COLOR color) {
        switch (color) {
            case COLOR::WHITE: return 'W';
            case COLOR::GREEN: return 'G';
            case COLOR::BLUE: return 'B';
            case COLOR::RED: return 'R';
            case COLOR::YELLOW: return 'Y';
            case COLOR::ORANGE: return 'O';
            default: return 'X';
        }
    }
public:
    //constructor initialization in public class
    RubiksCube3dArray() {
        //initializing each face with its color
        for (int face = 0; face < 6; face++) {
            for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        cube[face][i][j] = getColorLetter(COLOR(face));
                    }
            }
        }
    }

    // Get color of specific position //using virtual function - getColor from the abstract class
    //enum Face { FRONT = 0, BACK = 1, LEFT = 2, RIGHT = 3, TOP = 4, BOTTOM = 5 };
    COLOR getColor(FACE face, unsigned row, unsigned col) const   {
        char color = cube[int(face)][row][col];
        switch (color) {
            case 'W': return COLOR::WHITE;
            case 'G': return COLOR::GREEN;
            case 'R': return COLOR::RED;
            case 'B': return COLOR::BLUE;
            case 'O': return COLOR::ORANGE;
            case 'Y': return COLOR::YELLOW;
            default: return COLOR::WHITE;
        }
    }
    // Check if cube is solved
    //using virtual function - isSolved from the abstract class
    bool isSolved() const override {
        // Check if each face has same color
        for (int face = 0; face < 6; face++) {
            char color = cube[face][0][0];
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (cube[face][i][j] != color) return false;
                }
            }
        }
        return true;
    }

    GenericRubiksCube& f() override {
        rotateFace(static_cast<int>(FACE::FRONT));

        char temp[3];
        // Store the top edge of the UP face
        for (int i = 0; i < 3; i++) temp[i] = cube[static_cast<int>(FACE::UP)][2][i];

        // Move edges: Left → Top, Bottom → Left, Right → Bottom, Temp → Right
        for (int i = 0; i < 3; i++) {
            cube[static_cast<int>(FACE::UP)][2][i] = cube[static_cast<int>(FACE::LEFT)][2 - i][2];
            cube[static_cast<int>(FACE::LEFT)][2 - i][2] = cube[static_cast<int>(FACE::DOWN)][0][2 - i];
            cube[static_cast<int>(FACE::DOWN)][0][2 - i] = cube[static_cast<int>(FACE::RIGHT)][i][0];
            cube[static_cast<int>(FACE::RIGHT)][i][0] = temp[i];
        }

        return *this;
    }
    GenericRubiksCube& f2() override {
        this->f();
        this->f();
        return *this;
    }
    GenericRubiksCube& fPrime() override {
        this->f();
        this->f();
        this->f();
        return *this;
    }

    GenericRubiksCube& u() override {
        rotateFace(static_cast<int>(FACE::UP));

        char temp[3];
        // Store the back edge
        for (int i = 0; i < 3; i++) temp[i] = cube[static_cast<int>(FACE::BACK)][0][2 - i];

        // Move edges: Left → Back, Front → Left, Right → Front, Temp → Right
        for (int i = 0; i < 3; i++) {
            cube[static_cast<int>(FACE::BACK)][0][2 - i] = cube[static_cast<int>(FACE::LEFT)][0][2 - i];
            cube[static_cast<int>(FACE::LEFT)][0][2 - i] = cube[static_cast<int>(FACE::FRONT)][0][2 - i];
            cube[static_cast<int>(FACE::FRONT)][0][2 - i] = cube[static_cast<int>(FACE::RIGHT)][0][2 - i];
            cube[static_cast<int>(FACE::RIGHT)][0][2 - i] = temp[i];
        }

        return *this;
    }
    GenericRubiksCube& u2() override {
        this->u();
        this->u();
        return *this;
    }
    GenericRubiksCube& uPrime() override {
        this->u();
        this->u();
        this->u();
        return *this;
    }

    GenericRubiksCube& l() override {
        rotateFace(static_cast<int>(FACE::LEFT));

        char temp[3];
        // Store the front left edge
        for (int i = 0; i < 3; i++) temp[i] = cube[static_cast<int>(FACE::FRONT)][i][0];

        // Move edges: Down → Front, Back → Down, Up → Back, Temp → Up
        for (int i = 0; i < 3; i++) {
            cube[static_cast<int>(FACE::FRONT)][i][0] = cube[static_cast<int>(FACE::DOWN)][i][0];
            cube[static_cast<int>(FACE::DOWN)][i][0] = cube[static_cast<int>(FACE::BACK)][2 - i][2];
            cube[static_cast<int>(FACE::BACK)][2 - i][2] = cube[static_cast<int>(FACE::UP)][i][0];
            cube[static_cast<int>(FACE::UP)][i][0] = temp[i];
        }

        return *this;
    }
    GenericRubiksCube& l2() override {
        this->l();
        this->l();
        return *this;
    }
    GenericRubiksCube& lPrime() override {
        this->l();
        this->l();
        this->l();
        return *this;
    };

    GenericRubiksCube& r() override {
        rotateFace(static_cast<int>(FACE::RIGHT));

        char temp[3];
        // Store the front edge
        for (int i = 0; i < 3; i++) temp[i] = cube[static_cast<int>(FACE::FRONT)][i][2];

        // Move edges: Down → Front, Back → Down, Up → Back, Temp → Up
        for (int i = 0; i < 3; i++) {
            cube[static_cast<int>(FACE::FRONT)][i][2] = cube[static_cast<int>(FACE::DOWN)][i][2];
            cube[static_cast<int>(FACE::DOWN)][i][2] = cube[static_cast<int>(FACE::BACK)][2 - i][0];
            cube[static_cast<int>(FACE::BACK)][2 - i][0] = cube[static_cast<int>(FACE::UP)][i][2];
            cube[static_cast<int>(FACE::UP)][i][2] = temp[i];
        }

        return *this;
    }
    GenericRubiksCube& r2() override {
        this->r();
        this->r();
        return *this;
    }
    GenericRubiksCube& rPrime() override {
        this->r();
        this->r();
        this->r();
        return *this;
    }

    GenericRubiksCube& b() override {
        rotateFace(static_cast<int>(FACE::BACK));

        char temp[3];
        // Store the top edge
        for (int i = 0; i < 3; i++) temp[i] = cube[static_cast<int>(FACE::UP)][0][2 - i];

        // Move edges: Right → Top, Bottom → Right, Left → Bottom, Temp → Left
        for (int i = 0; i < 3; i++) {
            cube[static_cast<int>(FACE::UP)][0][2 - i] = cube[static_cast<int>(FACE::RIGHT)][i][2];
            cube[static_cast<int>(FACE::RIGHT)][i][2] = cube[static_cast<int>(FACE::DOWN)][2][i];
            cube[static_cast<int>(FACE::DOWN)][2][i] = cube[static_cast<int>(FACE::LEFT)][2 - i][0];
            cube[static_cast<int>(FACE::LEFT)][2 - i][0] = temp[i];
        }

        return *this;
    }
    GenericRubiksCube& b2() override {
        this->b();
        this->b();
        return *this;
    }
    GenericRubiksCube& bPrime() override {
        this->b();
        this->b();
        this->b();
        return *this;
    }

    GenericRubiksCube& d() override {
        rotateFace(static_cast<int>(FACE::DOWN));

        char temp[3];
        // Store the front bottom edge
        for (int i = 0; i < 3; i++) temp[i] = cube[static_cast<int>(FACE::FRONT)][2][i];

        // Move edges: Left → Front, Back → Left, Right → Back, Temp → Right
        for (int i = 0; i < 3; i++) {
            cube[static_cast<int>(FACE::FRONT)][2][i] = cube[static_cast<int>(FACE::LEFT)][2][i];
            cube[static_cast<int>(FACE::LEFT)][2][i] = cube[static_cast<int>(FACE::BACK)][2][i];
            cube[static_cast<int>(FACE::BACK)][2][i] = cube[static_cast<int>(FACE::RIGHT)][2][i];
            cube[static_cast<int>(FACE::RIGHT)][2][i] = temp[i];
        }

        return *this;
    }
    GenericRubiksCube& d2() override {
        this->d();
        this->d();
        return *this;
    }
    GenericRubiksCube& dPrime() override {
        this->d();
        this->d();
        this->d();
        return *this;
    }

    bool operator==(const RubiksCube3dArray& other) const {
        // Compare all cube elements
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (cube[i][j][k] != other.cube[i][j][k]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    struct Hash3D {
        size_t operator()(const RubiksCube3dArray &r1) const {
            string str="";
            for (int i=0;i<6;i++) {
                for (int j=0;j<3;j++) {
                    for (int k=0;k<3;k++) {
                        str +=r1.cube[i][j][k];
                    }
                }
            }
            return hash<string>()(str);
        }
    };


};



#endif //RUBIKSCUBE3DARRAY_H
