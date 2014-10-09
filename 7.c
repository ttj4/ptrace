/* Compile this program into `child3' */
#include <stdio.h>
#include <stdint.h>
#include <sys/cdefs.h>

main()
{
    printf("child3 starts...\n");
    asm("pushl %ebx\n\t" 
        "movl  $143, %ebx\n\t" 
        "L1: cmpl $245, %ebx\n\t"
        "jne L1\n\t" 
        "popl %ebx\n\t");
    printf("child3 outside loop...\n");
}

