#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

#define DBG 0

void printSizes(stack<char>* stacks, int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << "Stack " << i << " size " << stacks[i].size() << endl;
    }
}

void printTops(stack<char>* stacks, int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << stacks[i].top();
    }
    cout << endl;
}

void moveCrane9000(stack<char> &fromStack, stack<char> &toStack, int amountOfCrates)
{
    for(int i = 0; i < amountOfCrates; i++)
    {
        char c = fromStack.top();
        toStack.push(c);
        fromStack.pop();
    }
}

void moveCrane9001(stack<char> &fromStack, stack<char> &toStack, const int amountOfCrates)
{
    char c[amountOfCrates];
    for(int i = 0; i < amountOfCrates; i++)
    {
        c[i] = fromStack.top();
        fromStack.pop();
    }
    for(int i = amountOfCrates-1; i >=0; i--)
    {
        toStack.push(c[i]);
    }
}

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d5p1_ex.txt");
    #else
    f.open("inputs/d5p1.txt");
    #endif

    int nrOfStacks = 0;
    int maxInputStackHeight = 0;
    string inputStacks;
    // Part 1 and 2
    // partially read input
    for(string line; getline(f, line); )
    {
        if(nrOfStacks == 0)
        {
            nrOfStacks = (line.size()+1) / 4;
        }
        if(line.find('[') != string::npos)
        {
            maxInputStackHeight++;
            inputStacks.append(line);
            inputStacks.append(" ");
        }
        else
            break;
    }
    //#if DBG
    cout << inputStacks << endl;
    //#endif

    // process input stacks
    stack<char> stacks[nrOfStacks];
    for(int i = inputStacks.size(); i>=0; i--)
    {
        char c = inputStacks[i];
        if(c >= 'A' && c <= 'Z')
        {
            //int stackNr = ((i + 2) % (4 * nrOfStacks));
            // +2, 1 for index, 1 for [ char.
            int stackNr = (i + 2 - ( i / (nrOfStacks * 4)) * (nrOfStacks * 4)) /4;
            int stackHeight = maxInputStackHeight - 1 - ( i / (nrOfStacks * 4));
            stacks[stackNr].push(c);
        }
    }
    stack<char> stacksP2[nrOfStacks];
    for(int i = 0; i < nrOfStacks; i++)
    {
        stacksP2[i] = stacks[i];
    }

    // read empty line
    string line; getline(f, line);
    // read crane commands
    for(string line; getline(f, line); )
    {
        //cout << line << endl;
        int move = line.find("move");
        int from = line.find("from");
        int to   = line.find("to");
        int amount = stoi(line.substr(move+5, from - (move+5)));
        int stackFrom = stoi(line.substr(from+5, to - (from+5))) -1;
        int stackTo = stoi(line.substr(to+2, line.size() - (to+2))) - 1;
        //printSizes(stacks, nrOfStacks);
        moveCrane9000(stacks[stackFrom], stacks[stackTo], amount);
        moveCrane9001(stacksP2[stackFrom], stacksP2[stackTo], amount);
    }

    cout << "Answer part 1: ";
    printTops(stacks, nrOfStacks);
    cout << "Answer part 2: ";
    printTops(stacksP2, nrOfStacks);
    f.close();
    return 0;
}

