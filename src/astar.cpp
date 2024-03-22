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
        cout << "Parent: " <<"x (col): " << current->x << "|  y (row): " << current->y << endl;

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

        // for(Node& neighbor : neighbors){
        //     cout << "First Print |||: " << "Neighbor x: " << neighbor.x << "|  Neighbor y: " << neighbor.y << endl;
        //     cout << "is valid : " << isValid(neighbor.x, neighbor.y, grid) << endl;
        //     cout << "is blocked : " << !isBlocked(neighbor.x, neighbor.y, grid) << endl;
        //     cout << "closed list : " << !closedList[neighbor.y][neighbor.x] << endl;
        // }
        for(Node& neighbor : neighbors){
            cout << "Neighbor x: " << neighbor.x << "| Neighbor y: " << neighbor.y << endl;
            if(isValid(neighbor.x, neighbor.y, grid)){
                if (!isBlocked(neighbor.x, neighbor.y, grid) && !closedList[neighbor.y][neighbor.x]){
                    neighbor.g = current->g + getDistance(neighbor.x, neighbor.y, current->x, current->y);
                    neighbor.h = calculateHValue(neighbor.x, neighbor.y, goal);
                    neighbor.f = neighbor.g + neighbor.h;
                    neighbor.parent = current;
                    cout << "Pushing this "<<"Neighbor x: " << neighbor.x << "| Neighbor y: " << neighbor.y << " in the open list" <<endl;
                    openList.push(&neighbor);
                }
            }
        }
    }
    cout << "Path Not Found..." << endl;
    return path;
}
