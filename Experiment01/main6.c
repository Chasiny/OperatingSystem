

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //管道
    int fd[2];
    //用于接收的字符串
    char str[256];
    //用于写管道的字符串
    char parentStr1[27] = "this is a pipe from child1";
    char parentStr2[27] = "this is a pipe from child2";
    pid_t childPid1, childPid2;
    if (pipe(fd) < 0)
    {
        printf("pipe fail\n");
        exit(0);
    }
    //创建子进程
    childPid1 = fork();
    if (childPid1 < 0)
    {
        printf("fork1 fail\n");
        exit(0);
    }
    else if (childPid1 == 0)
    {
        //对管道写加锁
        lockf(fd[1],1,0);
        printf("start to write into pipe1\n");
        //关闭管道读
        close(fd[0]);
        //写管道
        write(fd[1], parentStr1, 27);
        //解锁管道
        lockf(fd[1],0,0);
        sleep(1);
        exit(0);
    }
    else
    {
        //创建子进程
        childPid2 = fork();
        if (childPid2 < 0)
        {
            printf("fork2 fail\n");
            exit(0);
        }
        else if (childPid2 == 0)
        {
            //休眠让自己进程1优先获得管道读写
            sleep(1);
            //对管道写加锁
            lockf(fd[1],1,0);
            printf("start to write into pipe2\n");
            //关闭管道读
            close(fd[0]);
            //写管道
            write(fd[1], parentStr2, 27);
            //解锁管道
            lockf(fd[1],0,0);
            sleep(1);
            exit(0);
        }
        else
        {
            //等待子进程结束
            wait(0);
            //读取管道
            read(fd[0],str, 27);
            //输出管道信息
            printf("%s\n",str);
            wait(0);
            read(fd[0],str, 27);
            printf("%s\n",str);
            exit(0);
        }
    }
}