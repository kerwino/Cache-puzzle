# Cache-puzzle
---
## 更新
下面是关于我的设备 CPU 更加详细的信息
```txt
processor	: 0
vendor_id	: AuthenticAMD
cpu family	: 23
model		: 49
model name	: AMD EPYC 7K62 48-Core Processor
stepping	: 0
microcode	: 0x1000065
cpu MHz		: 2595.124
cache size	: 512 KB
physical id	: 0
siblings	: 2
core id		: 0
cpu cores	: 2
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm rep_good nopl cpuid extd_apicid tsc_known_freq pni pclmulqdq ssse3 fma cx16 sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm cmp_legacy cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw topoext ibpb vmmcall fsgsbase bmi1 avx2 smep bmi2 rdseed adx smap clflushopt sha_ni xsaveopt xsavec xgetbv1 arat
bugs		: fxsave_leak sysret_ss_attrs spectre_v1 spectre_v2 spec_store_bypass
bogomips	: 5190.24
TLB size	: 1024 4K pages
clflush size	: 64
cache_alignment	: 64
address sizes	: 48 bits physical, 48 bits virtual
power management:

processor	: 1
vendor_id	: AuthenticAMD
cpu family	: 23
model		: 49
model name	: AMD EPYC 7K62 48-Core Processor
stepping	: 0
microcode	: 0x1000065
cpu MHz		: 2595.124
cache size	: 512 KB
physical id	: 0
siblings	: 2
core id		: 1
cpu cores	: 2
apicid		: 1
initial apicid	: 1
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm rep_good nopl cpuid extd_apicid tsc_known_freq pni pclmulqdq ssse3 fma cx16 sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm cmp_legacy cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw topoext ibpb vmmcall fsgsbase bmi1 avx2 smep bmi2 rdseed adx smap clflushopt sha_ni xsaveopt xsavec xgetbv1 arat
bugs		: fxsave_leak sysret_ss_attrs spectre_v1 spectre_v2 spec_store_bypass
bogomips	: 5190.24
TLB size	: 1024 4K pages
clflush size	: 64
cache_alignment	: 64
address sizes	: 48 bits physical, 48 bits virtual
power management:
```
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

