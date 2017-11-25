

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    pid_t child;
    //创建子进程
    child = fork();
    if (child < 0)
    {
        printf("fork fail!\n");
    }
    else if (child == 0)
    {
        //输出子进程信息
        printf("fork success\n");
        printf("child pid: %d\n", getpid());
        
        //将二进制文件代替子进程
        if (execl("/home/chy/Project/C++/OperatingSystem/OperatingSystem/Experiment01/execl/execl_exit_0.out", "", NULL) < 0)
        {
            //execl执行失败
            fprintf(stderr, "execl failed:%s", strerror(errno));
            return -1;
        }
    }
    else
    {
        //输出父进程信息
        printf("this is parent\n");
        int status;
        wait(&status);
        
        //输出子进程结束的标记，即exit函数中的参数
        printf("child process is end,status:%d\n", WEXITSTATUS(status)); //status是按位存储的状态信息，需要调用相应的宏来还原一下
    }
}
