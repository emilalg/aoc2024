#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <tuple>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::getline;
using std::cin;
using std::pair;
using std::set;
using std::tie;

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
    coord start_location;
    Direction initial_direction;
    
    // Find starting position
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].length(); j++) {
            switch (map[i][j]) {
                case '^':
                    initial_direction = UP;
                    start_location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
                case '>':
                    initial_direction = RIGHT;
                    start_location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
                case 'v':
                    initial_direction = DOWN;
                    start_location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
                case '<':
                    initial_direction = LEFT;
                    start_location = {j, i};
                    map[i][j] = '.';
                    goto found_start;
            }
        }
    }
found_start:

    auto successful = 0;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].length(); j++) {
            if (map[i][j] == '#' || coord{j,i} == start_location) {
                continue;  
            }

            enum Direction dir = initial_direction;
            coord location = start_location;
            vector<string> modmap = map;
            modmap[i][j] = '#';
            set<pair<coord, Direction>> visited;  // Using a set instead of vector

            while (true) {
                // Store current state
                if (!visited.insert({location, dir}).second) {
                    // If we couldn't insert, we've seen this state before
                    successful++;
                    break;
                }

                coord next = move_forward(location, dir);

                if (!is_in_bounds(next, modmap)) {
                    break;
                }

                if (has_obstacle(location, dir, modmap)) {
                    dir = rotate(dir);
                } else {
                    location = next;
                }
            }
        }
    }
    return successful;
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