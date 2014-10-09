#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <bits/signum.h>
#include <sys/ptrace.h>

main()
{
	ptrace(PTRACE_TRACEME,0,0,0);
	while(1);
}
