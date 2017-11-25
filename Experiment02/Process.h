//
// Created by chy on 17-11-21.
//

#ifndef EXPERIMENT02_PROCESS_H
#define EXPERIMENT02_PROCESS_H

class Process
{
  public:
    void Init(int rn, int p);
    ~Process();
    int pid;          //ID
    int resourceNum;       //资源种类数
    int *max;  //资源最大需求
    int *allocation;      //已获得的资源
    int *need;     //仍需要的资源
    bool isFinish;    //是否完成申请
    int value;        //定义排序的等级
};

#endif //EXPERIMENT02_PROCESS_H
