# Cache-puzzle
---

## 代码做了什么事情

我想要测试验证Cache的工作情况，所以编写了 `cache_puzzle.cpp`。内容介绍如下：
```c
#define BEGIN struct timeval begin,end;\
              gettimeofday(&begin,NULL);

#define END(s) gettimeofday(&end,NULL);\
               printf("step:%-4d\t%ld us.\n",s,(end.tv_sec-begin.tv_sec)*1000000+(end.tv_usec-begin.tv_usec));
```
被以上两个宏定义包裹的代码块的运行时间将会被输出到终端，其中 END 可以提供整型参数作为提示信息。

```c
#define f(step) for(int index=0;index < N;index+=step){a[index]*=index;}
```
该宏的用法是根据传入的参数 `step` ，作为步长为 `step` 的循环，循环的总长度 `N` 为 `2^26` ，循环的内容是执行一次加法操作。
```c
int main(){
    int *a = new int[N];
    for (int j = 1; j <= 64; j*=2){
        BEGIN;
        f(j);
        END(j);
    }
}
```
以上代码用于对于不同步长的循环的执行时间进行测量。

## 代码的执行结果

代码的执行结果如下：
```txt
step:1   	286720 us.
step:2   	100646 us.
step:4   	51523 us.
step:8   	27507 us.
step:16  	19413 us.
step:32  	19203 us.
step:64  	11014 us.
```

## 我的设备情况

在我的设备上执行 `lscpu` 得到这台设备的 Cache 信息如下：
```txt
L1d cache:           32K
L1i cache:           32K
L2 cache:            4096K
L3 cache:            16384K
```
## 我的疑惑

为什么当步长为 16 和 32 时，循环花费的时间差距很小？

