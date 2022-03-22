#include <stdio.h>
#include <sys/time.h>
const int N (64*1024*1024);
#define BEGIN struct timeval begin,end;\
              gettimeofday(&begin,NULL);

#define END(s) gettimeofday(&end,NULL);\
               printf("step:%-4d\t%ld us.\n",s,(end.tv_sec-begin.tv_sec)*1000000+(end.tv_usec-begin.tv_usec));

#define f(step) for(int index=0;index < N;index+=step){a[index]*=index;}

int main(){
    int *a = new int[N];
    for (int j = 1; j <= 64; j*=2){
        BEGIN;
        f(j);
        END(j);
    }
}
