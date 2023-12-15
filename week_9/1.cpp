#include <iostream>
#include <vector>

int moreThanHalf(std::vector<int>& nums){ //O(n^2)
    std::vector<int> nums_v; //массив с числами, на повторение которых смотрим
    std::vector<int> rep_v; //массив с числом повторений этого элемента
    for(int i = 0; i < nums.size(); ++i){
        if (std::find(nums_v.begin(), nums_v.end(), nums[i]) == nums_v.end()) { //если число уже есть в массиве, то пропускаем его
            nums_v.push_back(nums[i]);
            int rep = 0; // число повторений
            for(int j = 0; j < nums.size(); ++j){
                if(nums[j] == nums[i]){
                    rep += 1;
                }
            }
            rep_v.push_back(rep);
        }
    }

    for(int i = 0; i < rep_v.size(); ++i){
        if(rep_v[i] > nums.size() / 2){
            return nums_v[i];
        }
    }
    std::cout << "no such element" << std::endl;
    return 0;
}

std::vector<int> moreThanThird(std::vector<int>& nums){ //O(n^2)
    std::vector<int> nums_v; //массив с числами, на повторение которых смотрим
    std::vector<int> rep_v; //массив с числом повторений этого элемента
    for(int i = 0; i < nums.size(); ++i){
        if (std::find(nums_v.begin(), nums_v.end(), nums[i]) == nums_v.end()) { //если число уже есть в массиве, то пропускаем его
            nums_v.push_back(nums[i]);
            int rep = 0; // число повторений
            for(int j = 0; j < nums.size(); ++j){
                if(nums[j] == nums[i]){
                    rep += 1;
                }
            }
            rep_v.push_back(rep);
        }
    }

    std::vector<int> answer; //массив с элементами, которые повторяются более 1/3 раз

    for(int i = 0; i < rep_v.size(); ++i){
        if(rep_v[i] > nums.size() / 3){
            answer.push_back(nums_v[i]);
        }
    }
    
    if(answer.size() == 0){
        std::cout << "no such elements" << std::endl;
    }

    return answer;
}

int main(){
    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(3);
    std::cout << moreThanHalf(nums) << std::endl;
}

