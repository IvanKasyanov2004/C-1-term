#include <iostream>
#include <vector>
#include <algorithm>

void print(std::vector<int> nums){
    for(int i = 0; i < nums.size(); ++i){
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
}

void quickSort(std::vector<int>& arr, std::vector<int>& indexes, int left, int right){ //переставляет также индексы  O(n logn)
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
 
    //разбиение
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            std::swap(indexes[i], indexes[j]);
            i++;
            j--;
        }
    };
 
    //рекурсия
    if (left < j)
        quickSort(arr, indexes, left, j);
    if (i < right)
        quickSort(arr, indexes, i, right);
    
}

std::vector<int> twoSum(std::vector<int>& nums, int target){  //O(n logn)
    std::vector<int> nums_s; //сортированный вектор nums
    for(int i = 0; i < nums.size(); ++i){
        nums_s.push_back(nums[i]);
    }
    std::vector<int> indexes; //вектор изначальных индексов в неотсортированном массиве
    for(int i = 0; i < nums.size(); ++i){
        indexes.push_back(i);
    }
    quickSort(nums_s, indexes, 0, nums.size() - 1); //O(n logn)
    
    std::vector<int> idx_s; //вектор с индексами в сортированном масииве (idx_sort)
    idx_s.push_back(0);
    idx_s.push_back(nums.size() - 1);
    std::vector<int> idx_u; //вектор с индексами в несортированном масииве (idx_unsort)
    idx_u.push_back(indexes[0]);
    idx_u.push_back(indexes[nums.size() - 1]);

    int i = 0;
    int j = nums.size() - 1;

    while(i < j){   //O(n)
        int sum = nums_s[i] + nums_s[j];
        if(sum == target){
            std::vector<int> idx; //вектор с индексами в несортированном масииве (idx_unsort)
            idx.push_back(indexes[i]);
            idx.push_back(indexes[j]);
            return idx;
        }
        if(sum < target){
            i += 1;
        }
        if(sum > target){
            j -= 1;
        }
    }
}

int main(){
    std::vector<int> nums;
    nums.push_back(5);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(10);
    std::vector<int> idx = twoSum(nums, 15);
    print(nums);
    print(idx);
}