#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> disk_state; 
    
    void read_in(const std::string& line) {
        size_t pos = 0;
        int file_id = 0;
        
        while (pos < line.length()) {
            int file_size = line[pos] - '0';
            
            for (int i = 0; i < file_size; i++) {
                disk_state.push_back(file_id);
            }
            
            pos++;
            if (pos < line.length()) {
                int space_size = line[pos] - '0';
                for (int i = 0; i < space_size; i++) {
                    disk_state.push_back(-1);
                }
                pos++;
            }
            file_id++;
        }
    }
    
    void compact_disk() {
        bool moved;
        do {
            moved = false;
            int rightmost_pos = -1;
            for (int i = disk_state.size() - 1; i >= 0; i--) {
                if (disk_state[i] != -1) {
                    rightmost_pos = i;
                    break;
                }
            }
            
            if (rightmost_pos == -1) break;
            
            int leftmost_space = -1;
            for (size_t i = 0; i < disk_state.size(); i++) {
                if (disk_state[i] == -1) {
                    leftmost_space = i;
                    break;
                }
            }
            
            if (leftmost_space != -1 && rightmost_pos > leftmost_space) {
                disk_state[leftmost_space] = disk_state[rightmost_pos];
                disk_state[rightmost_pos] = -1;
                moved = true;
            }
        } while (moved);
    }
    
    long long calculate_checksum() {
        long long checksum = 0;
        for (size_t i = 0; i < disk_state.size(); i++) {
            if (disk_state[i] != -1) {
                checksum += static_cast<long long>(i) * disk_state[i];
            }
        }
        return checksum;
    }
    
    void print_state() {
        for (int id : disk_state) {
            if (id == -1) std::cout << ".";
            else std::cout << id;
        }
        std::cout << std::endl;
    }
};

int main() {
    std::string line;
    std::getline(std::cin, line);

    Solution solution;
    solution.read_in(line);
    solution.compact_disk();
    std::cout << solution.calculate_checksum() << std::endl;

    return 0;
}