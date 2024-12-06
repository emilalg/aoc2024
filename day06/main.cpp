#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::getline;
using std::cin;
using std::pair;
using std::set;

using coord = pair<size_t, size_t>;

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum Direction rotate(enum Direction current) {
    switch (current) {
        case UP:    return RIGHT;
        case RIGHT: return DOWN;
        case DOWN:  return LEFT;
        case LEFT:  return UP;
        default:    return UP;
    }
}

bool is_in_bounds(const coord& pos, const vector<string>& map) {
    return pos.first < map[0].size() && pos.second < map.size();
}

bool has_obstacle(const coord& pos, Direction dir, const vector<string>& map) {
    switch (dir) {
        case UP:
            return pos.second == 0 || map[pos.second - 1][pos.first] == '#';
        case RIGHT:
            return pos.first >= map[0].size() - 1 || map[pos.second][pos.first + 1] == '#';
        case DOWN:
            return pos.second >= map.size() - 1 || map[pos.second + 1][pos.first] == '#';
        case LEFT:
            return pos.first == 0 || map[pos.second][pos.first - 1] == '#';
    }
    return false;
}

coord move_forward(const coord& pos, Direction dir) {
    coord next = pos;
    switch (dir) {
        case UP:    next.second--; break;
        case RIGHT: next.first++;  break;
        case DOWN:  next.second++; break;
        case LEFT:  next.first--;  break;
    }
    return next;
}

int handle(vector<string> map) {
    set<coord> visited;
    coord location;
    Direction direction;
    
    // Find starting position
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].length(); j++) {
            switch (map[i][j]) {
                case '^':
                    direction = UP;
                    location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
                case '>':
                    direction = RIGHT;
                    location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
                case 'v':
                    direction = DOWN;
                    location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
                case '<':
                    direction = LEFT;
                    location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
            }
        }
    }
found_start:

    visited.insert(location);
    
    while (true) {
        coord next = move_forward(location, direction);
        
        if (!is_in_bounds(next, map)) {
            break;
        }
        
        if (has_obstacle(location, direction, map)) {
            direction = rotate(direction);
        } else {
            location = next;
            visited.insert(location);
        }
    }
    
    // -1 :D
    return visited.size() - 1;
}

int main() {
    string line;
    vector<string> input;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    cout << handle(input) << endl;
    return 0;
}