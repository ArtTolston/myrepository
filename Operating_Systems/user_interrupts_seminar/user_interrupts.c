#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdio.h>

int flag = 0;

void handler(int nsig) {
	flag = 1;
}

int main() {
	pid_t pid1 = getpid();
	printf("%d\n", pid1);

	pid_t pid2;

	scanf("%d", &pid2);

	int number = 75;
	int *status;

	signal(SIGUSR1, handler);

    for (int i = 128; i >= 1; i /= 2) {
    	printf("%d\n", i);
	    if ( i & number ) {// 1 
	        kill(pid2, SIGUSR1);
	    }
	    else {// 0 
	        kill(pid2, SIGUSR2);
		}

		while(!flag);
		flag = 0;
	}


}