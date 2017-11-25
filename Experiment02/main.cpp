#include <iostream>
#include "Banker.h"

using namespace std;

int main()
{
    Banker b(5, 10);
    //b.PrintData();
    b.Run(0);
    return 0;
}