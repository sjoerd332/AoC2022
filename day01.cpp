#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

void printCalories(std::vector<std::list<int>>& aTotal) {
    for (const auto& i: aTotal){
        for (const auto& j: i) {
            std::cout << j << ' ';
        }
        std:: cout << '\n';
    }
}

int main(){
    std::cout << "Start" << std::endl;
    std::ifstream f;
    //f.open("inputs/d1p1_ex.txt");
    f.open("inputs/d1p1.txt");
    
    std::vector<std::list<int>> Elves;
    Elves.push_back(std::list<int>());
    for (std::string line; std::getline(f, line); ) {
        //std::cout << line << std::endl;
        if(line.size() == 0) {
            Elves.push_back(std::list<int>());
        }
        else {
            std::list<int>& calories = Elves.back();
            calories.push_back(std::stoi(line));
        }
    }

    //printCalories(Elves);
    
    int maxSum = 0;
    // get elf with maximum calories
    for(auto& i: Elves) {
        int myElfSum = 0;
        for (const auto& j: i) {
            myElfSum +=j;
        }
        if(myElfSum > maxSum) 
            maxSum = myElfSum;
    }

    std::cout << "Answer part 1: " << maxSum;

    return 0;
}

