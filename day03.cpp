#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

#define DBG 0

char checkRucksack(string rucksack)
{
    if(rucksack.length() % 2 == 1)
    {
        cerr << "Uneven length rucksack: " << rucksack << endl;
        return '1'; // unprioritized char
    }
    string compartment1 = rucksack.substr(0, rucksack.length()/2);
    string compartment2 = rucksack.substr(rucksack.length()/2,rucksack.length()/2);
    for(int i=0; i < compartment1.length(); i++)
    {
        if(compartment2.find(compartment1[i]) != string::npos)
        {
            // stop at first found
            return compartment1[i];
        }
    }
    return '1'; // unprioritized char
}

int getPriority(char c)
{
    int p = 0;
    if(c >= 'a' && c <= 'z')
        p = c - 'a' + 1;
    else if(c >= 'A' && c <= 'Z')
        p = 27 + c - 'A';
    return p;
}

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d3p1_ex.txt");
    #else
    f.open("inputs/d3p1.txt");
    #endif

    queue<char> duplicateItems;
    int prioSum = 0;
    for(std::string line; std::getline(f, line); )
    {
        char c = checkRucksack(line);
        duplicateItems.push(c);
        prioSum += getPriority(c);
        #if DBG 
            cout << c << " in line " << line << endl; 
        #endif
    }

    cout << "Answer part 1: " << prioSum << endl;
    f.close();
    return 0;
}

