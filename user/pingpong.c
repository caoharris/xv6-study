#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define num 2
int 
main(int argc, char *argv[])
{
    int p1[num],p2[num];
    pipe(p1);
    pipe(p2);
    // pipe 0-read 1-wirte

    if(fork()==0){
        char recvbyte;
        read(p1[0],&recvbyte,1);
        printf("%d: received ping\n",getpid());
        write(p2[1],&recvbyte,1);
        exit(0);
    }
    else{
        char sendbyte='1';
        write(p1[1],&sendbyte,1);
        read(p2[0],&sendbyte,1);
        printf("%d: received pong\n",getpid());
        wait(0);
    }
    exit(0);
}