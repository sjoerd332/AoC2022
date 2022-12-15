#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define DBG 1

typedef enum{
    fileType,
    dirType
} memoryContentType;

struct MemoryContent
{
    string name;
    int size;
    const memoryContentType type;
    vector<MemoryContent> content;
    MemoryContent(string n, memoryContentType t, int s=0) : name(n), size(s), type(t) {}
};

class Device 
{
    public:
    Device() : memory("/", dirType) {}

    const string getCwdString(vector<string> absCwd)
    {
        string cwdTotal;
        //cout << "cwd string: ";
        for(int i = 0; i < cwd.size(); i++)
        {
            cwdTotal += cwd[i];
            //cout << cwd[i] << "+";
        }
        //cout << endl;
        return cwdTotal;
    }

    const int getNameIdx(MemoryContent* dir, string name)
    {
        int idx = 0;
        if(dir->content.size() == 0)
        {
            cout << "searching in empty dir" << endl;
            return idx;
        }
        for(int i = 0; i < dir->content.size(); i++)
        {
            if(dir->content[i].name == name)
                return idx;
            idx++;
        }
        return idx;
    }

    MemoryContent* getDir(vector<string> absCwd)
    {
        MemoryContent* mySrcDir = &memory;
        if(absCwd.size() == 1)
            return &memory;
        for(int i = 0; i < absCwd.size()-1; i++)
        {
            //cout << "Request: " << absCwd[i]  << " searching in: " << mySrcDir->name << endl;
            if(mySrcDir->name == absCwd[i] && mySrcDir->type == dirType)
            {
                mySrcDir = &mySrcDir->content[getNameIdx(mySrcDir, absCwd[i+1])];
            }
            else
            {
                cout << "Cannot get dir: " << getCwdString(absCwd) << endl;
                return nullptr;
            }
        }
        return mySrcDir;
    }

    const MemoryContent* getDirSafe(vector<string> absCwd)
    {
        return getDir(absCwd);
    }

    const bool in(const MemoryContent* dir, const string name)
    {
        bool found = false;
        if(dir == nullptr)
        {
            cout << "nullptr dir found!" << endl;
            return found;
        }
        for(int i = 0; i < dir->content.size(); i++)
        {
            if(dir->content[i].name == name)
                found = true;
        }
        return found;
    }

    void processCommand(string cmd, string arg)
    {
        if(cmd == "cd")
        {
            if(arg == "..")
            {
                cwd.pop_back();
            }
            else if(arg == "/")
            {
                cwd.clear();
                cwd.push_back("/");
            }
            else
            {
                cout << "Finding " << arg << " in " << getCwdString(cwd) << endl;
                if(in(getDir(cwd), arg))
                {
                    cwd.push_back(string(arg));
                    cout << "cd'ed to: " << getCwdString(cwd) << endl;
                }
                else
                {
                    cout << "Unknown directory " << arg << " in " << getCwdString(cwd) << endl;
                }
            }
        }
        else if(cmd == "ls")
        {
            while(arg.size() > 0)
            {
                string line;
                if(arg.find('\n') != string::npos)
                {
                    line = arg.substr(0, arg.find('\n'));
                    arg = arg.substr(arg.find('\n')+1, arg.size() - arg.find('\n')-1);
                    cout << line << endl;
                }
                else
                {
                    line = arg;
                    arg.erase();
                }
                // find a dir and add to memory
                if(line.substr(0,4).find("dir ") != string::npos)
                {
                    string dname = line.substr(4, line.size()-4);
                    if(!in(getDir(cwd), dname))
                    {
                        MemoryContent* myDir = getDir(cwd);
                        myDir->content.push_back(MemoryContent(dname, dirType));
                    }
                    else
                    {
                        cout << "Directory already present in memory " << line.substr(4) << endl; 
                    }
                }
                // found a file, add to memory
                else
                {
                    string fname = line.substr(line.find(' ')+1, line.size()-line.find(' ')-1);
                    int s = stoi(line.substr(0, line.find(' ')));
                    cout << fname << " - file with size: " << s << endl;
                    if(!in(getDir(cwd), fname))
                    {
                        MemoryContent* myDir = getDir(cwd);
                        myDir->content.push_back(MemoryContent(fname, fileType, s));
                    }
                    else
                    {
                        cout << "File already present in memory " << fname << endl; 
                    }
                    // also trace back cwd to add new file to all dir sizes
                    for(int i = 0; i < cwd.size(); i++)
                    {
                        MemoryContent* myDir = getDir(cwd);
                        myDir->size += s;
                    }
                }
            }
        }
        else
        {
            cout << "Unknown command" << cmd << " with args: " << arg << endl;
        }
    }

    int sumSmallDirSizes(int maxSize = 100000)
    {
        int sum = 0;
        bool traversedContent = false;
        int depth = 0;
        int idx = 0;
        MemoryContent* d = &memory;
        while(traversedContent == false)
        {
            if(d->size <= maxSize)
            {
                 sum += d->size();
            }
        }



        for(int i = 0; i < memory.content.size(); i++)
        {
            if(memory.content[i].size <= maxSize)
            {

            }
        }
        return sum;
    }

    private:
    MemoryContent memory;
    vector<string> cwd;
};

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d7p1_ex.txt");
    #else
    f.open("inputs/d7p1.txt");
    #endif

    // Part 1
    Device d;
    string cmd, arg;
    bool argWasNotYetSent = false;
    for(string line; getline(f, line); )
    {
        if(argWasNotYetSent && (line.find('$') == 0))
        {
            argWasNotYetSent = false;
            d.processCommand(cmd,arg);
            cmd.erase();
            arg.erase();
        }
        if(line.find('$') == 0 && line.size() > 4)
        {
            cmd = line.substr(2,2);
            arg = line.substr(5, line.size()-5);
            d.processCommand(cmd, arg);
            cmd.erase();
            arg.erase();
        }
        else if(line.find('$') == 0)
        {
            cmd = line.substr(2,2);
        }
        else
        {
            argWasNotYetSent = true;
            arg.append(line);
            arg.append("\n");
        }
    }
    d.processCommand(cmd,arg);
    
    cout << "Answer part 1: " << d.sumSmallDirSizes() << endl;
    f.close();
    return 0;
}

