#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"
#include <getopt.h>


static int app_mode = 0;
int parse_option(int argc, char *argv[]);

int main(int argc, char *argv[])
{
		ssize_t numRead, numWrite;
		char buf[BUFSIZ];
		mode_t file_mode;
		int  i, nfiles;
		int files[10];
					
		if (parse_option(argc, argv)) {
			return 1;
		}
		
		file_mode  = (app_mode ? O_APPEND : O_TRUNC);
		file_mode |= O_RDWR | O_CREAT;
		nfiles = argc - optind;
		if (nfiles > 0) {
			if (files == NULL) {
				errExit("fopen failed\n");
		}

			for (i = optind; i < argc; i++) {
				int File = open(argv[i], file_mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
				if (File == -1)
					errExit("open failed\n");
				files[i - optind] = File;
			}
		}
		
		while ((numRead = read(0, buf, sizeof buf)) > 0) {
				write(1, buf, numRead);
				if(numWrite == -1)			
					errExit("write to stdout failed\n");
				if(nfiles > 0)
					for (i = 0; i < nfiles; i++) {
						numWrite = write(i+3, buf, numRead);
						if(numWrite != numRead)
							errExit("write to file failed\n");
				}
	}
		if (nfiles > 0) {
		for (i = 0; i < nfiles; i++) {
			if(close(i) == -1)
				errExit("close() failed for file fd = %d\n", i);
		}	
	}
		
		exit(EXIT_SUCCESS);
}
int parse_option(int argc, char *argv[]){
	
		char c;
		
	while ((c = getopt(argc, argv, "a")) != -1) {
		switch (c) {
		case 'a':
			app_mode = 1;
			break;
		default:
			abort();
			break;
		}
	}
	return 0;
	
}
