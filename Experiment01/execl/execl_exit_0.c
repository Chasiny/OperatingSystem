

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc,char ** argv) {
    //输出进程信息
    printf("exec process pid is %d\n",getpid());
    exit(0);
}
