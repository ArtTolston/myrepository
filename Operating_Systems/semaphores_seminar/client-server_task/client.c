#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>



int main(void)
{
    
    int msqid;
    char pathname[]="09-1a.c";
    key_t  key;
    int i,len, maxlen = 81;

    struct mymsgbuf
    {
       long mtype;
       struct packet {
        int pid;
        double num;
     } mpacket;
    } mybuf;



    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }


    /* Send information */

    double num = 2.0;
    
    for (i = 1; i <= 3; i++){
       
       mybuf.mtype = 2;
       mybuf.mpacket.pid = getpid();
       mybuf.mpacket.num = num;
       len = sizeof(mybuf.mpacket);

       printf("send to server: %f", num);
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to server\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
       }

      if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, getpid(), 0)) < 0){
         printf("Can\'t receive message from server\n");
         exit(-1);
       }

    }    

    return 0;    
}
