/* `tracer' parent */
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
main()
{
    int pid, status;
    if((pid = fork()) == 0) {
        execl("/home/jinto/unix_exp/newfolder/signals/ptrace/child1", "child1", 0);
        printf("exec failed...\n");
    } else {
        sleep(1);
        kill(pid, SIGINT);
        wait(&status); // wait for child to stop
        if(WIFSTOPPED(status))
            printf("child has stopped...\n");
        sleep(3);
        ptrace(PTRACE_CONT, pid, 0, 0);
        /* Will not come out of this wait because
         * child does not terminate.
         */
        wait(&status); 
    }
}
        

