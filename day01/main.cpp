#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main(int argc, char* argv[])
{   
    // initial code

    std::vector<int> c1;
    std::vector<int> c2;

    std::string line;
    while (std::getline(std::cin, line)) {
        c1.push_back(atoi(line.substr(0, line.find(' ')).c_str()));
        c2.push_back(atoi(line.substr(line.find_last_of(' ') + 1).c_str()));
    }

    std::sort(c1.begin(), c1.end());
    std::sort(c2.begin(), c2.end());

    // 1st score

    auto diff = 0;
    for (size_t i = 0; i < c1.size(); i++) {
        auto temp = c1[i] - c2[i];
        if (temp < 0) {
            temp = temp * -1;
        }
        diff += temp;
    }
    std::cout << diff << std::endl;

    // similarity score part

    std::unordered_map<int, int> similarities;
    auto total = 0;
    for (size_t i = 0; i < c1.size(); i++) {
        if (similarities.find(c1[i]) == similarities.end()) {
            int count = 0;
            for (size_t j = 0; j < c2.size(); j++) {
                if (c1[i] == c2[j]) {
                    count++;
                }
            }
            similarities[c1[i]] = count;
        }
        total += c1[i] * similarities[c1[i]];
    }
    std::cout << total << std::endl;

    return 0;
}