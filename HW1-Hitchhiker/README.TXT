Coehl Gleckner
DSA 2
HW - Sliding Puzzle
9/17/2018

General
I started with creating a working puzzle, that could shuffle randomly n(set by player) times and be able to swap accordingly.
Double pointers allow creation of a pointer of arrays, so that we can keep track of board states we have seen.
You can also Reset the board at anytime. 
I've also included improvements I could make, if in the future I want to get better at C++ and don't want to start something from scratch.

Naming
LC = Lowest Cost
H = Heuristic
HC = HillClimbing

Astar
Checks with lowest cost outwards from the starting array of values, then proceeds to check heuristics
Similar to Sonar, checks outwards
Returns how many checks it does to find the completed array

Hillclimbing
Checks a certain direction to a certain depth
Continues on that depth and searches all possible nodes, then recursively jumps back up
Returns how many checks it had to find the completed array


-------IMPROVEMENTS TO BE MADE IN THE FUTURE---------
1) Convert to exclusive pointers, no arrays
2) Clean memory progressively
3) Inside both lowest cost and heuristics, if the exact graph exists don't make a new one, especially if the number is lower
4) Finish Printing A Star
5) Implemenate changing the size of the array
6) All the bonuses I didn't complete