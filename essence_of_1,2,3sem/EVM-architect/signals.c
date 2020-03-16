#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/errno.h>

#define pageSIZE 4096
char array[pageSIZE] = {0}, array1[pageSIZE] = {0};
int count = 0, bit;
pid_t pid;

void exit_for_parent(int signo) {
    write(STDOUT_FILENO, array, count);
    exit(EXIT_SUCCESS);
}

void exit_for_child(int signo) {
    exit(EXIT_SUCCESS);
}

void gentle_exit(int signo) {
    kill(pid, SIGUSR2);
    write(STDOUT_FILENO, array, count);
    exit(EXIT_SUCCESS);
}

void empty(int signo) {
}

void one(int signo) {
    bit = 1;
}

void zero(int signo) {
    bit = 0;
}


int main(int argc, char ** argv){
    
    if (argc != 2) {
        perror("Wrong amount of args");
        exit(EXIT_FAILURE);
    }
    pid_t ppid = getpid();
    
    sigset_t set, old_set;
    
    signal(SIGCHLD, exit_for_parent);
    
    signal(SIGUSR1, zero);
    
    signal(SIGUSR2, one);
    
    signal(SIGTSTP, gentle_exit);
    
    signal(SIGINT, gentle_exit);
    
    sigemptyset(&set);
    
    sigaddset(&set, SIGTSTP);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, &old_set);
    
    pid = fork();
    
    if (pid == 0) {
        
        unsigned int fd = 0;
        int i, j, read_done;
        
        sigset_t set1, old_set1;
        
        sigemptyset(&set1);
        
        sigaddset(&set1, SIGUSR1);
        sigaddset(&set1, SIGUSR2);
        
        //sigaddset(&set1, SIGALRM);
        
        sigprocmask(SIG_BLOCK, &set1, &old_set1);
        
        signal(SIGUSR1, empty);
        
        signal(SIGUSR2, exit_for_child);
        
        //signal(SIGALRM, exit_for_child);
        
        if ((fd = open(argv[1], O_RDONLY)) < 0){
            perror("Can't open file");
            exit(EXIT_FAILURE);
        }
        
        while ((read_done = read(fd, array1, pageSIZE)) > 0){
            //alarm(1);
            for (j = 0; j < read_done; j++)
                for ( i = 0; i < 8; i++){
                    if ((array1[j] & (1 << (7 - i))) == 0)
                        kill(ppid, SIGUSR1);
                    else
                        kill(ppid, SIGUSR2);
                    sigsuspend(&old_set);
                }
        }
        exit(EXIT_SUCCESS);
    }
    
    int i;
    
    while(1) {
        memset(array, '\0', pageSIZE);
        for (count = 0; count < pageSIZE; count++) {
                for (int i = 0; i < 8; ++i) {
                        sigsuspend(&old_set);
                        array[count] |= bit << (7 - i);
                        if (i != 7)
                            kill(pid, SIGUSR1);
                }
                if (count != pageSIZE - 1)
                        kill(pid, SIGUSR1);
        }
        write(STDOUT_FILENO, array, pageSIZE);
        kill(pid, SIGUSR1);
    }
    
    exit(EXIT_SUCCESS);
}
