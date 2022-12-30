#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <utility>
#include <cstdint>
#include <cinttypes>

using namespace std;

#define DBG 0

typedef int64_t nrType;

nrType pow(const int base, const nrType power)
{
    nrType val = 1;
    for(int i = 0; i < power; i++)
    {
        val *= base;
    }
    return val;
}

// Helper voor staartdeling, factorial voor 5 machten
nrType f5(const int power)
{
    nrType ans = 0;
    for(int i = 0; i <= power; i++)
    {
        ans += ((nrType)2)*pow(5, i);
    }
    return ans;
}

// Staartdeling achtig
string intToSnafu(const nrType iNumber)
{
    nrType rest = iNumber;
    const array<pair<const int, const char>, 5> values = {
        make_pair(0, '0'),
        make_pair(1, '1'),
        make_pair(2, '2'),
        make_pair(-1, '-'),
        make_pair(-2, '=')};
    int curExp = 0;
    nrType nrToSubtract = 0;
    nrType minDif = 0;
    string retval = "";
    bool done = false;
    while(imaxabs(rest) > f5(curExp))
    {
        curExp++;
    }
    const int maxExp = curExp;
    while(curExp > -1 || done == false)
    {
        nrToSubtract = 0;
        minDif = INT64_MAX;
        char c = '0';
        for (const auto& m: values)
        {
            const nrType nr = ((nrType)m.first) * pow(5, curExp);
            if(imaxabs(rest - nr) < imaxabs(minDif))
            {
                minDif = rest - nr;
                nrToSubtract = nr;
                c = m.second;
            }
        }
        retval += c;

        //cout << endl;
        //cout << "Exponent: " << curExp << endl;
        //cout << "From\t\t" << rest << endl;
        //cout << "Subtract\t" << nrToSubtract << endl;
        rest -= nrToSubtract;
        //cout << "Result\t\t" << rest << endl;
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
    //cout << "test: " << intToSnafu(SnafuToInt("2002")) << endl;
    cout << "Answer part 1: " << sum << " (sum), and in SNAFU: " << intToSnafu(sum) << endl;
    f.close();
    return 0;
}

