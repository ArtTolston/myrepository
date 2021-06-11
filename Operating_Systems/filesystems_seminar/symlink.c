#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <io.h>

int main() {
	char pathname[10], previous_pathname[10];

	for(int i = 1; i < 1000; i++) {
		sprintf(pathname, "aaa%d", i);
		sprintf(previous_pathname, "aaa%d", i - 1);
		if(symlink(previous_pathname, pathname) < 0) {
			printf("cant create\n");
		}

		if(open(pathname, O_RDONLY) < 0) {
			printf("cant open file on %d iteration", i);
		}

		if(close(pathname) < 0) {
			printf("cant close file");
		}

	}


}