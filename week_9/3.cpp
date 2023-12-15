#include <iostream>
#include <list>
#include <algorithm>

int removeDuplicates(std::list<int>& nums){  //o(n)
    auto ptr = nums.begin();
    while(ptr != nums.end()){
        auto ptr_next = ++ptr; //здесь увеличили ptr
        ptr--; //здесь уменьшили ptr
        if(ptr_next != nums.end() and *ptr == *ptr_next){
            ptr = nums.erase(ptr);
        } else {
            ++ptr;
        }
    }
    return nums.size();
}


int main(){
    std::list<int> nums;
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(3);
    nums.push_back(3);
    nums.push_back(4);
    std::cout << removeDuplicates(nums);
}