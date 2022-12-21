#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>

using namespace std;

#define DBG 0

struct Pos {
    int x;
    int y;

    bool operator<(const Pos& other) const
    {
        // Simple: cannot sort uniquely.
        //bool ret = x < other.x && y < other.y; 
        // Other tactic:
        bool ret = x < other.x;
        // prioritize x over y
        if(x == other.x)
            ret = y < other.y;
        return ret;
    }

    bool operator==(const Pos& other) const
    {
        return x == other.x && y == other.y; 
    }
};

struct RopePiece {
    public:
    RopePiece()
    {
        memset(&head, 0, sizeof(head));
        memset(&tail, 0, sizeof(tail));
    }

    void move(char dir)
    {
        switch(dir)
        {
            case 'U':
                head.y++;
                // straight up
                if(head.x-tail.x == 0 && head.y-tail.y > 1)
                {
                    tail.y++;
                }
                // lx == 1 or -1 (logically)
                else if(head.y-tail.y > 1)
                {
                    tail.y++;
                    tail.x = head.x;
                }
                // no tail move
                else {}
                break;
            case 'D':
                head.y--;
                // straight down
                if(head.x-tail.x == 0 && head.y-tail.y < -1)
                {
                    tail.y--;
                }
                // lx == 1 or -1 (logically)
                else if(head.y-tail.y < -1)
                {
                    tail.y--;
                    tail.x = head.x;
                }
                // no tail move
                else {}
                break;
            case 'L':
                head.x--;
                // left straight
                if(head.y-tail.y == 0 && head.x-tail.x < -1)
                {
                    tail.x--;
                }
                // ly == 1 or -1 (logically)
                else if(head.x-tail.x < -1)
                {
                    tail.x--;
                    tail.y = head.y;
                }
                // no tail move
                else {}
                break;
            case 'R':
                head.x++;
                // right straight
                if(head.y-tail.y == 0 && head.x-tail.x > 1)
                {
                    tail.x++;
                }
                // ly == 1 or -1 (logically)
                else if(head.x-tail.x > 1)
                {
                    tail.x++;
                    tail.y = head.y;
                }
                // no tail move
                else {}
                break;
            default:
                break;
        };
        // Keep up the tail trail, fill the stack
        tailTrail.push_back(tail);
    }

    int getUniqueTailPositions()
    {
        list<Pos> l = tailTrail;
        l.sort();
        l.unique();
        return l.size();
    }

    void printTailPositions()
    {
        for(list<Pos>::iterator it = tailTrail.begin(); it != tailTrail.end(); ++it)
        {
            cout << it->x << " " << it->y << endl;
        }
    }

    void printUniquePositions()
    {
        list<Pos> l = tailTrail;
        l.sort();
        l.unique();
        for(list<Pos>::iterator it = l.begin(); it != l.end(); ++it)
        {
            cout << it->x << " " << it->y << endl;
        }
    }

    private:
    Pos head, tail;
    list<Pos> tailTrail;
};

int main() {
    cout << "Start" << endl;
    std::ifstream f;
    #if DBG
    f.open("inputs/d9p1_ex.txt");
    #else
    f.open("inputs/d9p1.txt");
    #endif

    // Part 1
    RopePiece p;
    for(string line; getline(f, line); )
    {
        size_t spacePos = line.find(' ');
        int moves = stoi(line.substr(spacePos+1, line.size()-spacePos+1), 0);
        char dir = line[0];
        while(moves > 0)
        {
            p.move(dir);
            moves--;
        }
    }
    //p.printTailPositions();
    //p.printUniquePositions();

    cout << "Answer part 1: " << p.getUniqueTailPositions() << endl;
    f.close();
    return 0;
}

