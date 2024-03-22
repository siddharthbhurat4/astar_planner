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
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0}
    };
    
    //Defining the start and goal nodes
    Node* start = new Node(0, 0, 0.0, 0.0, nullptr); 
    Node* goal = new Node(4, 2, 0.0, 0.0, nullptr);

    //Find the path
    vector<Node> planned_path = astar.findPath(start, goal, grid);
    cout << planned_path.size() << endl;
    // for(int i = 0; i<planned_path.size(); i++){
    //     cout << "Path point x: " << planned_path[i].x << "Path point y: " << planned_path[i].y << endl;
    // }
    //Display or visualize the path
    // SFML window setup
    // sf::RenderWindow window(sf::VideoMode(400, 400), "A* Pathfinding Visualization");
    // sf::RectangleShape cell(sf::Vector2f(40, 40)); // Size of each cell
    // // Main loop
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }
        
    //     // Clear the window
    //     window.clear();
        
    //     // Draw grid
    //     for (size_t i = 0; i < grid.size(); ++i) {
    //         for (size_t j = 0; j < grid[i].size(); ++j) {
    //             cell.setPosition(j * 40, i * 40); // Position of each cell
    //             if (grid[i][j] == 1) {
    //                 cell.setFillColor(sf::Color::Black); // Obstacle
    //             } else {
    //                 cell.setFillColor(sf::Color::White); // Free space
    //             }
    //             window.draw(cell);
    //         }
    //     }

    //     // Display the window
    //     window.display();
    // }
    delete start;
    delete goal;
    return 0;
}