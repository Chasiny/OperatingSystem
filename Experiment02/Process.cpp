//
// Created by chy on 17-11-21.
//

#include "Process.h"

void Process::Init(int rn, int _pid)
{
    pid = _pid;
    resourceNum = rn;
    max=new int[rn];
    need = new int[rn];
    allocation = new int[rn];
    isFinish = false;
};

Process::~Process()
{
    delete[] max;
    delete[] need;
    delete[] allocation;
};
