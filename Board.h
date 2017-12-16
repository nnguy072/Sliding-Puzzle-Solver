#include <vector>
#include <iostream>
using namespace std;

class puzzleBoard {
   private:
      vector<vector<int> > board;         // current state of board
      vector<vector<int> > goalState;     // what the board should look like
      int row;                            // # of rows
      int column;                         // # of columns
      
      // to keep track of where the blank is
      int xBlank;
      int yBlank;
   
      bool hasMoved;                      // changes when blank moves
      
      int depth;                          // depth of the node
      int misplacedTiles;                 // # of misplaced tiles
      int manhattanDistance;              // manhattan distance
      
      string move;                          // returns what move it is
      
   public:
      puzzleBoard();                      // makes 3x3 board w/ hardcoded numbers
      puzzleBoard(int row, int column);   // row x column board
      void populateBoard();               // user inputs number for board
      bool isGoalState();                 // checks if board's state == goal state
                              
      int getRow();                       // returns # of rows
      int getColumn();                    // returns # of columns
      int getXBlank();                    // return x/row index of blank square
      int getYBlank();                    // return y/column index of blank square
      bool getHasMoved();
      int getDepth();                     // gets the depth
      string getMove();
      void setMove(string s);                       
      
      void printBoard();                  // output current board state 
      void printGoalState();              // output the goal state
      
      bool moveBlankUp();                 // move blank square up
      bool moveBlankDown();               // move blank square down
      bool moveBlankLeft();               // move blank square left
      bool moveBlankRight();              // move blank square right
      
      puzzleBoard& operator=(const puzzleBoard& rhs);
      bool operator==(const puzzleBoard& rhs) const;
      
      int calcMisplaced();                    // return number of misplaced tiles
      int calcManhattan();                    // return manhattan distance
      
      int getMisplacedHeurstic();
      int getManhattanHeurstic();
};