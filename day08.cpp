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
    const int height = h;
    const int width = w;
    int heightMap[height][width], visibilityMap[height][width];
    memset(&heightMap, 0, sizeof(heightMap));
    memset(&visibilityMap, 0, sizeof(visibilityMap));
    h=0;
    // fill height map
    for(string line; getline(f, line); )
    {
        for(int j = 0 ; j< line.size(); j++)
        {
            string c = line.substr(j,1);
            heightMap[h][j] = stoi(c, 0);
        }
        h++;
    }
    // fill visibility map
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // for each position
            bool stillVisible = true;
            // fill border
            if(i == 0 || j == 0 || i == height-1 || j == width-1)
            {
                visibilityMap[i][j] = 1;
            }
            // visibility from top
            for(int k = 0; k < i; k++)
            {
                if(heightMap[i][j] <= heightMap[k][j])
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
            for(int k = height-1; k > i; k--)
            {
                if(heightMap[i][j] <= heightMap[k][j])
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
                if(heightMap[i][j] <= heightMap[i][k])
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
                if(heightMap[i][j] <= heightMap[i][k])
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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(visibilityMap[i][j])
                ans1++;
        }
    }

    cout << "Answer part 1: " << ans1 << endl;

    // Part 2
    // fill scenic map
    int scenicMap[height][width];
    memset(&scenicMap, 0, sizeof(scenicMap));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int l=1,r=1,u=1,d=1;
            while(heightMap[i][j] > heightMap[i][j-l] && j-l >= 1)
            {
                l++;
            }
            while(heightMap[i][j] > heightMap[i][j+r] && j+r <= width-2)
            {
                r++;
            }
            while(heightMap[i][j] > heightMap[i-u][j] && i-u >= 1)
            {
                u++;
            }
            while(heightMap[i][j] > heightMap[i+d][j] && i+d <= height-2)
            {
                d++;
            }
            scenicMap[i][j] = l*r*u*d;
        }
    }
    // find maximum
    int max = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(scenicMap[i][j] > max)
                max = scenicMap[i][j];
        }
    }
    cout << "Answer part 2: " << max << endl;

    f.close();
    return 0;
}

