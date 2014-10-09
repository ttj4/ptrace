//segment of code which alters value of
//a variable in a child process. Identical
//to code which reads and changes register value.

//`addr' is address of variable being accessed.
#include <stdio.h>
#include <sys/ptrace.h>
#include <signal.h>
main()
{
	int data,pid;
	int status = 0;
	unsigned long int addr = 0x0000000000601040;
	if ((pid = fork()) == 0) {
		ptrace(PTRACE_TRACEME,0,0,0);
		execl("/home/jinto/unix_exp/newfolder/signals/ptrace/child4","child4",0);
		printf("exec error\n");
	}
	else {
		wait(&status);
		ptrace(PTRACE_CONT,pid,0,0);
		sleep(1);
		kill(pid,SIGINT);
		wait(&status);
		data = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
		printf("data = %d\n", data);
		data = 245;
		ptrace(PTRACE_POKEDATA, pid, addr, data);
		ptrace(PTRACE_CONT, pid, 0, 0); 
		wait(&status);
	}
}


