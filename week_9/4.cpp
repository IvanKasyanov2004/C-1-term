#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector <std::vector<std::string> > groupByName(std::vector<std::string>& strs){ //o(n)
    std::unordered_map< std::string, std::vector<std::string> > hash_map;
    for (int i = 0; i < strs.size(); ++i) {  // o(n)
        std::string sorted_str = strs[i];
        std::sort(sorted_str.begin(), sorted_str.end()); //o(a loga) (a - длина строки) 
        hash_map[sorted_str].push_back(strs[i]);
    }

    std::vector< std::vector<std::string> > result;
    for (auto it = hash_map.begin(); it != hash_map.end(); ++it) {  //o(n)
        result.push_back(it->second);
    }

    return result;
}

int main() {
    std::vector<std::string> strs;
    strs.push_back("eat");
    strs.push_back("tea");
    strs.push_back("tan");
    strs.push_back("ate");
    strs.push_back("nat");
    strs.push_back("bat");
    std::vector< std::vector<std::string> > result = groupByName(strs);
    std::cout << result[0][0];
    std::cout << result[1][0];
    std::cout << result[2][0];
    return 0;
}