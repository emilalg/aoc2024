#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <tuple>

using std::string;
using std::vector;
using std::getline;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::tie;
using std::stringstream;

pair<int, int> handle(vector<string>& input) {

    vector<pair<string, string>> rules;
    auto total = 0;
    auto total2 = 0;

    for (auto i: input) {
        if (i.empty() || i.length() == 1 || i.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        } else if (i.find_first_of('|') != string::npos) {
            // handle rule
            auto index = i.find_first_of('|');
            auto p1 = i.substr(0, index);
            auto p2 = i.substr(index+1, i.length());
            rules.push_back({p1, p2});
        } else {
            auto allowed = true;
            vector<int> nums;
            vector<pair<vector<int>, pair<int, int>>> broken_rules;
            stringstream ss(i);
            string temp;
            while (getline(ss, temp, ',')) {
                nums.push_back(stoi(temp));
            }
            for (auto j: rules) {
                string p1,p2;
                tie(p1, p2) = j;
                int n1 = stoi(p1);
                int n2 = stoi(p2);
                
                auto pos1 = string::npos;
                auto pos2 = string::npos;
                
                for(size_t idx = 0; idx < nums.size(); idx++) {
                    if(nums[idx] == n1) pos1 = idx;
                    if(nums[idx] == n2) pos2 = idx;
                }
                
                if(pos1 != string::npos && pos2 != string::npos) {
                    if(pos1 >= pos2) {
                        broken_rules.push_back({nums, {n1, n2}});
                        allowed = false;
                        continue;
                    }
                }
            }
            if (broken_rules.size() != 0) {
                vector<int> fixed_nums = nums; 
                for (auto j: broken_rules) {
                    vector<int> temp_nums;
                    pair<int, int> rule;
                    tie(temp_nums, rule) = j;
                    int rule_first, rule_second;
                    tie(rule_first, rule_second) = rule; 

                    int pos1 = -1, pos2 = -1;
                    for(size_t i = 0; i < fixed_nums.size(); i++) {
                        if(fixed_nums[i] == rule_first) pos1 = i;
                        if(fixed_nums[i] == rule_second) pos2 = i;
                    }

                    if(pos1 != -1 && pos2 != -1 && pos1 > pos2) {
                        int temp = fixed_nums[pos1];
                        for(int i = pos1; i > pos2; i--) {
                            fixed_nums[i] = fixed_nums[i-1];
                        }
                        fixed_nums[pos2] = temp;
                    }
                }
                total2 += fixed_nums[fixed_nums.size() / 2]; 
            } else if (allowed) {
                total += nums[nums.size() / 2];
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