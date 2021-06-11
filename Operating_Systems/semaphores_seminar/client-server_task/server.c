//единственность
//киллер сервера получить сообщение с типом 2
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    
    int msqid;
    char pathname[]="server.c";
    key_t  key;
    int i,len, maxlen = 100;

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
    
    while (true){

       if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0)) < 0){
         printf("Can\'t receive message from client\n");
         exit(-1);
       }


       mybuf.mtype = mybuf.mpacket.pid;
       mybuf.mpacket.pid = 0;
       mybuf.mpacket.num = mybuf.mpacket.num * mybuf.mpacket.num;

       printf("send to client: %f\n", mybuf.mpacket.num);
       
       
       
       len = sizeof(mybuf.mpacket);
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to client\n");
         exit(-1);
       }

    }    

}