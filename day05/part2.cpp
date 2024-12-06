#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <tuple>
#include <algorithm>
using std::string;
using std::vector;
using std::getline;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::tie;
using std::stringstream;

bool compareByRules(int a, int b, const vector<pair<string, string>>& rules) {
    for (const auto& rule : rules) {
        int first = stoi(rule.first);
        int second = stoi(rule.second);
        if (a == first && b == second) return true;
        if (a == second && b == first) return false;
    }
    return a < b; 
}

pair<int, int> handle(vector<string>& input) {
    vector<pair<string, string>> rules;
    auto total = 0;
    auto total2 = 0;
    for (auto i: input) {
        if (i.empty() || i.length() == 1 || i.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        } else if (i.find_first_of('|') != string::npos) {
            auto index = i.find_first_of('|');
            auto p1 = i.substr(0, index);
            auto p2 = i.substr(index+1, i.length());
            rules.push_back({p1, p2});
        } else {
            vector<int> nums;
            stringstream ss(i);
            string temp;
            while (getline(ss, temp, ',')) {
                nums.push_back(stoi(temp));
            }
            
            bool allowed = true;
            for(const auto& rule : rules) {
                int n1 = stoi(rule.first);
                int n2 = stoi(rule.second);
                
                auto pos1 = string::npos;
                auto pos2 = string::npos;
                
                for(size_t idx = 0; idx < nums.size(); idx++) {
                    if(nums[idx] == n1) pos1 = idx;
                    if(nums[idx] == n2) pos2 = idx;
                }
                
                if(pos1 != string::npos && pos2 != string::npos && pos1 >= pos2) {
                    allowed = false;
                    break;
                }
            }
            
            if (allowed) {
                total += nums[nums.size() / 2];
            } else {
                vector<int> sorted_nums = nums;
                std::sort(sorted_nums.begin(), sorted_nums.end(), 
                    [&rules](int a, int b) { return compareByRules(a, b, rules); });
                total2 += sorted_nums[sorted_nums.size() / 2];
            }
        }
    }
    return {total, total2};
}

int main() {
    string line;
    vector<string> input;
   
    while (getline(cin, line)) {
        input.push_back(line);
    }
    auto out = handle(input);
    cout << out.first << endl;
    cout << out.second << endl;
}