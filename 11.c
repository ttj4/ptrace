#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <signal.h>
main()
{
	int status,pid,dat;
	unsigned long addr = 0x0000000000601044;
	status = 0;
	if ((pid = fork()) == 0) {
		ptrace(PTRACE_TRACEME,0,0,0);
		execl("/home/jinto/unix_exp/newfolder/signals/ptrace/child5","child5",0);
		printf("error execl\n");
	}
	else {
		//wait for child to stop at the `exec'
		wait(&status);
		while(1) {
		     // do just one instruction
		     ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
		     wait(&status);
		     if(WIFEXITED(status)) break;
		     // `addr' is address of `i' in child process
		     dat = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
		     if(dat == 10) {
        			ptrace(PTRACE_POKEDATA, pid, addr, 2341);
   			        ptrace(PTRACE_CONT, pid, 0, 0);
 	         break;
     		 }
		}
		wait(&status);
		if(WIFEXITED(status))printf("child over\n");
	}
}

