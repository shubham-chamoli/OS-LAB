#include <stdio.h>
#include <unistd.h>
int main(){
    // Create a child process
    pid_t pid = fork();
    if (pid < 0){
        // Fork failed
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0){
        // This is the child process
        printf("Child Process:\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else{
        // This is the parent process
        printf("Parent Process:\n");
        printf("PID: %d, Child PID: %d\n", getpid(), pid);
    }
    return 0;
}
