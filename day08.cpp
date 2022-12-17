#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <array>

using namespace std;

#define DBG 0

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    string fname = "inputs/d8p1_ex.txt";
    #else
    string fname = "inputs/d8p1.txt";
    #endif
    f.open(fname);

    // Part 1
    // find sizes
    int w, h=0;
    for(string line; getline(f, line); )
    {
        w = line.size();
        h++;
    }
    f.close();
    f.open(fname);
    const int heigth = h;
    const int width = w;
    int heigthMap[heigth][width], visibilityMap[heigth][width];
    memset(&heigthMap, 0, sizeof(heigthMap));
    memset(&visibilityMap, 0, sizeof(visibilityMap));
    h=0;
    // fill height map
    for(string line; getline(f, line); )
    {
        for(int j = 0 ; j< line.size(); j++)
        {
            string c = line.substr(j,1);
            heigthMap[h][j] = stoi(c, 0);
        }
        h++;
    }
    // fill visibility map
    for(int i = 0; i < heigth; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // for each position
            bool stillVisible = true;
            // fill border
            if(i == 0 || j == 0 || i == heigth-1 || j == width-1)
            {
                visibilityMap[i][j] = 1;
            }
            // visibility from top
            for(int k = 0; k < i; k++)
            {
                if(heigthMap[i][j] <= heigthMap[k][j])
                {
                    stillVisible = false;
                }
            }
            if(stillVisible)
            {
                visibilityMap[i][j] += 1;
            }
            stillVisible = true;
            // visibility from bottom
            for(int k = heigth-1; k > i; k--)
            {
                if(heigthMap[i][j] <= heigthMap[k][j])
                {
                    stillVisible = false;
                }
            }
            if(stillVisible)
            {
                visibilityMap[i][j] += 2;
            }
            stillVisible = true;
            // visibility from left
            for(int k = 0; k < j; k++)
            {
                if(heigthMap[i][j] <= heigthMap[i][k])
                {
                    stillVisible = false;
                }
            }
            if(stillVisible)
            {
                visibilityMap[i][j] += 4;
            }
            stillVisible = true;
            // visibility from right
            for(int k = width-1; k > j; k--)
            {
                if(heigthMap[i][j] <= heigthMap[i][k])
                {
                    stillVisible = false;
                }
            }
            if(stillVisible)
            {
                visibilityMap[i][j] += 8;
            }
        }
    }
    // count visibility map entries
    int ans1 = 0;
    for(int i = 0; i < heigth; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(visibilityMap[i][j])
                ans1++;
        }
    }

    cout << "Answer part 1: " << ans1 << endl;
    f.close();
    return 0;
}

