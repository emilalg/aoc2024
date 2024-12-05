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

int handle(vector<string>& input) {

    vector<pair<string, string>> rules;
    auto total = 0;

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
                        allowed = false;
                        break;
                    }
                }
            }
            
            if (allowed) {
                total += nums[nums.size() / 2];
            }
        }
    }
    return total;

}

int main() {
    string line;
    vector<string> input;
    
    while (getline(cin, line)) {
        input.push_back(line);
    }
    auto out = handle(input);
    cout << out << endl;
}