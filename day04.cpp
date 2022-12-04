#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

#define DBG 0

vector<int> getTaskSet(string s)
{
    vector<int> taskSet;
    for(int i = stoi(s.substr(0, s.find('-'))); 
        i <= stoi(s.substr(s.find('-') + 1, s.size() - (s.find('-')))); 
        i++)
    {
        taskSet.push_back(i);
    }
    return taskSet;
}

pair<vector<int>, vector<int>> interpretLine(string line)
{
    string strSet1 = line.substr(0, line.find(','));
    int startPosSet2 = line.find(',') + 1;
    string strSet2 = line.substr(startPosSet2, line.size() - startPosSet2);
    #if DBG
        cout << strSet1 << " and " << strSet2 << endl;
    #endif
    return pair<vector<int>, vector<int>> (getTaskSet(strSet1), getTaskSet(strSet2));
}

int checkContainment(pair<vector<int>, vector<int>> p)
{
    if(get<0>(p)[0] >= get<1>(p)[0] && get<0>(p)[0] <= get<1>(p).back() && get<0>(p).back() <= get<1>(p).back())
        return 1;
    else if(get<1>(p)[0] >= get<0>(p)[0] && get<1>(p)[0] <= get<0>(p).back() && get<1>(p).back() <= get<0>(p).back())
        return 1;
    //else
    return 0;
}

int checkPartialContainment(pair<vector<int>, vector<int>> p)
{
    int rVal = 0;
    for(auto i: get<0>(p))
    {
        for(auto j: get<1>(p))
        {
            if(i == j)
            {
                rVal = 1;
            }
        }
    }
    return rVal;
}

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d4p1_ex.txt");
    #else
    f.open("inputs/d4p1.txt");
    #endif

    // Part 1 and 2
    int sumOfFullyContainedSets = 0;
    int sumOfPartialContainedSets = 0;
    for(string line; getline(f, line); )
    {
        pair<vector<int>, vector<int>> p = interpretLine(line);
        #if DBG
            for (auto i: get<0>(p))
                cout << i << ' ';
            cout << "and ";
            for (auto i: get<1>(p))
                cout << i << ' ';
            cout << endl;
        #endif
        sumOfFullyContainedSets += checkContainment(p);
        sumOfPartialContainedSets += checkPartialContainment(p);
    }
    
    cout << "Answer part 1: " << sumOfFullyContainedSets << endl;
    cout << "Answer part 2: " << sumOfPartialContainedSets << endl;
    f.close();
    return 0;
}

