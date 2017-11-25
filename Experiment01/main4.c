#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

//终止进程标记
int k1, k2;
//子进程pid
pid_t cpid1, cpid2;

//终止进程1函数
void int_fun1(int s) {
    printf("要杀子进程1\n");
    k1 = 0;
}

//终止进程2函数
void int_fun2(int s) {
    printf("要杀子进程2\n");
    k2 = 0;
}

void killfunc(int s) {
    //printf("父进程杀子进程\n");
    //父进程调用给子进程发送终止信号
    if (cpid1 > 0)
        kill(cpid1, SIGUSR1);
    if (cpid2 > 0)
        kill(cpid2, SIGUSR2);
}

int main() {
    //置标记为1
    k1 = k2 = 1;
    //默认子进程pid为负数
    cpid1 = cpid2 = -1;
    //创建子进程1
    cpid1 = fork();
    if (cpid1 == -1) {
        //printf("创建子进程1失败！\n");
        exit(1);
    } else if (cpid1 == 0) {
        //printf("进入子进程1\n");
        //子进程屏蔽ctrl c信号
        signal(SIGINT,SIG_IGN);
        //设置子进程对SIGUSR1处理函数为int_fun1
        signal(SIGUSR1, int_fun1);
        while (k1 == 1) {
            //printf("子进程1运行中\n");
            sleep(1);
        }
        //子进程终止
        printf("Child process1 is killed by parent!\n");
        exit(0);
    } else {
        cpid2 = fork();
        if (cpid2 == -1) {
            //printf("创建子进程2失败！\n");
            exit(1);
        } else if (cpid2 == 0) {
            //printf("进入子进程2\n");
            //子进程屏蔽ctrl c信号
            signal(SIGINT,SIG_IGN);
            //设置子进程对SIGUSR2处理函数为int_fun2
            signal(SIGUSR2, int_fun2);
            while (k2 == 1) {
                //printf("子进程2运行中\n");
                sleep(1);
            }
            //子进程终止
            printf("Child process2 is killed by parent!\n");
            exit(0);
        } else {
            //父进程设置SIGINT信号处理函数为killfunc
            signal(SIGINT, killfunc);
            //printf("父进程运行中\n");
            wait(0);
            printf("Parent process is killed!\n");
            exit(0);
        }
    }
}