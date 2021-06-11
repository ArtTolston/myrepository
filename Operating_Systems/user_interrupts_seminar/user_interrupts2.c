#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdio.h>

char number = 0;
int counter = 128;
pid_t pid2;

void my_handler1(int nsig) {
	if (nsig == SIGUSR1) {
		number += counter;
		counter /= 2;
	} else {
		counter /= 2;	
	}
	kill(pid2, SIGUSR1);
	printf("%d\n", number);
}

int main() {
	signal(SIGUSR1, my_handler1);
	signal(SIGUSR2, my_handler1);

	pid_t pid1 = getpid();
	printf("%d\n", pid1);

	scanf("%d", &pid2);

	





	while(1);

}