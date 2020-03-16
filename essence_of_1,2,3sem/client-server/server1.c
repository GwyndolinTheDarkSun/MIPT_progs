#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>

#define FIFO "ServerFifo"
#define pageSIZE 4096
#define sizestrPID 11
#define startNumbClients 5
#define shrChar 5

typedef struct argStruct {
    char text[pageSIZE+ 1];
} argStruct;

pthread_t *thread;
argStruct *args;

void exit_server (int signo) {
    system("clear");
    puts("Server finished working");
    free(thread);
    free(args);
    unlink(FIFO);
    exit(EXIT_SUCCESS);
}

void *mythread (void *arg) {
    int fd_file, fd_client, pid_client, read_count, i, j;
    char FILE_name[pageSIZE- sizestrPID - 2] = {0};
    char fifo_client[sizestrPID] = {0};
    char buf[pageSIZE] = {0};
    argStruct * c = (argStruct *) arg;
    // signal handler
    for (i = 0; c->text[i] != shrChar; i++) {
        fifo_client[i] = c->text[i];
    }
    pid_client = (int) strtod(fifo_client, NULL);
    for (j = i + 1; c->text[j] != shrChar; j++) {
        FILE_name[j - i - 1] = c->text[j];
    }
    //открываем требуемый файл на чтение
    if ((fd_file = open(FILE_name, O_RDONLY)) < 0) {
        printf("Open File\n");
        kill(pid_client, SIGUSR1);
    } else {
        //открываем FIFO клиента
        if ((fd_client = open(fifo_client, O_WRONLY)) < 0) {
            printf("Open fifo_client\n");
            kill(pid_client, SIGUSR1);
        } else {
            //читаем в цикле по 4096 байт из требуемого файла до ошибки или до конца файла
            while ((read_count = read(fd_file, buf, pageSIZE)) > 0) {
                //пишем считанные 4096 байт в FIFO клиента
                if ((write(fd_client, buf, read_count)) <= 0) {
                    printf("Write client\n");
                    kill(pid_client, SIGUSR1);
                    break;
                }
            }
            puts("Request processed succesfully");
        }
        //закрываем все дескрипторы
        close(fd_client);
    }
    close(fd_file);
}

int main() {
    int i, fd_server, a;
    char buf[pageSIZE];
    (void)umask(0);
    unlink(FIFO);
    
    //корректно обрабатываем CTRL + Z ( сигнал SIGTSTP )
    signal(SIGTSTP, exit_server);
    
    signal(SIGINT, exit_server);
    
    //создаем FIFO для сервера
    if (mknod(FIFO, S_IFIFO | 0666, 0) < 0) {
        printf("FIFO");
        exit(-1);
    }
    //открываем FIFO сервера на чтение
    if ((fd_server = open(FIFO, O_NONBLOCK)) < 0) {
        printf("Open ServerFifo\n");
        exit(-1);
    }
    i = 0;
    if ((thread = (pthread_t *) malloc (startNumbClients * sizeof(pthread_t))) == NULL) {
        perror("Can't allocate thread array");
        return -1;
    }
    if ((args = (argStruct *) malloc (startNumbClients * sizeof(argStruct))) == NULL) {
        perror("Can't allocate args array");
        return -1;
    }
    while(1) {
        if (read(fd_server, buf, pageSIZE) > 0) {
            if ((i % startNumbClients) == 0) {
                a = ((i % startNumbClients) + 2) * startNumbClients;
                if ((thread = (pthread_t *) realloc (thread, a * sizeof(pthread_t))) == NULL) {
                    perror("Can't reallocate thread array");
                    free(thread);
                    free(args);
                    return -1;
                }
                if ((args = (argStruct *) realloc (args, a * sizeof(argStruct))) == NULL) {
                    perror("Can't reallocate args array");
                    free(thread);
                    free(args);
                    return -1;
                }
            }
            strcpy(args[i].text, buf);
            if (pthread_create(&thread[i], NULL, mythread,(void *) &args[i]) > 0) {
                perror("Create Thread");
                return -1;
            }
            i++;
        }
    }
    return 0;
}
