#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

using std::string;
using std::vector;
using std::tuple;
using std::getline;
using std::cin;
using std::cout;
using std::endl;
using std::tie;
using std::pair;
using coord = tuple<int, int>;

inline vector<pair<coord, coord>> calculate_coords(coord c, int h, int w) {
    int x, y;
    tie(x, y) = c;
    auto distance_r = w - x - 1;
    auto distance_b = h - y - 1;
    vector<pair<coord, coord>> output;
   
    if (x >= 3)
        output.push_back({c, {x-3, y}});
   
    if (distance_r >= 3)
        output.push_back({c, {x+3, y}});
   
    if (y >= 3)
        output.push_back({c, {x, y-3}});
   
    if (distance_b >= 3)
        output.push_back({c, {x, y+3}});
   
    if (x >= 3 && y >= 3)
        output.push_back({c, {x-3, y-3}});
   
    if (distance_r >= 3 && y >= 3)
        output.push_back({c, {x+3, y-3}});
   
    if (x >= 3 && distance_b >= 3)
        output.push_back({c, {x-3, y+3}});
   
    if (distance_r >= 3 && distance_b >= 3)
        output.push_back({c, {x+3, y+3}});
   
    return output;
}

inline bool verify(vector<string>& array, pair<coord, coord> coordinates) {
    coord start, end;
    tie(start, end) = coordinates;
   
    int x1, y1, x2, y2;
    tie(x1, y1) = start;
    tie(x2, y2) = end;
   
    int dx = (x2 - x1) / 3;
    int dy = (y2 - y1) / 3;
   
    string word = "";
    for (int i = 0; i <= 3; i++) {
        int x = x1 + (dx * i);
        int y = y1 + (dy * i);
        word += array[y][x];
    }
   
    return (word == "XMAS" || word == "SAMX");
}

bool is_same_sequence(const pair<coord, coord>& a, const pair<coord, coord>& b) {
    coord a_start, a_end, b_start, b_end;
    tie(a_start, a_end) = a;
    tie(b_start, b_end) = b;
    
    return (
        // Either exact same coordinates
        (a_start == b_start && a_end == b_end) ||
        // Or same coordinates in reverse
        (a_start == b_end && a_end == b_start)
    );
}

int process(vector<string>& array) {
    auto width = array[0].size();
    auto height = array.size();
    auto counter = 0;
    vector<pair<coord, coord>> known;
    
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            auto possible = calculate_coords(coord{col, row}, height, width);
            
            for (const auto& possibility : possible) {
                if (verify(array, possibility)) {
                    // Check if we've already counted this sequence
                    bool is_duplicate = false;
                    for (const auto& known_seq : known) {
                        if (is_same_sequence(possibility, known_seq)) {
                            is_duplicate = true;
                            break;
                        }
                    }
                    if (!is_duplicate) {
                        known.push_back(possibility);
                        counter++;
                    }
                }
            }
        }
    }
    return counter;
}

int main() {
    vector<string> collected;
    string line;
    while (getline(cin, line)) {
        collected.push_back(line);
    }
    auto output = process(collected);
    cout << output << endl;
    return 0;
}