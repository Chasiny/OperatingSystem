

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    pid_t child1, child2, parent;

    //获取父进程pid
    parent = getpid();

    //创建子进程1
    if ((child1 = fork()) < 0)
    {
        fprintf(stderr, "%s:fork of children1 failed:%s\n", argv[0], strerror(errno));
        exit(1);
    }
    else if (child1 == 0)
    {
        //输出子进程pid以及其父进程pid
        printf("child1 id is %d,parent id is %d\n", getpid(), getppid());
        sleep(2);
    }
    else
    {
        //创建子进程2
        if ((child2 = fork()) < 0)
        {
            fprintf(stderr, "%s:fork of children2 failed:%s\n", argv[0], strerror(errno));
            exit(1);
        }
        else if (child2 == 0)
        {
            //输出子进程pid以及其父进程pid
            printf("child2 id is %d,parent id is %d\n", getpid(), getppid());
            sleep(2);
        }
        else
        {
            //输出父进程pid
            printf("father id is %d\n", getpid());
            sleep(1);
            exit(0);
        }
    }
    exit(0);
}
