#include<signal.h>
#include<stdio.h>

extern int i = 0;

void handler(int n) {
	
	if(n == SIGQUIT) {
		i++;
	}
}

int main() {
	
	void *p = signal(SIGQUIT, handler);
	while(i <= 5);
	(void)signal(SIGQUIT, p); 
	while(1);
}

