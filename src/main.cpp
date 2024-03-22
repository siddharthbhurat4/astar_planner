#include <astar.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    //Creating the instance of astar planner class
    Astar astar;

    //Defining the occupancy grid  or the map
    // Example grid (0 for free space, 1 for obstacles)
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };
    
    //Defining the start and goal nodes
    Node* start = new Node(3, 4, 0.0, 0.0, nullptr); 
    Node* goal = new Node(3, 0, 0.0, 0.0, nullptr);

    //Find the path
    vector<Node> planned_path = astar.findPath(start, goal, grid);
    cout << "Length of Path: " << planned_path.size() << endl;

    //Uncomment to print the path points generated
    // for(int i = 0; i<planned_path.size(); i++){
    //     cout << "Path point x: " << planned_path[i].x << "Path point y: " << planned_path[i].y << endl;
    // }

    delete start;
    delete goal;
    return 0;
}