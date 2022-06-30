#include "folder.h"
#include "mycolor.h"

int Folder::nextColorNum=0;
Folder::Folder()
{
    name = "Untitled" + std::to_string(nextColorNum);
    id=nextColorNum++;
    color=Colors[id%COLOR_NUM];
}

Folder::Folder(string name_) :name(name_)
{
    id=nextColorNum++;
    color=Colors[id%COLOR_NUM];
}
string Folder::getName()
{
    return name;
}
void Folder::setName(string name_)
{
    name=name_;
}

int Folder::getId()
{
    return id;
}

string Folder::getColor()
{
    return color;
}
