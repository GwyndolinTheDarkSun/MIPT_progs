//странно , но предыдущая версия , которую вам показывал , программы не работала из-за atoi и глобального qId, после того,
//как qId стал передаваться через структуры , а atoi был заменен на strtod , все заработало
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct msgbuf {
   long mType;
   int mText[1];
};

typedef struct pdata{
    int index;
    int qId;
    int maxindex;
} pdata;

void *mythread(void *arg) {
    int a, qId;
    struct msgbuf msg, buf;
    pdata * datat = (pdata *) arg;
    a = datat->index;
    qId = datat->qId;
    if (msgrcv(qId, &buf, sizeof(msg.mText), a, 0) == -1) {
        perror("Thread : msgrcv failed:");
        exit(-1);
    }
    if (buf.mText[0] == 0)
        printf("I start the estaphete ! My number is %d\n", a);
    else
        printf("I've got the estaphete from %d, my number is %d\n", buf.mText[0], a);
    if (a != datat->maxindex) {
        msg.mType = a + 1;
        msg.mText[0] = a;
        /*sleep(1);*/
        if (msgsnd(qId, &msg, sizeof(msg.mText), 0) == -1) {
           perror( "Thread : msgsnd failed");
           exit(-1);
        }
    }
}

int main(int argc, char *argv[]) {
    int i, numb, qId;
    pthread_t *thread;
    key_t key;
    pdata *data;
    struct msgbuf msg;
    char *ptr;
    if (argc < 2) {
        perror("Too few arguments");
        return -1;
    }
    if ((key = ftok("/tmp", 0)) == -1) {
        perror("ftok failed");
        return errno;
    }
    if ((qId = msgget (key, 0666|IPC_CREAT|IPC_EXCL)) < 0) {
        if ((qId = msgget(key, 0)) < 0) {
            perror("Can't find message queue");
            return errno;
        }
    }
    numb = ((int) strtod(argv[1], &ptr)) + 1;
    if ((thread = (pthread_t *) malloc (numb * sizeof(pthread_t))) == NULL) {
        perror("Can't allocate thread array");
        if (msgctl(qId, IPC_RMID, (struct msqid_ds *) NULL) == -1) {
            perror("msgctl failed");
            free(thread);
            return errno;
        }
        return -1;
    }
    if ((data = (pdata *) malloc (numb * sizeof(pdata))) == NULL) {
        perror("Can't allocate thread array");
        if (msgctl(qId, IPC_RMID, (struct msqid_ds *) NULL) == -1) {
            perror("msgctl failed");
            free(thread);
            free(data);
            return errno;
        }
        free(thread);
        return -1;
    }
    for (i = 1; i < numb; i++) {
        data[i].index = i;
        data[i].maxindex = numb - 1;
        data[i].qId = qId;
        if (pthread_create(&thread[i], NULL, mythread,(void *) &data[i]) > 0) {
            perror("Can't create thread");
            if (msgctl(qId, IPC_RMID, (struct msqid_ds *) NULL) == -1) {
                perror("msgctl failed");
                free(thread);
                free(data);
                return errno;
            }
            free(thread);
            free(data);
            return -1;
        }
    }
    msg.mType = 1;
    msg.mText[0] = 0;
    if (msgsnd(qId, &msg, sizeof(msg.mText), 0) == -1) {
        perror("msgsnd failed");
        if (msgctl(qId, IPC_RMID, (struct msqid_ds *) NULL) == -1) {
            perror("msgctl failed");
            free(thread);
            free(data);
            return errno;
        }
        free(thread);
        free(data);
        return errno;
    }
    pthread_join(thread[numb - 1], (void **) NULL);
    if (msgctl(qId, IPC_RMID, (struct msqid_ds *) NULL) == -1) {
        perror("msgctl failed");
        free(thread);
        free(data);
        return errno;
    }
    free(thread);
    free(data);
    return 0;
}
