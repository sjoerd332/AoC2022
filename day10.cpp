#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

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

class ClockCircuit
{
    public:
    ClockCircuit(CPU* aCpu) : cycleCnt(0)
    {
        setCpu(aCpu);
    }

    void setCpu(CPU* aCpu)
    {
        theCpu = aCpu;
    }

    void cycle()
    {
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
};

class Device
{
    public:
    Device() : programCnt(0), theClk(&theCpu)
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
        return retVal;
    }

    private:
    CPU theCpu;
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
    f.close();
    return 0;
}

