#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int game(char theirInput, char yourInput)
{
    int score = 0;
    switch(yourInput) { 
    case 'X': score += 1; break;
    case 'Y': score += 2; break;
    case 'Z': score += 3; break;
    default: break;
    };

    // Rock, paper, scissors, or  A, B, C, or X, Y, Z.
    int cmp = yourInput - theirInput - ('X' - 'A');
    if(cmp == 0)
    {
        // draw
        score += 3;
    }
    else if(cmp == -2 || cmp == 1)
    {
        // win (-2 for rock vs scissors, 1 for paper vs scissors and 1 for rock vs paper
        score += 6;
    }

    return score;
}

int main() {
    cout << "Start" << endl;
    // Part 1
    std::ifstream f;
    //f.open("inputs/d2p1_ex.txt");
    f.open("inputs/d2p1.txt");

    int myScore = 0;
    for(std::string line; std::getline(f, line); )
    {
        myScore += game(line[0],line[2]);
    }
    
    cout << "Answer part 1: " << myScore;

    return 0;
}

