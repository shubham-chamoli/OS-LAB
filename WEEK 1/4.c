#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    }
    if(pid == 0) {
        printf("Child process started. PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(5);  
        printf("Child process (PID=%d) still running, new Parent PID = %d\n", getpid(), getppid());
        printf("This is an ORPHAN process example.\n");
        exit(0);
    }
    else {
        printf("Parent process started. PID = %d\n", getpid());
        printf("Parent creating a zombie process...\n");
        if(fork() == 0) { 
            printf("Zombie child (PID=%d) created.\n", getpid());
            exit(0); 
        }
        sleep(1);
        printf("Parent process exiting, first child will become orphan.\n");
    }
    return 0;
}
