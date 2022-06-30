#ifndef FOLDER_H
#define FOLDER_H

#include<string>
#include <vector>
#include "file.h"

using namespace std;

class Folder
{
    string name;
    int id;
    string color;
public:
    static int nextColorNum;
    vector<File*> files;
    Folder();
    Folder(string name_);
    string getName();
    void setName(string name_);
    int getId();
    string getColor();
};

#endif // FOLDER_H
