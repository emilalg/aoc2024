#include <iostream>
#include <vector>
#include <string>
#include <map>

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

    int get_file_size(int file_id) {
        int size = 0;
        for (int block : disk_state) {
            if (block == file_id) size++;
        }
        return size;
    }
    
    int find_leftmost_space(int required_size, int current_start) {
        int consecutive_spaces = 0;
        int space_start = -1;
        
        for (size_t i = 0; i < disk_state.size(); i++) {
            if (disk_state[i] == -1) {
                if (consecutive_spaces == 0) space_start = i;
                consecutive_spaces++;
                if (consecutive_spaces >= required_size) {
                    if (space_start < current_start) {
                        return space_start;
                    }
                }
            } else {
                consecutive_spaces = 0;
                space_start = -1;
            }
        }
        return -1;
    }
    
    int get_file_start(int file_id) {
        for (size_t i = 0; i < disk_state.size(); i++) {
            if (disk_state[i] == file_id) return i;
        }
        return -1;
    }
    
    void move_file(int file_id, int new_pos) {
        std::vector<int> new_state = disk_state;
        int file_size = get_file_size(file_id);
        
        for (int& block : new_state) {
            if (block == file_id) block = -1;
        }
        
        for (int i = 0; i < file_size; i++) {
            new_state[new_pos + i] = file_id;
        }
        
        disk_state = new_state;
    }
    
    void compact_disk() {
        int max_file_id = 0;
        for (int block : disk_state) {
            if (block > max_file_id) max_file_id = block;
        }
        
        for (int file_id = max_file_id; file_id >= 0; file_id--) {
            int file_size = get_file_size(file_id);
            if (file_size == 0) continue;  
            
            int current_start = get_file_start(file_id);
            int new_pos = find_leftmost_space(file_size, current_start);
            
            if (new_pos != -1) {
                move_file(file_id, new_pos);
            }
        }
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