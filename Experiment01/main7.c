#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define  SHMKEY  1111
int  shmid,i;
int  *addr;
char *data;

void  client( )
{
    int i;
    //获取共享存储区
    shmid=shmget(SHMKEY,1024,0777);
    //获取共享存储区始地址
    addr=(int *)shmat(shmid,0,0);
    //获取要写字符串的地址
    data=(char *)((int *)shmat(shmid,0,0)+1);
    for (i=9;i>=0;i--)
    {
        //等待服务端是否接收数据
        while (*addr!=-1);
        //向共享存储区写i的值以及字符串数据
        char sendData[256]="hello,this is a test data";
        printf("sent i is %d,data is %s\n",i,sendData);
        *addr=i;
        strcpy(data,sendData);
    }
    exit(0);
}

void  server( )
{
    //获取共享存储区
    shmid=shmget(SHMKEY,1024,0777|IPC_CREAT);
    //获取共享存储区始地址
    addr=(int *)shmat(shmid,0,0);
    //获取要读字符串的地址
    data=(char *)((int *)shmat(shmid,0,0)+1);
    do
    {
        *addr=-1;
        //等待客户端进程写数据到共享存储区
        while (*addr==-1);
        //读取共享存储区数据
        printf("received i is %d,data is%s\n",*addr,data);
    }while (*addr);
    //关闭共享存储区
    shmctl(shmid,IPC_RMID,0);
    exit(0);
}

int main( )
{
    //开启服务端进程
    while ((i=fork( ))==-1);
    if (!i) server( );
    //调用系统ipcs命令查看共享存储详情
    system("ipcs  -m");
    //开启客户端进程
    while ((i=fork( ))==-1);
    if (!i) client( );
    wait(0);
    wait(0);
    return 0;
}