#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

#define DBG 0

class CPU
{
    public:

    void setInstruction(string anInstr, int anArg)
    {
        theInstruction = anInstr;
        theArgument = anArg;
    }

    bool doInstruction()
    {
        currentInstructionCycleNr++;
        if(theInstruction == "addx" && currentInstructionCycleNr == 2)
        {
            reg_x += theArgument;
            currentInstructionCycleNr = 0;
        }
        else if(theInstruction == "noop" && currentInstructionCycleNr == 1)
        {
            // do nothing
            currentInstructionCycleNr = 0;
        }
        else if(currentInstructionCycleNr > 0)
        {
            // instruction was running already
        }
        else
        {
            cout << "Invalid instruction: " << theInstruction << " with arg " << theArgument << endl;
        }
        return isBusy();
    }

    bool isBusy()
    {
        return currentInstructionCycleNr > 0;
    }

    int getRegX()
    {
        return reg_x;
    }
    
    private:
    int reg_x = 1;
    int currentInstructionCycleNr = 0;
    string theInstruction;
    int theArgument;
};

class CRT
{
    public:
    CRT(CPU* aCpu) : theCpu(aCpu), thePixelCnt(0)
    {
        memset(theScreen, '-', sizeof(theScreen));
    }

    void draw()
    {
        int x = thePixelCnt % theWidth;
        int y = thePixelCnt / theWidth;
        int xSprite = theCpu->getRegX() % theWidth;
        int ySprite = theCpu->getRegX() / theWidth;
        bool isSprite = ((xSprite-x == -1 || xSprite-x == 0 || xSprite-x == 1)); // && y == ySprite, if y would also be relevant
        if(x >= 0 && x < theWidth && y >= 0 && y < theHeight)
        {
            if(isSprite)
                theScreen[x][y] = '#';
            else
                theScreen[x][y] = '.';
        }
        thePixelCnt++;
        if(thePixelCnt >= theWidth*theHeight)
            thePixelCnt = 0;
    }

    char getPixel(int x, int y)
    {
        if(x >= 0 && x < theWidth && y >= 0 && y < theHeight)
            return theScreen[x][y];
        else
            return 0;
    }

    static const int theWidth = 40;
    static const int theHeight = 6;

    private:
    CPU* theCpu;
    int thePixelCnt;
    char theScreen[theWidth][theHeight];
};

class ClockCircuit
{
    public:
    ClockCircuit(CPU* aCpu, CRT* aCrt) : cycleCnt(0), theCpu(aCpu), theCrt(aCrt)
    {}

    void cycle()
    {
        if(theCrt != nullptr)
            theCrt->draw();
        if(theCpu != nullptr)
            theCpu->doInstruction();
        cycleCnt++;
    }

    int getCycle()
    {
        return cycleCnt;
    }

    private:
    int cycleCnt;
    CPU* theCpu;
    CRT* theCrt;
};

class Device
{
    public:
    Device() : programCnt(0), theClk(&theCpu, &theCrt), theCrt(&theCpu)
    {
    }

    void run(int nrOfCycles)
    {
        int myCycles = 0;
        while(myCycles < nrOfCycles)
        {
            if(theCpu.isBusy() == false && programCnt < theProgram.size())
            {
                string cmd = get<0>(theProgram.at(programCnt));
                int arg = get<1>(theProgram.at(programCnt));
                theCpu.setInstruction(cmd, arg);
                if(programCnt < theProgram.size()-1)
                    programCnt++;
            }
            theClk.cycle();
            myCycles++;
        }
    }

    void setProgram(vector<pair<string,int>> aProgram)
    {
        theProgram = aProgram;
    }

    int getRegister(string name)
    {
        int retVal = 0;
        if(name == "X")
            retVal = theCpu.getRegX();
        else if(name == "cycleCnt")
            retVal = theClk.getCycle();
        else if(name == "CRT width")
            retVal = theCrt.theWidth;
        else if(name == "CRT height")
            retVal = theCrt.theHeight;
        return retVal;
    }

    char getPixel(int x, int y)
    {
        return theCrt.getPixel(x,y);
    }

    private:
    CPU theCpu;
    CRT theCrt;
    ClockCircuit theClk;
    vector<pair<string,int>> theProgram;
    int programCnt;
};

class DeviceAnalysis
{
    public:
    void setExamination(vector<int> examinationSamples)
    {
        theExaminationPoints = examinationSamples;
    }

    typedef enum analysisPhase
    {
        after = 0,
        during = 1
    } Ap;
    
    int getSignalStrength(Ap ap)
    {
        vector<int> signalStrengths;
        int signalStrength = 0;
        int pointDiff = 0;
        for(int i = 0; i < theExaminationPoints.size(); i++)
        {
            pointDiff = theExaminationPoints[i] - (int)(ap) - d.getRegister("cycleCnt");
            d.run(pointDiff);
            int xVal = d.getRegister("X");
            int cycleNr = d.getRegister("cycleCnt") + (int)(ap);
            signalStrengths.push_back(xVal * cycleNr);
            signalStrength += xVal * cycleNr;
        }
        return signalStrength;
    }

    void setProgram(vector<pair<string,int>> aProgram)
    {
        d.setProgram(aProgram);
    }

    void printCrt()
    {
        const int w = d.getRegister("CRT width");
        const int h = d.getRegister("CRT height");
        const int nrOfP = w*h;
        const int nrOfLetters = 8;
        int cycleCnt = d.getRegister("cycleCnt");
        while(cycleCnt % nrOfP != 0)
        {
            d.run(1);
            cycleCnt = d.getRegister("cycleCnt");
        }
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                if(j % (w / nrOfLetters) == 0 && j > 0)
                    cout << "\t";
                cout << d.getPixel(j,i);
            }
            cout << endl;
        }
    }

    private:
    Device d;
    vector<int> theExaminationPoints;
};

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d10p1_ex.txt");
    #else
    f.open("inputs/d10p1.txt");
    #endif

    // Part 1
    vector<pair<string,int>> program;
    for(string line; getline(f, line); )
    {
        string cmd = line.substr(0, line.find(" "));
        int arg = 0;
        if(cmd != "noop")
            arg = stoi(line.substr(line.find(" ")+1,line.size()-line.find(" ")-1), 0);
        program.push_back(pair<string,int>(cmd, arg));
    }

    DeviceAnalysis da;
    da.setProgram(program);
    vector<int> exampinationCycles = {20, 60, 100, 140, 180, 220};
    da.setExamination(exampinationCycles);
    int ans1 = da.getSignalStrength(DeviceAnalysis::Ap::during);
    
    cout << "Answer part 1: " << ans1 << endl;

    // Part 2
    cout << "Answer part 2: " << endl;
    da.printCrt();

    f.close();
    return 0;
}

