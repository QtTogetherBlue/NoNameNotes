#ifndef FILE_H
#define FILE_H

#include <string>
using namespace std;
class File
{
    string _name;
public:
    File();
    File(string name);
    string getName();
    void setName(string name);
};

#endif // FILE_H
