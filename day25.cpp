#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

#define DBG 1

int pow(int base, int power)
{
    int val = 1;
    for(int i = 0; i < power; i++)
    {
        val *= base;
    }
    return val;
}

void borrow(string& s, const int sNumberOffset, int& nr)
{
    if(nr > pow(5, s.size()+sNumberOffset))
    {
        cout << "Larger remainder than extracted SNAFU" << endl;
        s = "1" + s;
    }
    else
    {
        // nr = 20 would be 4*5, or 25 - 5
        const size_t pos = s.size()-1;
        if(s[pos] == '=')
            s[pos] = '-';
        else if(s[pos] == '-')
            s[pos] = '0';
        else if(s[pos] == '0')
            s[pos] = '1';
        else if(s[pos] == '1')
            s[pos] = '2';
        else if(s[pos] == '2')
        {
            string s2 = s.substr(0, pos);
            borrow(s2, sNumberOffset + 1, nr);
            s = s2;
        }
    }
}

string intToSnafu(const int iNumber)
{
    // check how many SNAFU symbols are required
    int temp = iNumber;
    int nrOfPosses = 0;
    while(temp > 0)
    {
        nrOfPosses++;
        temp /=5;
    }
    temp = iNumber;
    int reconstructedNumber = 0;
    string sNumber = "";
    for(int i = nrOfPosses; i >0; i--)
    {
        int base = pow(5,i);
        int div = (temp + 2*base) / base;
        int rem = temp % base;
        if(div == 4)
        {
            sNumber.append("2");
            temp -= 2 * base;
        }
        else if(div == 3)
        {
            sNumber.append("1");
            temp -= base;
        }
        else if(div == 2)
        {
            sNumber.append("0");
        }
        else if(div == 1)
        {
            sNumber.append("-");
            temp = temp + base + 5*base;
        }
        else if(div == 0)
        {
            sNumber.append("=");
            temp = temp + 2 * base + 5*base;
        }
        else
        {
            // Division was not possible, borrow at bigger nrs
            borrow(sNumber, i+1, temp);
        }
    }

    // if(temp !=0)
    //     cout << temp << endl;
    return sNumber;
}

// An alternative way of intToSNAFU would be to make a searching algorthm and check for the minimum difference (=0) via SNAFUtoInt

// helper voor staartdeling, factorial voor 5 machten
int f5(int power)
{
    int ans = 0;
    for(int i = 0; i < power; i++)
    {

    }
    return ans;
}

// alternative: staartdeling
string intToSnafu3(const int iNumber)
{
    int temp = iNumber;
    map<const int, const char> values = {{-2, '='},{-1, '-'},{0, '0'},{1, '1'},{2, '2'}};
    int maxExp = 0;
    string retval = "";
    while(temp != 0)
    {
        for(const auto& [key, value] : m)
        {
            if(temp
        }
    }
    if(retval.size() == 0)
        retval = values[0];
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

