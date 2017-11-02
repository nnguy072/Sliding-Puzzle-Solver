#include <iostream>
#include <queue>
#include "board.h"
using namespace std;

void quickSort(vector<puzzleBoard>& v, int left, int right);

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

// f(n) = g(n) + h(n); g(n) = cost to get to node h(n) = # of misplaced tiles
queue<puzzleBoard> misplacedTile(queue<puzzleBoard>& q, puzzleBoard& n, vector<puzzleBoard>& v){
   // we want to store what's in the queue so it can be sorted
   // we want to sort bc we want the one w/ best heurstic to go first
   vector<puzzleBoard> tempVec;
   while(!q.empty()){
      tempVec.push_back(q.front());
      //cout << q.front().getMisplacedHeurstic() << " ";
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
   
   // checks if expanded is legal and not a repeated state
   // also add to the vector containing all nodes inside queue
   if(childUp.getHasMoved() && !isRepeated(v, childUp)){
      //cout << "Queued Up" << endl;
      tempVec.push_back(childUp);
      v.push_back(childUp);   // push into vector to keep track of repeats
   }
   if(childDown.getHasMoved() && !isRepeated(v, childDown)){
      //cout << "Queued Down" << endl;
      tempVec.push_back(childDown);
      v.push_back(childDown);
   }
   if(childLeft.getHasMoved() && !isRepeated(v, childLeft)){
      //cout << "Queued Left" << endl;
      tempVec.push_back(childLeft);
      v.push_back(childLeft);
   }
   if(childRight.getHasMoved() && !isRepeated(v, childRight)){
      //cout << "Queued Right" << endl;
      tempVec.push_back(childRight);
      v.push_back(childRight);
   }
   
   // sort temp bc we want best herustic to go first
   quickSort(tempVec, 0, tempVec.size() - 1);
   
   //populate queue again
   for(int i = 0; i < tempVec.size(); i++){
      q.push(tempVec[i]);
      //cout << tempVec[i].getMisplacedHeurstic() << " ";
   }

   return q; 
}

queue<puzzleBoard> manhattanDistance(queue<puzzleBoard>& q, puzzleBoard& n, vector<puzzleBoard>& v){
   
   
   return q; 
}

int general_search(puzzleBoard& p, const string& queueing_function){
   // make queue and initalize with inital state
   queue<puzzleBoard> nodes;
   vector<puzzleBoard> repeatedStates; // keeps track of which state we've seen
   nodes.push(p);
   repeatedStates.push_back(p);
   int max = 0;
   
   // basically an infinite loop
   while(1){
      // if queue is empty then return failure
      if(nodes.empty())
         return -1;
      
      // remove front of queue
      puzzleBoard node = nodes.front();
      nodes.pop();
      
      if(node.getDepth() == 0){
         cout << "Expanding state: " << endl;
      }
      if(node.getDepth() != 0 && queueing_function == "2"){
         cout << "The best state to expand w/ a g(n) = " << node.getDepth()
              << " and a h(n) = " << node.calcMisplaced() << " is..." << endl;
      }
      // print the node it is checking/expanding
      node.printBoard();
      cout << endl;

      // if the node we're checking is in goal state return success
      if(node.isGoalState()){
         cout << "Success\n" << endl;
         cout << "To solve this problem the search algorithm expanded a total of " << repeatedStates.size() << " nodes." << endl;
         cout << "The maximum number of nodes in the queue at any one time was " << max << "." << endl;
         cout << "The depth of the goal node was " << node.getDepth() << "." << endl;
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
      
      
      // keep track of maximum number of nodes at any one time
      if(nodes.size() > max)
         max = nodes.size();
      //cout << "nodes size: " << nodes.size() << endl;
      //cout << "repeatedStates size: " << repeatedStates.size() << endl;
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
   cout << "\t3. A* with the Manhattan distance heuristic" << endl;
   cout << "\t";
   cin >> input;
   cout << endl;
   
   if(general_search(eightPuzzle, input) != 1)
      cout << "Failure" << endl;

   return 0;
}

// http://www.algolist.net/Algorithms/Sorting/Quicksort
// algorithm was taken from ^^^^^^^^^^^^
void quickSort(vector<puzzleBoard>& v, int left, int right){
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
      quickSort(v, left, j);
   if (i < right)
      quickSort(v, i, right);
}
