#include <iostream>
#include <queue>
#include "board.h"
using namespace std;

// checks if the state is same as one inside the queue
bool isRepeated(const vector<puzzleBoard>& v, const puzzleBoard& p){
   for(int i = 0; i < v.size(); i++){
      if(v[i] == p)
         return true;
   }
   return false;
}

// BFS and won't add repeated states onto queue
queue<puzzleBoard> uniformCost(queue<puzzleBoard> q, puzzleBoard& n, vector<puzzleBoard>& v){
   // operators move blank UP/DOWN/LEFT/RIGHT
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
   
   // checks if expanded is legal and not a repeated state
   if(childUp.getHasMoved() && !isRepeated(v, childUp)){
      //cout << "Queued Up" << endl;
      q.push(childUp);        // push child in queue
      v.push_back(childUp);   // push into vector to keep track of repeats
   }
   if(childDown.getHasMoved() && !isRepeated(v, childDown)){
      //cout << "Queued Down" << endl;
      q.push(childDown);
      v.push_back(childDown);
   }
   if(childLeft.getHasMoved() && !isRepeated(v, childLeft)){
      //cout << "Queued Left" << endl;
      q.push(childLeft);
      v.push_back(childLeft);
   }
   if(childRight.getHasMoved() && !isRepeated(v, childRight)){
      //cout << "Queued Right" << endl;
      q.push(childRight);
      v.push_back(childRight);
   }
   
   return q; 
}

queue<puzzleBoard> misplacedTile(queue<puzzleBoard>& q, puzzleBoard& n, vector<puzzleBoard>& v){
   cout << "# of misplaced tiles: " << n.misplaced() << endl;
   
   // operators move blank UP/DOWN/LEFT/RIGHT
   puzzleBoard temp = n;
   temp.moveBlankUp();
   puzzleBoard childUp = temp;
   3
   temp = n;
   temp.moveBlankDown();
   puzzleBoard childDown = temp;
   
   temp = n;
   temp.moveBlankLeft();
   puzzleBoard childLeft = temp;
   
   temp = n;
   temp.moveBlankRight();
   puzzleBoard childRight = temp;
   
   
   
   return q; 
}

queue<puzzleBoard> manhattanDistance(queue<puzzleBoard>& q, puzzleBoard& n, vector<puzzleBoard>& v){
   
   
   return q; 
}

int general_search(puzzleBoard& p, const string& queueing_function){
   // make queue and initalize with inital state
   queue<puzzleBoard> nodes;
   vector<puzzleBoard> repeatedStates; // keeps track of which state we've seen
   repeatedStates.push_back(p);
   
   // basically an infinite loop
   while(1){
      // if queue is empty then return failure
      if(nodes.empty())
         return -1;
      
      // remove front of queue
      puzzleBoard node = nodes.front();
      nodes.pop();
      
      // print the node it is checking/expanding
      node.printBoard();
      cout << endl;
      
      // if the node we're checking is in goal state return success
      if(node.isGoalState()){
         return 1;
      }
      
      // expand and enqueue children
      // 1 == uniform cost; 2 == misplacedTile; 3 == manhattanDistance
      if(queueing_function == "1")
         nodes = uniformCost(nodes, node, repeatedStates);
      else if(queueing_function == "2")
         nodes = misplacedTile(nodes, node, repeatedStates);
      else if(queueing_function == "3")
         nodes = manhattanDistance(nodes, node, repeatedStates);
      
      cout << "nodes size: " << nodes.size() << endl;
      cout << "repeatedStates size: " << repeatedStates.size() << endl;
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
      eightPuzzle = puzzleBoard(row, column);
      eightPuzzle.populateBoard();
   }
   else{
      cout << "Dude, just enter 1 or 2 like a normal person..." << endl;
      return 1;
   }
   
   cout << "Enter your choice of algorithm:" << endl;
   cout << "\t1. Uniform Cost Search" << endl;
   cout << "\t2. A* with the Misplaced Tile Heuristic" << endl;
   cout << "\t3. A* with the Manhattan distance heuristic" << endl;
   cout << "\t";
   cin >> input;
   cout << endl;
   
   cout << general_search(eightPuzzle, input) << endl;
    
   return 0;
}