#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const char allowed[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ','};

int handle_mul(const std::string& s) {

    for(auto c : s) {
        if(std::find(std::begin(allowed), std::end(allowed), c) == std::end(allowed)) {
            return 0;
        }
    }

    if (s.find("mul(") != std::string::npos) {
        return 0;
    }

    if (s.find_first_of(',') != s.find_last_of(',') || s.find_first_of(',') == 0) {
        return 0;
    }
   
    auto sep = s.find(',');
    auto num1 = s.substr(0, sep);
    auto num2 = s.substr(sep+1);
   
    if(num1.length() < 1 || num1.length() > 3 || 
       num2.length() < 1 || num2.length() > 3) {
        return 0;
    }
   
    return std::stoi(num1) * std::stoi(num2);
}

void process_line(const std::string& line, int& basic_sum, int& conditional_sum, bool& enabled) {
    size_t pos = 0;
    
    while (pos < line.length()) {
        if (line.substr(pos).find("do()") == 0) {
            enabled = true;
            pos += 4;
            continue;
        }
        if (line.substr(pos).find("don't()") == 0) {
            enabled = false;
            pos += 7;
            continue;
        }
        if (line.substr(pos).find("mul(") == 0) {
            auto sub = line.substr(pos + 4);
            auto close_pos = sub.find(')');
            if (close_pos != std::string::npos) {
                auto result = handle_mul(sub.substr(0, close_pos));
                basic_sum += result;
                if (enabled) {
                    conditional_sum += result;
                }
            }
        }
        pos++;
    }
}

int main() {
    std::string line;
    int basic_sum = 0, conditional_sum = 0;
    bool enabled = true;  
    
    while (std::getline(std::cin, line)) {
        process_line(line, basic_sum, conditional_sum, enabled);
    }
    
    std::cout << "P1: " << basic_sum << std::endl;
    std::cout << "P2: " << conditional_sum << std::endl;
    return 0;
}