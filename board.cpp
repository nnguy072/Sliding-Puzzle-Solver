#include "board.h"
#include <iostream>
using namespace std;

/* 
default board is 3x3                1 2 *   goal state:   1 2 3
definitely a better way to this     4 5 3                 4 5 6
has hardcoded numbers --------->    7 8 6                 7 8 *
*/
puzzleBoard::puzzleBoard() {
   vector<vector<int> > temp(3, vector<int>(3, 0));
   board = temp;
   goalState = temp;
   row = 3;
   column = 3;
   hasMoved = false;
   
   //definitely a better way of doing this
   // hard code default board
   board[0][0] = 1;
   board[0][1] = 2;
   board[0][2] = 0;
   board[1][0] = 4;
   board[1][1] = 5;
   board[1][2] = 3;
   board[2][0] = 7;
   board[2][1] = 8;
   board[2][2] = 6;
   
   // hard coded goal state
   goalState[0][0] = 1;
   goalState[0][1] = 2;
   goalState[0][2] = 3;
   goalState[1][0] = 4;
   goalState[1][1] = 5;
   goalState[1][2] = 6;
   goalState[2][0] = 7;
   goalState[2][1] = 8;
   goalState[2][2] = 0;
   
   // update location of blank
   xBlank = 0;
   yBlank = 2;
}

// define a row x column board with 0's
// definitely a better way to do this?
puzzleBoard::puzzleBoard(int row, int column){
   // declare a row x column vector fill with 0
   vector<vector<int> > temp(row, vector<int>(column, 0));
   board = temp;
   goalState = temp;
   this->row = row;
   this->column = column;
   hasMoved = false;
   
   // generate goal state
   int counter = 1;
   for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
         if(counter != (row * column)){
            goalState[i][j] = counter;
            counter++;
         } else {       // last spot is a blank
            goalState[i][j] = 0;
         }
      }
   }
}

// modify board to user input
void puzzleBoard::populateBoard() {
   int input;
   
   cout << "Enter your puzzle, use a zero to represent the blank" << endl;
   for(int i = 0; i < row; i++){
      cout << "Enter row " << i + 1 << ", use space between numbers:\t\t";
      for(int j = 0; j < column; j++){
         cin >> input;
         board[i][j] = input;
         if(input == 0){
            xBlank = i;
            yBlank = j;
         }
      }
   }
}

// check if board is in goal State 
bool puzzleBoard::isGoalState(){
   for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
         if(board[i][j] != goalState[i][j])
            return false;
      }
   }
   return true;
}

// accessors
int puzzleBoard::getRow(){ return row; }
int puzzleBoard::getColumn(){ return column; }
int puzzleBoard::getXBlank(){ return xBlank; }
int puzzleBoard::getYBlank(){ return yBlank; }
bool puzzleBoard::getHasMoved(){ return hasMoved; }

// prints n x n board
void puzzleBoard::printBoard() {
   for(int i = 0; i < board.size(); i++){
      for(int j = 0; j < board[i].size(); j++){
         cout << board[i][j] << " ";
         if(j == board[i].size() - 1){
            cout << endl;
         }
      }
   }
}

// print goal state
void puzzleBoard::printGoalState() {
   for(int i = 0; i < goalState.size(); i++){
      for(int j = 0; j < goalState[i].size(); j++){
         cout << goalState[i][j] << " ";
         if(j == goalState[i].size() - 1){
            cout << endl;
         }
      }
   }
}

// ----------------------------------------------------------------------
// operators
bool puzzleBoard::moveBlankUp(){
   // if on the first row, you can't move the blank up
   if(xBlank == 0){
      //cout << "can't move up" << endl;
      hasMoved = false;
      return false;
   } else {
      // switch places square above
      int temp = board[xBlank - 1][yBlank];
      board[xBlank - 1][yBlank] = 0;
      board[xBlank][yBlank] = temp;
      
      // update blank location
      xBlank -= 1;
      hasMoved = true;
   }
   return true;
}

bool puzzleBoard::moveBlankDown(){
   // if on the bottom row, you can't move the blank down
   if(xBlank == row - 1){
      //cout << "can't move down" << endl;
      hasMoved = false;
      return false;
   } else {
      // switch places square below
      int temp = board[xBlank + 1][yBlank];
      board[xBlank + 1][yBlank] = 0;
      board[xBlank][yBlank] = temp;
      
      // update blank location
      xBlank += 1;
      hasMoved = true;
   }
   return true;
}

bool puzzleBoard::moveBlankLeft(){
   // if on the left column, you can't move it left
   if(yBlank == 0){
      //cout << "can't move left" << endl;
      hasMoved = false;
      return false;
   } else {
      // switch places square on left
      int temp = board[xBlank][yBlank - 1];
      board[xBlank][yBlank - 1] = 0;
      board[xBlank][yBlank] = temp;
      
      // update blank location
      yBlank -= 1;
      hasMoved = true;
   }
   return true;
}

bool puzzleBoard::moveBlankRight(){
   // if on the right column, you can't move it right
   if(yBlank == column - 1){
      //cout << "can't move right" << endl;
      hasMoved = false;
      return false;
   } else {
      // switch places square on right
      int temp = board[xBlank][yBlank + 1];
      board[xBlank][yBlank + 1] = 0;
      board[xBlank][yBlank] = temp;
      
      // update blank location
      yBlank += 1;
      hasMoved = true;
   }
   return true;
}
// ----------------------------------------------------------------------

void puzzleBoard::testMoving(){
   string input;
   
   cout << "u/d/r/l: ";
   cin >> input;
   
   while(input == "u" || input == "d" || input == "r" || input == "l"){
   if(input == "u"){
      moveBlankUp();
      printBoard();
   } else if(input == "d"){
      moveBlankDown();
      printBoard();
   } else if(input == "r"){
      moveBlankRight();
      printBoard();
   } else if(input == "l"){
      moveBlankLeft();
      printBoard();
   }
   cout << "u/d/r/l: ";
   cin >> input;
   }
}

puzzleBoard& puzzleBoard::operator=(const puzzleBoard& rhs){
   // HOW IS THIS THING WORKING???
   // these are all private data fields??
   board = rhs.board;
   goalState = rhs.goalState;
   row = rhs.row;
   column = rhs.column;
   xBlank = rhs.xBlank;
   yBlank = rhs.yBlank;
   
   return *this;
}

bool puzzleBoard::operator==(const puzzleBoard& rhs) const{
   for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
         if(board[i][j] != rhs.board[i][j])
            return false;
      }
   }
   return true;
}

int puzzleBoard::misplaced(){
   int misplacedTiles = 0;

   for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
         if(board[i][j] != goalState[i][j])
            misplacedTiles++;
      }
   }
   return misplacedTiles;
}

int puzzleBoard::manhattan(){
   int manhattanDistance = 0;
   
   return manhattanDistance;
}