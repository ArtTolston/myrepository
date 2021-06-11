#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	DIR *mydir;

	if(argc == 2) {
		mydir = opendir(argv[1]);
	} else {
		mydir = opendir("./");
	}

	struct dirent *file;

	printf("filename\t\t\ttype\t\t\tlink\n");

	while((file = readdir(mydir)) != NULL) {
		struct stat stats;

		char filename[100];
		if(argc == 2) {
			sprintf(filename, "%s%s", argv[1], file->d_name);
		} else {
			sprintf(filename, "./%s", file->d_name);
		}
		printf("%s\r\t\t\t\t", filename);


		if(lstat(filename, &stats) != 0) {
			printf("fail\n");
		}

		if(S_ISLNK(stats.st_mode) != 0) {
			printf("link\t\t");

			char pathname[100];
			int ret;

			if((ret = readlink(filename, pathname, 100)) == -1) {
				printf("oshibka\n");
			}
			pathname[ret + 1] = '\0';

			printf("%s\n", pathname);
		} else if(S_ISDIR(stats.st_mode)){
			printf("dir \n");


		} else if(S_ISREG(stats.st_mode)) {
			printf("regular file\n");
		} else if(S_ISBLK(stats.st_mode)) {
			printf("block device\n");
		} else if(S_ISCHR(stats.st_mode)) {
			printf("char device\n");
		}
		
	}
} 