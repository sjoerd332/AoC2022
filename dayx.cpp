#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define DBG 1

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/dxp1_ex.txt");
    #else
    f.open("inputs/dxp1.txt");
    #endif

    // Part 1
    for(string line; getline(f, line); )
    {

    }

    cout << "Answer part 1: " << endl;
    f.close();
    return 0;
}

