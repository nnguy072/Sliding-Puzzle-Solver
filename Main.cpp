#include <iostream>
#include <queue>
#include "Board.h"
using namespace std;

static vector<puzzleBoard> steps;

// helper function
void quickSortMisplaced(vector<puzzleBoard>& v, int left, int right);
void quickSortManhattan(vector<puzzleBoard>& v, int left, int right);
bool isRepeated(const vector<puzzleBoard>& v, const puzzleBoard& p);

// 1 = uniform cost:
// f(n) = g(n) + h(n); g(n) = depth/cost to get to node h(n) = 0; // BFS
//
// 2 = misplaced tiles:
// f(n) = g(n) + h(n); g(n) = cost to get to node h(n) = # of misplaced tiles
//
// 3 = manhattan distance:
// f(n) = g(n) + h(n); g(n) = cost to get to node/depth h(n) = manhattan distance
queue<puzzleBoard> queueing_function(queue<puzzleBoard>& q, puzzleBoard& n, vector<puzzleBoard>& v, const string& s){
   // we want to store what's in the queue so it can be sorted
   // we want to sort bc we want the one w/ best heurstic to go first
   // Checking this vector every time is very costly esp since there are 9! states...
   vector<puzzleBoard> tempVec;
   while(!q.empty()){
      tempVec.push_back(q.front());
      q.pop();
   }
   
   // expand operators move blank UP/DOWN/LEFT/RIGHT
   puzzleBoard temp = n;
   temp.moveBlankUp();
   puzzleBoard childUp = temp;

   temp = n;
   temp.moveBlankDown();
   puzzleBoard childDown = temp;

   temp = n;
   temp.moveBlankLeft();
   puzzleBoard childLeft = temp;

   temp = n;
   temp.moveBlankRight();
   puzzleBoard childRight = temp;
   
   if(childUp.getHasMoved() && !isRepeated(v, childUp)){
      tempVec.push_back(childUp);
      v.push_back(childUp);   // push into vector to keep track of repeats
   }
   if(childDown.getHasMoved() && !isRepeated(v, childDown)){
      tempVec.push_back(childDown);
      v.push_back(childDown);
   }
   if(childLeft.getHasMoved() && !isRepeated(v, childLeft)){
      tempVec.push_back(childLeft);
      v.push_back(childLeft);
   }
   if(childRight.getHasMoved() && !isRepeated(v, childRight)){
      tempVec.push_back(childRight);
      v.push_back(childRight);
   }
   
   // sort temp bc we want best herustic to go first
   // if queueing function is 1 don't need to sort bc it's just BFS
   if(s == "2")   // misplaced
      quickSortMisplaced(tempVec, 0, tempVec.size() - 1);
   else if(s == "3") // manhattan
      quickSortManhattan(tempVec, 0, tempVec.size() - 1);

   //populate queue again
   for(int i = 0; i < tempVec.size(); i++){
      q.push(tempVec[i]);
   }
   
   return q; 
}

int general_search(puzzleBoard& p, const string& algorithm){
   // make queue and initalize with inital state
   queue<puzzleBoard> nodes;
   vector<puzzleBoard> repeatedStates; // keeps track of which state we've seen
   nodes.push(p);
   repeatedStates.push_back(p);
   int max = 0;
   
   cout << "Inital State" << endl;
   p.printBoard();
   cout << endl;
   
   // basically an infinite loop
   while(1){
      // if queue is empty then return failure
      if(nodes.empty())
         return -1;
      
      // remove front of queue
      puzzleBoard node = nodes.front();
      nodes.pop();
      if(node.getDepth() != 0){
         steps.push_back(node);
      }
      
      // if the node we're checking is in goal state return success
      if(node.isGoalState()){
         cout << "Success!" << endl;
         node.printBoard();
         cout << endl;
         
         cout << "To solve this problem the search algorithm expanded a total of " << repeatedStates.size() << " nodes." << endl;
         cout << "The maximum number of nodes in the queue at any one time was " << max << "." << endl;
         cout << "The depth of the goal node was " << node.getDepth() << "." << endl;
         return 1;
      }
   
      // print the node it is checking/expanding
      /*
      if(node.getDepth() == 0){
         cout << "Expanding state: " << endl;
      }
      if(node.getDepth() != 0 && algorithm == "1"){
         cout << "The best state to expand w/ a g(n) = " << node.getDepth()
              << " and a h(n) = 0 is..." << endl;
      } else if(node.getDepth() != 0 && algorithm == "2"){
         cout << "The best state to expand w/ a g(n) = " << node.getDepth()
              << " and a h(n) = " << node.calcMisplaced() << " is..." << endl;
      } else if(node.getDepth() != 0 && algorithm == "3"){
         cout << "The best state to expand w/ a g(n) = " << node.getDepth()
              << " and a h(n) = " << node.calcManhattan() << " is..." << endl;
      }
      node.printBoard();
      cout << endl;
      */
      
      // expand and enqueue children
      // 1 == uniform cost; 2 == misplacedTile; 3 == manhattanDistance
      // repeatedStates vector to check for repeated states
      nodes = queueing_function(nodes, node, repeatedStates, algorithm);
         
      // keep track of maximum number of nodes at any one time
      if(nodes.size() > max)
         max = nodes.size();
   }
}

