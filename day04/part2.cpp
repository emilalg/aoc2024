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

bool check(vector<string>& array, coord c) {
    int x,y;
    tie(x, y) = c;

    string w1 = "";
    w1 += array[y-1][x-1];
    w1 += array[y][x];
    w1 += array[y+1][x+1];

    string w2 = "";
    w2 += array[y-1][x+1];
    w2 += array[y][x];
    w2 += array[y+1][x-1];

    if (w1 == "MAS" || w1 == "SAM") {
        if (w2 == "MAS" || w2 == "SAM") {
            return true;
        }
    }
    return false;
}

int process(vector<string>& array) {
    auto width = array[0].size();
    auto height = array.size();
    auto counter = 0;
    vector<pair<coord, coord>> known;
    
    for (size_t row = 1; row < height-1; row++) {
        for (size_t col = 1; col < width-1; col++) {
            
            if (check(array, coord{col, row})) {
                counter++;
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