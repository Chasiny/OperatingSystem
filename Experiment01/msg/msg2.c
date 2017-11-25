#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MSGKEY 2222
//消息结构体
struct Msg {
    long msgtype;
    char data[1000];
} msg;

int msgqid;

void client() {
    int i;
    //获取消息队列
    msgqid = msgget(MSGKEY, 0777);
    //循环发送消息
    for (i = 10; i >= 1; i--) {
        //写信息到消息队列
        msg.msgtype = i;
        strcpy(msg.data,"hello,are you receive?");
        printf("I sent the data:hello,are you receive?\n");
        msgsnd(msgqid, &msg, 1024, 0);
    }
    exit(0);
}

int main() {
    client();
}