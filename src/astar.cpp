#include "astar.h"
//Column is x
//Row is y

Astar::Astar(){}

bool Astar::isValid(int x, int y, vector<vector<int>>& grid){
    return (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size());
}

bool Astar::isBlocked(int x, int y, vector<vector<int>>& grid){
    return grid[y][x];
}

bool Astar::isDestination(int x, int y, Node goal){
    return (x==goal.x && y==goal.y);
}

double Astar::calculateHValue(int x, int y, Node* goal){
    return sqrt((x-goal->x)*(x-goal->x) + (y-goal->y)*(y-goal->y));
}

double Astar::getDistance(int x1, int y1, int x2, int y2){
    return int(10 * sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

vector<Node> Astar::getNeighbours(Node* current){
    vector<Node> neighbors;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if (i==0 && j==0) continue;
            neighbors.push_back(Node(current->x+i, current->y+j, 0, 0, nullptr));
        }
    }
    return neighbors;
}

vector<Node> Astar::findPath(Node* start, Node* goal, vector<vector<int>>& grid){
    
    //Initializing the open list using priority queue
    priority_queue<Node*, vector<Node*>, CompareNodes> openList;
    
    //Initializing closed list using a 2d array
    vector<vector<bool>> closedList(grid.size(), vector<bool>(grid[0].size(), false));

    //calculate the h cost for the start node
    start->h = calculateHValue(start->x, start->y, goal);

    //put stating node in the open list
    openList.push(start);
    // // vector<pair<int, int>> path;
    vector<Node> path;

    while(openList.empty() != true){
        //Load the node with lowest f cost
        Node* current = openList.top();

        //pop that node off the open list
        openList.pop();

        //found the goal and reconstruct the path
        if(current->x == goal->x && current->y == goal->y){
            cout << "Goal Reached" << endl;
            while (current->parent != nullptr) {
                path.push_back(*current);
                current = current->parent;
            }
            return path;
        }

        //add it to the closed list
        closedList[current->y][current->x] = true;

        //find the 8 neighbors of the current cell
        vector<Node> neighbors = getNeighbours(current);


        for(int i = 0; i < neighbors.size(); i++){
            if(isValid(neighbors[i].x, neighbors[i].y, grid)){
                if (!isBlocked(neighbors[i].x, neighbors[i].y, grid) && !closedList[neighbors[i].y][neighbors[i].x]){
                    double g = current->g + getDistance(neighbors[i].x, neighbors[i].y, current->x, current->y);
                    double h = calculateHValue(neighbors[i].x, neighbors[i].y, goal);
                    double f = neighbors[i].g + neighbors[i].h;
                    Node* parent = current;
                    Node* successor = new Node(neighbors[i].x, neighbors[i].y, g, h, parent);
                    openList.push(successor);
                }
            }
        }
    }
    cout << "Path Not Found..." << endl;
    return path;
}
