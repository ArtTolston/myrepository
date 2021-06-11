#include <sys/types.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	struct sembuf mybuf;
	int semid;
	key_t key;
	char pathname[] = "boat.c";

	if((key = ftok(pathname, 0)) < 0) {
		printf("Cannot generate key\n");
		exit(-1);
	}


	if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("Cannot get semid\n");
		exit(-1);
	}

	mybuf.sem_op = 500;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;


	if(semop(semid, &mybuf, 1) < 0) { //A(s,500)
		printf("Cannot set 500 to semaphore\n");
		exit(-1);
	}


	for(int i = 0; i < 3; i += 1) {

		printf("Embarkation number: %d", i);

		mybuf.sem_op =  0;
		mybuf.sem_flg = 0;
		mybuf.sem_num = 0;

		if(semop(semid, &mybuf, 1) < 0) {  // Z(s)
			printf("Cannot wait all passengers get to boat\n");
			exit(-1);
		}

		printf("Check passenger's tickets\n");

		mybuf.sem_op = -1;
		mybuf.sem_flg = 0;
		mybuf.sem_num = 0;

		for(int j = 0; j < 5; j += 1) {

			if(semop(semid, &mybuf, 1) < 0) {  // D(s, 1)
				printf("Cannot check tickets\n");
				exit(-1);
			}
		}

		printf("Sailing\n");

		mybuf.sem_op = 50;
		mybuf.sem_flg = 0;
		mybuf.sem_num = 0;

		if(semop(semid, &mybuf, 1) < 0) { // A(s, 50)
			printf("Cannot let passengers go\n");
			exit(-1);
		}

		mybuf.sem_op =  0;
		mybuf.sem_flg = 0;
		mybuf.sem_num = 0;

		if(semop(semid, &mybuf, 1) < 0) {  //Z(s)
			printf("Cannot not all passengers leave boat\n");
			exit(-1);
		}

		mybuf.sem_op = 500;
		mybuf.sem_flg = 0;
		mybuf.sem_num = 0;

		if(semop(semid, &mybuf, 1) < 0) { //A(s, 500)
			printf("Cannot let passengers go\n");
			exit(-1);
		}

		printf("End of Sailing\n\n\n");
	}
}