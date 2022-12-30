#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <array>
#include <utility>

using namespace std;

#define DBG 0

int pow(const int base, const int power)
{
    int val = 1;
    for(int i = 0; i < power; i++)
    {
        val *= base;
    }
    return val;
}

// helper voor staartdeling, factorial voor 5 machten
int f5(const int power)
{
    int ans = 0;
    for(int i = 0; i <= power; i++)
    {
        ans += 2*pow(5, i);
    }
    return ans;
}

// Alternative: staartdeling achtig
string intToSnafu3(const int iNumber)
{
    int rest = iNumber;
    const array<pair<const int, const char>, 5> values = {
        make_pair(0, '0'),
        make_pair(1, '1'),
        make_pair(2, '2'),
        make_pair(-1, '-'),
        make_pair(-2, '=')}; // order matters for iteration
    int maxExp = 0;
    int curExp = 0;
    int nrToSubtract = 0;
    string retval = "";
    bool done = false;
    while(curExp > -1 || done == false)
    {
        nrToSubtract = 0;
        if(abs(rest) > f5(curExp))
        {
            curExp++;
        }
        else
        {
            bool subtracted  = false;
            for (const auto& m: values)
            {
                const int nr = m.first * pow(5, curExp);
                if(((rest >= 0 && (nr >= rest || m.first == 2)) || (rest < 0 && (nr <= rest || m.first == -2))) && subtracted == false)
                {
                    nrToSubtract = nr;
                    retval += m.second;
                    subtracted = true;
                }
            }
            rest -= nrToSubtract;
            curExp--;
            if(curExp == -1)
                done = true;
        }
        if(curExp > maxExp)
            maxExp = curExp;
    }
    if(rest != 0)
            cout << "Error: rest is not zero: " << rest << endl;
    if(retval.size() == 0)
        retval = values[0].second;
    return retval;
}

int SnafuToInt(const string sNumber)
{
    int val = 0;
    int stringPos = sNumber.size()-1;
    int powerPos = 0;
    while(stringPos >= 0)
    {
        char c = sNumber.at(stringPos);
        switch(c)
        {
            case '2':
                val += 2 * pow(5, powerPos);
                break;
            case '1':
                val += pow(5, powerPos);
                break;
            case '0':
                break;
            case '-':
                val -= pow(5, powerPos);
                break;
            case '=':
                val -= 2 * pow(5, powerPos);
                break;
            default:
                break;
        };
        powerPos++;
        stringPos--;
    }
    return val;
}

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d25p1_ex.txt");
    #else
    f.open("inputs/d25p1.txt");
    #endif

    // Part 1
    int sum = 0;
    for(string line; getline(f, line); )
    {
        sum += SnafuToInt(line);
    }
    cout << "test: " << SnafuToInt("1=1") << endl;
    cout << "Answer part 1: " << sum << " (sum), and in SNAFU: " << intToSnafu3(sum) << endl;
    f.close();
    return 0;
}

