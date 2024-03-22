#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <unordered_set>

using namespace std;


//Column is x
//Row is y

struct Node{
    int x;
    int y;
    double f;
    double g;
    double h;
    Node* parent;
    Node(int x, int y, double g, double h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent){
            f = g + h;
        }
};

// Define a custom hash function for Node
struct NodeHash {
    size_t operator()(const Node* node) const {
        // Combine hashes of x and y using XOR
        return std::hash<int>()(node->x) ^ std::hash<int>()(node->y);
    }
};

// Define a custom equality operator for Node
struct NodeEqual {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->x == rhs->x && lhs->y == rhs->y;
    }
};


struct CompareNodes{
    bool operator()(const Node* a, const Node* b){
        return a->f > b->f; //lowest fvalue has higher priority
    }
};

class Astar {
    public:
        
        // constructor
        Astar();

        //Path finding function, astar algorithm goes here
        vector<Node> findPath(Node* start, Node* goal, vector<vector<int>>& grid); 
        
        //helper functions
        bool isValid(int x, int y, vector<vector<int>>& grid);
        bool isBlocked(int x, int y, vector<vector<int>>& grid);
        bool isDestination(int x, int y, Node goal);
        double calculateHValue(int x, int y, Node* goal);
        vector<Node> getNeighbours(Node* current);
        double getDistance(int x1, int y1, int x2, int y2);
        // int getMovementCost(Node& a, Node& b);

};

