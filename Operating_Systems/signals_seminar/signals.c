#include<signal.h>
#include<stdio.h>

void handler(int n) {
	if(n == SIGQUIT) {
		printf("SIGQUIT\n");
	} else if(n == SIGINT) {
		printf("SIGINT\n");
	}
}

int main() {
	
	(void)signal(SIGQUIT, handler);
	(void)signal(SIGINT, handler);
	while(1);
}