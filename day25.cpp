#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <array>
#include <utility>
#include <cstdint>

using namespace std;

#define DBG 0

typedef int64_t nrType;

nrType pow(const int base, const int power)
{
    nrType val = (unsigned long long) 1;
    for(int i = 0; i < power; i++)
    {
        val *= base;
    }
    return val;
}

// helper voor staartdeling, factorial voor 5 machten
nrType f5(const int power)
{
    nrType ans = (unsigned long long) 0;
    for(int i = 0; i <= power; i++)
    {
        ans += ((nrType)2)*pow(5, i);
    }
    return ans;
}

// Alternative: staartdeling achtig
string intToSnafu(const nrType iNumber)
{
    nrType rest = iNumber;
    const array<pair<const int, const char>, 5> values = {
        make_pair(0, '0'),
        make_pair(1, '1'),
        make_pair(2, '2'),
        make_pair(-1, '-'),
        make_pair(-2, '=')}; // order matters for iteration
    int curExp = 0;
    nrType nrToSubtract = 0;
    string retval = "";
    bool done = false;
    while(abs(rest) > f5(curExp))
    {
        curExp++;
    }
    const int maxExp = curExp;
    while(curExp > -1 || done == false)
    {
        nrToSubtract = 0;
        bool subtracted  = false;
        for (const auto& m: values)
        {
            const nrType nr = m.first * pow(5, curExp);
            if(((rest >= 0 && (nr >= rest || m.first == 2)) || (rest < 0 && (nr <= rest || m.first == -2))) && subtracted == false)
            {
                nrToSubtract = nr;
                retval += m.second;
                subtracted = true;
            }
        }
        if(subtracted == false)
        {
            retval += values[0].second;
        }
        rest -= nrToSubtract;
        curExp--;
        if(curExp == -1)
            done = true;
    }
    if(rest != 0)
            cout << endl << "Error: rest is not zero: " << rest << endl << endl;
    if(retval.size() == 0)
        retval = values[0].second;
    return retval;
}

nrType SnafuToInt(const string sNumber)
{
    nrType val = 0;
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
    nrType sum = 0;
    for(string line; getline(f, line); )
    {
        sum += SnafuToInt(line);
    }
    //cout << "test: " << SnafuToInt("1=1") << endl;
    cout << "Answer part 1: " << sum << " (sum), and in SNAFU: " << intToSnafu(sum) << endl;
    f.close();
    return 0;
}

