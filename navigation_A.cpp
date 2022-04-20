#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
/* TODO: Define a Map class
   Inside the map class, define the mapWidth, mapHeight and grid as a 2D vector
*/
class Map
{
public:
   //Map();
   //~Map();
   const static int mapWidth =6;
   const static int mapHeight = 5;
   vector<vector<int>> grid ={
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 }
   } ;
   
};
/* TODO: Define a Planner class
   Inside the Planner class, define the start, goal, cost, movements, and movements_arrows
   Note: The goal should be defined it terms of the mapWidth and mapHeight
*/
class Planner : public Map {
public:
   int start[2] = {0,0};
   int goal[2] = {mapHeight-1, mapWidth-1};
   int cost = 1;

   vector<vector<int>> movements = {
      {-1,0},
      {0,-1},
      {1,0},
      {0,1}
   };
   string movements_arrows[4] = {"^","<","v",">"};
};

// Template function to print 2D vectors of any type

template <typename T>

void print2DVector(T Vec){

   for (int i=0; i<Vec.size();i++){
      for (int j=0; j< Vec[0].size(); j++)
         cout << Vec[i][j] << " ";
      cout << endl;
   }


}

/*#### TODO: Code the search function which will generate the expansion list ####*/
// You are only required to print the final triplet values
void search(Map map, Planner planner)
{
    vector<vector<int>> available;
    vector <vector<int>> used (map.mapHeight, vector<int> (map.mapWidth,0));
    vector <vector<int>> costArray (map.mapHeight, vector<int> (map.mapWidth,-1));
    vector <vector<int>> actions (map.mapHeight, vector<int> (map.mapWidth,-1));
    used[planner.start[0]][planner.start[1]] = 1;

    // Defined the triplet values
    int x = planner.start[0];
    int y = planner.start[1];
    int c = 0;
    int h=0;
    int f =0;

    h = abs(planner.start[0] - planner.goal[0])+abs(planner.start[1] - planner.goal[1]);
    f = c+h;

    available.push_back({f,c,x,y});

    int found = 0;
    int resign=0;
    int costs = 0;
    int x2=0;
    int y2=0;
    int c2=0;

    vector<int> next (4,0);

    while (!found && !resign)
    {
         if (available.size() == 0) {
            resign = true;
            cout << "Failed to reach a goal" << endl;
        }
        else
        {
         //cout << 5 << endl;
         sort(available.begin(), available.end());
         reverse(available.begin(), available.end());
         next = available.back();
         available.pop_back();

         x= next[2];
         y=next[3];
         c = next[1];

         costArray[x][y] = costs;
         //cout <<"costArray" <<endl;
         //print2DVector(costArray);
         //cout << endl;
         costs+=1;

         if (x == planner.goal[0] && y == planner.goal[1] ){
            found = true;
            //print2DVector(used);
            //cout << 1 << endl;
         }
         else{
            //cout << 2 << endl;
            int moveStep = -1;
            for (vector<int> move : planner.movements){
               moveStep+=1;
               x2 = x + move[0];
               y2 = y + move[1];
               //cout << move[0] << " " << move[1] <<  endl;
               if(x2 >=0 && y2 >=0 && x2 < map.mapHeight && y2 < map.mapWidth){
                  //cout << 7 << endl;
                  if (map.grid[x2][y2] ==0 and used[x2][y2]==0){
                     c2 = c + planner.cost;
                     h = abs(x2 - planner.goal[0])+abs(y2 - planner.goal[1]);
                     f = c2+h;
                     available.push_back({f,c2,x2,y2});
                     //print2DVector(available);
                     //cout << endl;
                     used[x2][y2] = 1;
                     //print2DVector(used);
                     actions[x2][y2] = moveStep;
                     //cout << endl;cout << endl;
                     //cout << 3 <<"-"<< map.grid[x2][y2] << endl;
                  }
               }

            }
         }


        }
    }
   // Print the expansion List
    print2DVector(costArray);

    //generate optimal path

    x = planner.goal[0];
    y =planner.goal[1];

    vector<vector<string>> path (map.mapHeight, vector<string> (map.mapWidth,"-"));

    path[x][y] = "*";

    while( x != planner.start[0] || y != planner.start[1])
    {
      x2 = x - planner.movements[actions[x][y]][0];
      y2 = y - planner.movements[actions[x][y]][1];
      //cout <<"x2 " << x2;cout <<" y2 " << y2 << " "; cout << actions[x2][y2] <<endl;
      path[x2][y2] = planner.movements_arrows[actions[x][y]];
      x = x2;
      y=y2;
         // Print the expansion List
    //print2DVector(path);
    }

   // Print the Optimal Path
    print2DVector(path);
}

int main()
{  /* (1)
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Print classes variables
    cout << "Map:" << endl;
    print2DVector(map.grid);
    cout << "Start: " << planner.start[0] << " , " << planner.start[1] << endl;
    cout << "Goal: " << planner.goal[0] << " , " << planner.goal[1] << endl;
    cout << "Cost: " << planner.cost << endl;
    cout << "Robot Movements: " << planner.movements_arrows[0] << " , " << planner.movements_arrows[1] << " , " << planner.movements_arrows[2] << " , " << planner.movements_arrows[3] << endl;
    cout << "Delta:" << endl;
    print2DVector(planner.movements);

    return 0;
    */
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Search for the expansions
    search(map, planner);

    return 0;
}
