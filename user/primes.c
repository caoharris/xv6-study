#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define num 2

void sieve(int p[num])
{
    int value;
    read(p[0],&value,sizeof(value));
    if(value==-1)
    {
        exit(0);
    }
    printf("prime %d\n",value);

    int pright[num];
    pipe(pright);
    if(fork()==0)
    {
        close(pright[1]);
        close(p[0]); // close(p[1]);
        sieve(pright);
    }
    else{
        close(pright[0]);
        int buf;
        while(read(p[0],&buf,sizeof(buf))&& buf!=-1)
        {
            if(buf%value!=0)
            {
                write(pright[1],&buf,sizeof(buf));
            }
        }
        buf =-1;
        write(pright[1],&buf,sizeof(buf));
        wait(0);
        exit(0);
    }

};

int main(int argc, char *argv[])
{
    int p[num];
    pipe(p);
    // pipe 0-read 1-wirte
    if(fork()==0){
        close(p[1]);
        sieve(p);
        exit(0);
    }
    else{
        close(p[0]);
        int i=0;
        for(i=2;i<=35;i++){
            write(p[1],&i,sizeof(i));
        }
        i=-1;
        write(p[1],&i,sizeof(i));
    }
    wait(0);
    exit(0);
}