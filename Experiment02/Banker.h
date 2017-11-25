//
// Created by chy on 17-11-16.
//

#ifndef EXPERIMENT02_BANKER_H
#define EXPERIMENT02_BANKER_H

#include <time.h>
#include <cstdlib>
#include <cstdio>
#include "Global.h"
#include "Process.h"

class Banker
{
  private:
    int  resourceNum; //资源种类数
    int processNum; //进程数
    int *total;
    int * available;
    int *available_t;
    Process **process;

  public:
    Banker(int rn, int pn);
    ~Banker();
    bool InitData();
    void PrintData();
    bool Check(bool isShow);
    bool Recycle(int i);
    bool IsGive(int index);
    bool Run(int n);
    int ProcessSort(int n);
    int GetNoFinishNum();
    bool SortCheck(int i,int j);
};

#endif //EXPERIMENT02_BANKER_H
