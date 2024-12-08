#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <tuple>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::getline;
using std::cin;
using std::pair;
using std::set;
using std::tie;
using std::stringstream;

// again bruteforce solution ( behind in days D: )
// some cool stuff :D
int solve(long long comp, vector<int> nums) {
    auto counter = 0;
    int n = nums.size() - 1;
    int totalStates = 1 << n;
   
    for (int state = 0; state < totalStates; state++) {
        long long result = nums[0];
       
        for (int pos = 0; pos < n; pos++) {
            if (state & (1 << pos)) {
                result *= nums[pos + 1];
            } else {
                result += nums[pos + 1];
            }
        }
       
        if (result == comp) {
            counter++;
        }
    }
   
    return counter;
}

// claude helped :D
int solve_part2(long long comp, vector<int> nums) {
    auto counter = 0;
    int n = nums.size() - 1;
    int totalStates = 1;
    for(int i = 0; i < n; i++) totalStates *= 3;
    
    for (int state = 0; state < totalStates; state++) {
        long long result = nums[0];
        string concat_str = std::to_string(nums[0]);
        int current_state = state;
        
        for (int pos = 0; pos < n; pos++) {
            int op = current_state % 3;
            current_state /= 3;
            
            if (op == 0) { 
                result = result + nums[pos + 1];
                concat_str = std::to_string(result);
            }
            else if (op == 1) {  
                result = result * nums[pos + 1];
                concat_str = std::to_string(result);
            }
            else { 
                concat_str += std::to_string(nums[pos + 1]);
                result = std::stoll(concat_str);
            }
        }
        
        if (result == comp) {
            counter++;
        }
    }
    
    return counter;
}


pair<long long, long long> handle_input(const vector<string>& lines) {
    long long counter = 0;
    long long counter2 = 0;
    for (const auto& line : lines) {
        auto colon_pos = line.find(':');
        if (colon_pos == string::npos) continue;
        
        auto total = std::stoll(line.substr(0, colon_pos));
        
        vector<int> nums; 
        std::istringstream iss(line.substr(colon_pos + 2));
        int num;
        while (iss >> num) {
            nums.push_back(num);
        }
        
        if (solve(total, nums) > 0) {
            counter += total;
        }
        if (solve_part2(total, nums) > 0) {
            counter2 += total;
        }
    }
    return {counter, counter2};
}

int main() {
    string line;
    vector<string> input;
    while (getline(cin, line)) {
        input.push_back(line);
    }
    auto out = handle_input(input);
    cout << out.first << " : " << out.second << endl;
    return 0;
}