int main(){
   puzzleBoard eightPuzzle;
   
   // change dimensions of puzzle
   // change this to make it more general
   int row = 3;
   int column = 3;
   
   string input;
   cout << "Welcome to Nam Nguyen's 8-puzzle solver." << endl;
   cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle" << endl;
   cin >> input;
   cout << endl;
   
   if(input == "1"){
      eightPuzzle = puzzleBoard();
   }
   else if(input == "2"){
      cout << "Enter # of rows and columns, seperate using a space: ";
      cin >> row >> column;
      cout << "row: " << row << " column: " << column << endl;
      cout << endl;
      
      eightPuzzle = puzzleBoard(row, column);
      eightPuzzle.populateBoard();
      cout << endl;
   }
   else{
      cout << "Dude, just enter 1 or 2 like a normal person..." << endl;
      return 1;
   }
   
   cout << "Enter your choice of algorithm:" << endl;
   cout << "\t1. Uniform Cost Search" << endl;
   cout << "\t2. A* with the Misplaced Tile Heuristic" << endl;
   cout << "\t3. A* with the Manhattan Distance Heuristic" << endl;
   cout << "\t";
   cin >> input;
   cout << endl;
   
   if(general_search(eightPuzzle, input) != 1)
      cout << "Failure" << endl;

   if(input == "2" || input == "3"){
      cout << "Steps to solving puzzle: " << endl;
      for(int i = 0; i < steps.size();i++){
         cout << i+1 << ". " << steps[i].getMove() << endl;
      }
   }   
   return 0;
}

// http://www.algolist.net/Algorithms/Sorting/Quicksort
// algorithm was taken from ^^^^^^^^^^^^
// modified to sort misplaced tiles
void quickSortMisplaced(vector<puzzleBoard>& v, int left, int right){
   int i = left, j = right;
   puzzleBoard tmp;
   int pivot = v[(left + right) / 2].getMisplacedHeurstic();

   /* partition */
   while (i <= j) {
      while (v[i].getMisplacedHeurstic() < pivot)
         i++;
      while (v[j].getMisplacedHeurstic() > pivot)
         j--;
      if (i <= j) {
         tmp = v[i];
         v[i] = v[j];
         v[j] = tmp;
         i++;
         j--;
      }
   };

   /* recursion */
   if (left < j)
      quickSortMisplaced(v, left, j);
   if (i < right)
      quickSortMisplaced(v, i, right);
}

// http://www.algolist.net/Algorithms/Sorting/Quicksort
// algorithm was taken from ^^^^^^^^^^^^
// modified to sort manhattan
void quickSortManhattan(vector<puzzleBoard>& v, int left, int right){
   int i = left, j = right;
   puzzleBoard tmp;
   int pivot = v[(left + right) / 2].getManhattanHeurstic();

   /* partition */
   while (i <= j) {
      while (v[i].getManhattanHeurstic() < pivot)
         i++;
      while (v[j].getManhattanHeurstic() > pivot)
         j--;
      if (i <= j) {
         tmp = v[i];
         v[i] = v[j];
         v[j] = tmp;
         i++;
         j--;
      }
   };

   /* recursion */
   if (left < j)
      quickSortManhattan(v, left, j);
   if (i < right)
      quickSortManhattan(v, i, right);
}

// checks if the state is same as one inside the queue
bool isRepeated(const vector<puzzleBoard>& v, const puzzleBoard& p){
   for(int i = 0; i < v.size(); i++){
      if(v[i] == p)
         return true;
   }
   return false;
}