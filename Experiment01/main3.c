#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int main()
{
    printf("main process start...\n");
    pid_t childPid;
    //创建子进程
    childPid=fork();

    //父进程对屏幕输出加锁
    lockf(1,1,0);
    if(childPid<0){
        printf("fork fail\n");
    }else if(childPid==0){
        //子进程对屏幕输出加锁
        lockf(1,1,0);
        //输出信息到屏幕
        for(int i=0;i<100;i++){
            printf("this is child's show\n");
        }
        //解锁
        lockf(1,0,0);
    }else{
        //父进程休眠
        sleep(1);
        //父进程输出
        for(int i=0;i<100;i++){
            printf("this is parent's show\n");
        }
        //解锁
        lockf(1,0,0);
    }
}
