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

    // Part 1
    queue<char> duplicateItems;
    int prioSumP1 = 0;
    for(string line; getline(f, line); )
    {
        char c = checkRucksack(line);
        duplicateItems.push(c);
        prioSumP1 += getPriority(c);
        #if DBG 
            cout << c << " in line " << line << endl; 
        #endif
    }
    cout << "Answer part 1: " << prioSumP1 << endl;
    f.close();

    // Part 2
    #if DBG
    f.open("inputs/d3p1_ex.txt");
    #else
    f.open("inputs/d3p1.txt");
    #endif
    int prioSumP2 = 0;
    int currentGroup = 0;
    int doneGroup = 0;
    for(string l1; getline(f, l1); )
    {
        string l2, l3;
        getline(f, l2);
        getline(f, l3);
        currentGroup +=1;
        #if DBG 
            cout << "Lines: " << l1 << " " << l2 << " " << l3 << endl; 
        #endif
        char c;
        for(int i = 0; i < l3.size(); i++)
        {
            if(l2.find(l3[i]) != string::npos && l2.find(l3[i]) != -1)
            {
                if(l1.find(l3[i]) != string::npos && l1.find(l3[i]) != -1)
                {
                    if(currentGroup != doneGroup)
                    {
                        c = l3[i];
                        prioSumP2 += getPriority(c);
                        doneGroup = currentGroup;
                    }
                }
            }
        }
    }

    cout << "Answer part 2: " << prioSumP2 << endl;
    f.close();
    return 0;
}

