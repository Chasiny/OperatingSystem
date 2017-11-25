//
// Created by chy on 17-11-16.
//

#include "Banker.h"

Banker::Banker(int rn, int pn) {
    resourceNum = rn;
    processNum = pn;
    total = new int[rn];
    available = new int[rn];
    available_t = new int[rn];
    process = new Process *[pn];
    for (int i = 0; i < pn; i++) {
        process[i] = new Process;
        process[i]->Init(rn, i + 1);
    }
    InitData();
}

Banker::~Banker() {
    for (int i = 0; i < resourceNum; i++) {
        delete process[i];
    }
    delete[] total;
    delete[] available;
    delete[] available_t;
    delete[] process;
}

bool Banker::InitData() {
    bool isInitOK = false;
    printf("初始化数据\n");
    while (!isInitOK) {
        for (int i = 0; i < processNum; i++) {
            process[i]->isFinish = false;
        }
        srand(time(NULL));
        for (int i = 0; i < resourceNum; i++) {
            total[i] = rand() % (REC_RANGE_MAX - REC_RANGE_MIN) + REC_RANGE_MIN;
            available[i] = total[i];
        }
        for (int i = 0; i < processNum; i++) {
            for (int j = 0; j < resourceNum; j++) {
                process[i]->max[j] = (rand() % total[j]) / PROCESS_REC_RATE;
                int randX = process[i]->max[j] / GIVE_RATE;
                process[i]->allocation[j] = rand() % (randX > 0 ? randX : 1);
                if (process[i]->allocation[j] > available[j]) {
                    process[i]->allocation[j] = available[j];
                    available[j] = 0;
                } else {
                    process[i]->need[j] = process[i]->max[j] - process[i]->allocation[j];
                    available[j] = available[j] - process[i]->allocation[j];
                }
            }
        }
        for (int i = 0; i < resourceNum; i++) {
            available_t[i] = available[i];
        }
        isInitOK = Check(false);
        if (!isInitOK) {

        } else {
            for (int i = 0; i < resourceNum; i++) {
                available[i] = available_t[i];
            }
        }

    }
    printf("初始化数据成功\n");
    PrintData();
    //printf("sort ans:%d\n", ProcessSort(0));
    //PrintData();
    return true;
}

void Banker::PrintData() {
    printf("系统拥有的资源：");
    for (int i = 0; i < resourceNum; i++) {
        printf("\t%d", total[i]);
    }
    printf("\n");
    printf("系统剩余的资源：");
    for (int i = 0; i < resourceNum; i++) {
        printf("\t%d", available[i]);
    }
    printf("\n-进程--------最大需求-----------------------已获得-----------------------仍需要-----------需要总数");
    printf("\n");
    //printf("prodata\t\t\t\t allocation\t\t\t\tneed\n");
    for (int i = 0; i < processNum; i++) {
        printf("进程%d：", process[i]->pid);
        for (int j = 0; j < resourceNum; j++) {
            int index = i * resourceNum + j;
            printf("\t%d ", process[i]->max[j]);
        }
        printf("\t\t");
        for (int j = 0; j < resourceNum; j++) {
            int index = i * resourceNum + j;
            printf("\t%d", process[i]->allocation[j]);
        }
        printf("\t\t");
        for (int j = 0; j < resourceNum; j++) {
            int index = i * resourceNum + j;
            printf("\t%d", process[i]->need[j]);
        }
        printf("\t");
        printf("\n");
    }
}

bool Banker::Check(bool isShow) {
    int p = processNum;
    bool isOK = false;
    for (int i = 0; i < processNum; i++) {
        process[i]->isFinish = false;
    }
    while (p > 0) {
        isOK = false;
        for (int j = 0; j < processNum; j++) {
            if (IsGive(j) && !process[j]->isFinish) {
                //printf("优先分配进程%d\n", process[j]->pid);
                p--;
                process[j]->isFinish = true;
                for (int i = 0; i < resourceNum; i++) {
                    available[i] += process[j]->need[i];
                }
                isOK = true;
                if (isShow) {
                    //printf("%d:", j);
                }
                for (int k = 0; k < resourceNum; k++) {
                    if (isShow){
                        //printf("%d ", process[j]->need[k]);
                    }
                }
                if (isShow){
                    //printf("\n");
                }
            }
        }
        if (!isOK && p > 0) {
            //printf("dead lock\n");
            return false;
        }
    }
    //printf("ok\n");
    return true;
}

bool Banker::IsGive(int j) {
    for (int i = 0; i < resourceNum; i++) {
        if (process[j]->need[i] > available[i]) {
            return false;
        }
    }
    return true;
}

bool Banker::Run(int n) {
    for (int i = 0; i < processNum; i++) {
        process[i]->isFinish = false;
    }
    int start=0;
    int pre_start=0;
    while(start<processNum-1){
        pre_start=start;
        start=ProcessSort(start);
        //printf("排序结果%d\n",start);
        for(int i=pre_start;i<start;i++){
            Recycle(i);
            printf("回收%d\n",process[i]->pid);
            //PrintData();
        }
        //break;
    }

}

int Banker::GetNoFinishNum() {
    int ans = 0;
    for (int i = 0; i < processNum; i++) {
        if (process[i]->isFinish)
            ans++;
    }
    return ans;
}

bool Banker::Recycle(int i){
    process[i]->isFinish=true;
    for (int j = 0; j < resourceNum; j++) {
        available[j]+=process[i]->allocation[j];
    }
    return true;
}

int Banker::ProcessSort(int n) {
    int ans=n;
    if (n >= processNum - 1) {
        return ans;
    }
    for (int i = n; i < processNum - 1; i++) {
        for (int j = n+1; j < processNum - i; j++) {
            //printf("%d %d\n",j - 1, j);
            if (!SortCheck(j - 1, j)) {
                Process *p = process[j - 1];
                process[j - 1] = process[j];
                process[j] = p;
            }
        }
    }
    for(int i=n;i<processNum;i++){
        if(IsGive(i)){
            ans++;
        }
    }
    return ans;
}

//第一个优先的返回true
bool Banker::SortCheck(int i, int j) {
    //printf("比较%d和%d\n",i,j);
    process[i]->value = process[j]->value = 0;
    for (int k = 0; k < resourceNum; k++) {
        if (process[i]->need[k] > available[k]) {
            //printf("结果是：%d\n", false);
            return false;
        }
        if (process[j]->need[k] > available[k]) {
            //printf("结果是：%d\n", true);
            return true;
        }
        process[i]->value += process[i]->need[k];
        process[j]->value += process[j]->need[k];
    }
    //printf("结果是：%d\n", process[i]->value < process[j]->value ? true : false);
    return process[i]->value < process[j]->value ? true : false;
}
