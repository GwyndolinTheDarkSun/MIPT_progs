#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <ncurses.h>

#define pageSIZE 4096
#define sizestrPID 11
#define shrChar 5 //значение символа , который разделяет pid клиента и имя файла

char FIFO_client[sizestrPID] = {0};

//выходим из программы
void exit_client (int signo) {
    puts("Something strange happened");
    unlink(FIFO_client);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    int fd, len, size, i, j, rd;
    char buf[pageSIZE] = {0};
    char FIFO_client_info[pageSIZE] = {0};
    pid_t pid;
    char * FILE_NAME = argv[1];
    
    //создаем хэндлер для обработки завершения клиента из сервера ( сигнал SIGUSR1 ) 
    
    signal(SIGUSR1, exit_client);
    
    /*проверяем количество аргументов*/
    if (argc < 2) {
        perror("argc");
        return -1;
    }
    (void)umask(0);
    /*получаем pid процесса*/
    if ((pid = getpid()) < 0) {
        perror("getpid");
        exit(-1);
    }
    /*переводим pid из числа в строку и записываем в FIFO_client , это будет имя FIFO клиента*/
    sprintf(FIFO_client, "%d", pid);
    /*заполняем первую часть буфера , который мы кладем в FIFO сервера , кладя в нее FIFO /клиента*/
    for (i = 0; FIFO_client[i] != '\0'; i++) {
        FIFO_client_info[i] = FIFO_client[i];
    }
    /*кладем разделяющий знак между частями информации в буфере*/
    FIFO_client_info[i] = shrChar;
    /*заполняем вторую часть помещаемой информации именем файла*/
    for (j = i + 1; FILE_NAME[j - i - 1] != '\0'; j++) {
        if (j == pageSIZE) {
            printf("Too large FILE name, maximum 4084 letters\n");
            exit(-1);
        }
        FIFO_client_info[j] = FILE_NAME[j - i - 1];
    }
    /*кладем символ конца строки*/
    FIFO_client_info[j] = shrChar;
    /*удаляем файлы с именем FIFO_client*/
    unlink(FIFO_client);
    /*создаем поток работы с сервером FIFO_client*/
    if (mknod(FIFO_client, S_IFIFO | 0666, 0) < 0) {
        printf("Can't make FIFO\n");
        exit(-1);
    }
    /*открываем заведомо известный ранее созданный на сервере FIFO сервера ServerFifo на запись*/
    if ((fd = open("ServerFifo", O_WRONLY)) < 0) {
        printf("Open ServerFifo\n");
        close(fd);
        exit(-1);
    }
    len = strlen(FIFO_client_info);
    /*записываем в FIFO сервера имя FIFO клиента и имя требуемого файла*/
    if ((write(fd, FIFO_client_info, len)) <= 0) {
        perror("write");
        close(fd);
        exit(-1);
    }
    /*закрываем дескриптор FIFO сервера на запись*/
    close(fd);
    /*открываем FIFO клиента на чтение*/
    if ((fd = open(FIFO_client, O_RDONLY)) < 0) {
        printf("Open FIFO\n");
        close(fd);
        exit(-1);
    }
    /*читаем по pageSIZE байт и печатаем*/
    while ((rd = read(fd, buf, pageSIZE)) > 0) {
        //sleep(2);
        if ((write(STDOUT_FILENO, buf, rd)) < 0) {
            perror("write");
            exit(-1);
        }
    }
    //проверяем на ошибку чтения из FIFO
    if (rd < 0) {
        printf("Read from FIFO\n");
        close(fd);
        exit(-1);
    }
    unlink(FIFO_client);
    close(fd);
    return 0;
}

