#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define DBG 1

typedef enum{
    fileType,
    dirType
} memoryContent;

struct File
{
    string name;
    int size;
    const memoryContent type;
    File(string n, int s=0, memoryContent t = fileType) : name(n), size(s), type(t) {}
};

struct Dir : File
{
    vector<File> content;
    Dir(string n) : File(n, dirType) {}
};

class Device 
{
    public:
    Device() : memory("/") {}

    const string getCwdString(vector<string> absCwd)
    {
        string cwdTotal;
        for(int i = 0; i < cwd.size(); i++)
        {
            cwdTotal += cwd[i];
        }
        return cwdTotal;
    }

    const int getNameIdx(Dir* dir, string name)
    {
        int idx = 0;
        for(int i = 0; i < dir->content.size(); i++)
        {
            if(dir->content[i].name == name)
                return idx;
            idx++;
        }
        return idx;
    }

    Dir* getDir(vector<string> absCwd)
    {
        Dir* myRetDir = nullptr;
        Dir* mySrcDir = &memory;
        for(int i = 0; i < absCwd.size()-1; i++)
        {
            if(mySrcDir->name == absCwd[i] && mySrcDir->type == dirType)
            {
                mySrcDir = static_cast<Dir*>(&mySrcDir->content[getNameIdx(mySrcDir, absCwd[i+1])]);
            }
            else
                cout << "Cannot get dir" << getCwdString(absCwd) << endl;
                return nullptr;
        }
        return myRetDir;
    }

    const bool in(const Dir* dir, const string name)
    {
        bool found = false;
        if(dir == nullptr)
            cout << "nullptr dir found!" << endl;
            return found;
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
                if(in(getDir(cwd), arg))
                {
                    cwd.push_back(arg);
                }
                else
                {
                    cout << "Unknown directory " << arg << " in " << getCwdString(cwd) << endl;
                }
            }
        }
        else if(cmd == "ls")
        {
            //appendMemory()
            // for content
            //getDir(cwd)->content.push_back(
            while(arg.size() > 0)
            {
                string line;
                cout << line << endl;
                if(arg.find('\n') != string::npos)
                {
                    line = arg.substr(0, arg.find('\n'));
                    arg = arg.substr(arg.find('\n'), arg.size() - arg.find('\n'));
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
                        Dir* myDir = getDir(cwd);
                        myDir->content.push_back(Dir(dname));
                    }
                    else
                    {
                        cout << "Directory already present in memory " << line.substr(4) << endl; 
                    }
                }
                // found a file, add to memory
                else
                {
                    string fname = line.substr(line.find(' '), line.size()-line.find(' '));
                    int s = stoi(line.substr(0, line.find(' ')));
                    if(!in(getDir(cwd), fname))
                    {
                        Dir* myDir = getDir(cwd);
                        myDir->content.push_back(File(fname, s));
                    }
                    else
                    {
                        cout << "File already present in memory " << fname << endl; 
                    }
                    // also trace back cwd to add new file to all dir sizes
                    for(int i = 0; i < cwd.size(); i++)
                    {
                        Dir* myDir = getDir(cwd);
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

    private:
    Dir memory;
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
    
    cout << "Answer part 1: " << endl;
    f.close();
    return 0;
}

