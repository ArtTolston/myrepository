#include <sys/types.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	struct sembuf mybuf;
	int semid, res;
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

	for(int i = 0; i < 14; i += 1) {
		res = fork();
		if(res < 0) {
			printf("cannot fork\n");
			exit(-1);
		} else if(res == 0) {
			continue;
		} else {
			break;
		}
	}

	mybuf.sem_op = -100;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	if(semop(semid, &mybuf, 1) < 0) {
		printf("Cannot get on the boat\n");
		exit(-1);
	}

	printf("Passenger is on the boat\n");

	mybuf.sem_op = 0;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	if(semop(semid, &mybuf, 1) < 0) {
		printf("Cannot get on the board\n");
		exit(-1);
	}

	mybuf.sem_op = 1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	if(semop(semid, &mybuf, 1) < 0) {
		printf("Cannot prove tickets\n");
		exit(-1);
	}

	mybuf.sem_op = -10;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;

	if(semop(semid, &mybuf, 1) < 0) {
		printf("Cannot get from the board\n");
		exit(-1);
	}

	return 0;

}