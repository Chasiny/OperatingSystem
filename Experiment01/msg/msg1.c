#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MSGKEY 2222
//消息结构体
struct Msg {
    long msgtype;
    char data[1000];
} msg;

int msgqid;

void server() {
    //获取消息队列
    msgqid = msgget(MSGKEY, 0777 | IPC_CREAT);
    //循环接收消息
    do {
        //获取消息
        msgrcv(msgqid, &msg, 1024, 0, 0);
        //输出消息
        printf("receive the data:%s\n",msg.data);
    } while (msg.msgtype != 1);
    //关闭消息队列
    msgctl(msgqid, IPC_RMID, 0);
    exit(0);
}

int main() {
    server();
}