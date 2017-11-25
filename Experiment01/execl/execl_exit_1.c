
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <cstdlib>
#include <cstring>

int main(int argc,char ** argv) {
    printf("exec process pid is %d\n",getpid());
    exit(1);
}
