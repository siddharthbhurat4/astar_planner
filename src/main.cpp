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
    cout << "Length of Path" << planned_path.size() << endl;

    //Uncomment to print the path points generated
    // for(int i = 0; i<planned_path.size(); i++){
    //     cout << "Path point x: " << planned_path[i].x << "Path point y: " << planned_path[i].y << endl;
    // }

    //Display or visualize the path
    // SFML window setup
    int cell_size  = 50;
    int rows = grid.size();
    int cols = grid[0].size();
    sf::RenderWindow window(sf::VideoMode(400, 400), "A* Pathfinding Visualization");
    sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size)); // Size of each cell
    sf::Color lineColor(100, 100, 100); // Gray color for the grid lines

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        // Clear the window
        window.clear(sf::Color::Black);

        for (int i = 0; i <= rows; ++i) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(0, i * cell_size)),
                sf::Vertex(sf::Vector2f(cols * cell_size, i * cell_size))
            };
            line[0].color = lineColor;
            line[1].color = lineColor;
            window.draw(line, 2, sf::Lines);
        }

        // Draw vertical grid lines
        for (int j = 0; j <= cols; ++j) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(j * cell_size, 0)),
                sf::Vertex(sf::Vector2f(j * cell_size, rows * cell_size))
            };
            line[0].color = lineColor;
            line[1].color = lineColor;
            window.draw(line, 2, sf::Lines);
        }
        
        // Draw grid
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[i].size(); ++j) {
                cell.setPosition(j * cell_size, i * cell_size); // Position of each cell
                if (grid[i][j] == 1) {
                    cell.setFillColor(sf::Color::Black); // Obstacle
                } else {
                    if(i == start->y && j== start->x){
                        cell.setFillColor(sf::Color::Red);
                    }
                    else if(i == goal->y && j== goal->x){
                        cell.setFillColor(sf::Color::Green);
                    }
                    else cell.setFillColor(sf::Color::White); // Free space
                }
                window.draw(cell);
            }
        }

        //Show the path with blue
        for (size_t i = 1; i < planned_path.size(); i++) {
            cell.setPosition(planned_path[i].x * cell_size, planned_path[i].y * cell_size);
            cell.setFillColor(sf::Color::Blue);
            window.draw(cell);
        }

        // Display the window
        window.display();
    }
    delete start;
    delete goal;
    return 0;
}