#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{  
    printf("Invoking 'filter' system call");
         
    long int ret_status = syscall(333); // 333 is the syscall number
         
    if(ret_status == 0) 
         printf("System call 'filter' executed correctly. Use dmesg to check processInfo\n");
    
    else 
         printf("System call 'filter' did not execute as expected\n");
          
     return 0;
}
