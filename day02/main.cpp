#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

bool logic1(std::vector<int> n) {
    bool decreasing = n[1] < n[0];
    
    for (size_t i = 1; i < n.size(); i++) {
        int diff = abs(n[i] - n[i-1]);
        
        if (diff < 1 || diff > 3) return false;
        if (decreasing && n[i] >= n[i-1]) return false;
        if (!decreasing && n[i] <= n[i-1]) return false;
    }
    return true;
}

bool logic2(std::vector<int> n) {
    bool decreasing = n[1] < n[0];
    
    bool damper = false;
    for (size_t i = 1; i < n.size(); i++) {
        int diff = abs(n[i] - n[i-1]);
        
        if (diff < 1 || diff > 3) {
            if (damper) {
                return false;
            } else {
                damper = true;
            }
        }
        if (decreasing && n[i] >= n[i-1]) {
            if (damper) {
                return false;
            } else {
                damper = true;
            }
        };
        if (!decreasing && n[i] <= n[i-1]) {
            if (damper) {
                return false;
            } else {
                damper = true;
            }
        };
    }
    return true;
}

int main(int argc, char* argv[])
{   
    auto counter1 = 0;
    auto counter2 = 0;
    std::string line;
    while (std::getline(std::cin, line)) {

        std::vector<int> row;
        std::string alter = line;
        size_t pos = 0;
        while ((pos = alter.find(' ')) != std::string::npos) {
            row.push_back(atoi(alter.substr(0, pos).c_str()));
            alter = alter.substr(pos + 1);
        }
        if (!alter.empty()) {
            row.push_back(atoi(alter.c_str()));
        }
        
        if (logic1(row)) {
            counter1++;
        }
        if (logic2(row)) {
            counter2++;
        }
    }
    std::cout << counter1 << std::endl;
    std::cout << counter2 << std::endl;
    return 0;
}