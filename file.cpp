#include "file.h"
#include<string>
using namespace std;
File::File()
{

}
File::File(string name)
{
    _name = name;
}
string File::getName()
{
    return _name;
}
void File::setName(string name)
{
    _name = name;
}
