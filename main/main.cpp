#include "App.hpp"
#include <cstring>
#include <iostream>

void displayHelp()
{
    std::cout<<
    "Usage:\n"
    "   cal\n"
    "   cal [expression] or\n"
    "   cal --help , cal -h , cal ?\n"
    "\n"
    "Functions avalable:\n"
    "   sin  [expression]\n"
    "   cos  [expression]\n"
    "   tan  [expression]\n"
    "   sqrt [expression]\n"
    "   ln   [expression]\n"
    ;
}

int main(int argv , char** argc)
{
    if(argv == 2)
    {
        if(strcmp(argc[1],"--help") || strcmp(argc[1],"-h") || strcmp(argc[1],"?"))
        {
            displayHelp();
        }
        else
        {
            App::run(argc[1]);
        }
    }
    else
    {
        App::runPromt();
    }
}