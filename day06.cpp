#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#define DBG 0

bool isUnique(char* buf, const int bufSize = 4)
{
    bool foundEqual = false;
    //cout << "Buf: " << buf << endl;
    for(int i = 0; i < bufSize-1; i++)
    {
        for(int j = i+1; j < bufSize; j++)
        {
            //cout << buf[i] << " and " << buf[j] << endl;
            if(buf[i] == buf[j])
            {
                foundEqual = true;
                return !foundEqual;
            }
        }
    }
    return !foundEqual;
}

int getStartPos(string receiveBuffer, const int markerLength=4)
{
    int cnt = 0;
    char currentMark[markerLength];
    memset(currentMark, 0, markerLength);
    while(cnt < receiveBuffer.size() && (!isUnique(currentMark, markerLength) || cnt < markerLength))
    {
        for(int j = markerLength - 1; j > 0; j--)
        {
            currentMark[j] = currentMark[j-1];
        }
        currentMark[0] = receiveBuffer[cnt];
        cnt++;
    }
    return cnt;
}

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d6p1_ex.txt");
    #else
    f.open("inputs/d6p1.txt");
    #endif

    // Part 1
    string line;
    getline(f, line);
    auto ans1 = getStartPos(line);
    cout << "Answer part 1: " << ans1 <<  endl;
    auto ans2 = getStartPos(line, 14);
    cout << "Answer part 2: " << ans2 <<  endl;
    f.close();
    return 0;
}

