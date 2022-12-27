#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int gameP1(char theirInput, char yourInput)
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

int gameP2(char theirInput, char gameResult)
{
    // select choice to get a result
    char yourInput;
    switch(gameResult){
        // draw
        case 'Y': yourInput = theirInput; break;
        // you loose
        case 'X':
            if(theirInput == 'A')
                yourInput = 'C';
            else if(theirInput == 'B')
                yourInput = 'A';
            else
                yourInput = 'B';
            break;
        // you win
        case 'Z':
            if(theirInput == 'A')
                yourInput = 'B';
            else if(theirInput == 'B')
                yourInput = 'C';
            else
                yourInput = 'A';
            break;
            break;
        default: break;
    }
    // translate yourInput to P1 assumption
    yourInput += 'X' - 'A';
    // calculate result in the same way as before
    return gameP1(theirInput, yourInput);
}

int main() {
    cout << "Start" << endl;
    std::ifstream f;

    for(int i = 0; i < 2; i++)
    {
        //f.open("inputs/d2p1_ex.txt");
        f.open("inputs/d2p1.txt");
        int myScore = 0;
        for(std::string line; std::getline(f, line); )
        {
            if(i == 0)
                myScore +=gameP1(line[0],line[2]);
            else
                myScore +=gameP2(line[0],line[2]);
        }

        cout << "Answer part " << i +1 << ": " << myScore << endl;
        f.close();
    }

    return 0;
}

