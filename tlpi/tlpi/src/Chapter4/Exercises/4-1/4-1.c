#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "tlpi_hdr.h"

#define MAXBUFF 1024

void usage (void)
{
	printf ("\ntee - read from standard input and write to standard output and files\n");
	printf ("\nUsage : ./tee [OPTION] [OutPutFileName]\n");
	printf ("OPTION : \n"\
		"-h : help\n"\
		"-a : append to the given FILEs, do not overwrite\n"\
		"-i : ignore SIGINT\n");
}

int main (int argc, char *argv[])
{
	int c = 0;
	char *outFile = NULL;
	int fout = -1;
	int numRead, numWrite;
	char *buff = NULL, *buff_init = NULL;
	int counter = 0;
	off_t offset;
	int ifAppend = 0;
	int ifInterruptIgnore = 0;
	int flags = 0, mode = 0;

	while ((c = getopt (argc, argv, "hai")) != -1) {
		switch (c) {
		case 'h':
			usage ();
			return 0;
			break;

		case 'a':
			ifAppend = 1;
			break;

		case 'i':
			ifInterruptIgnore = 1;
			break;
		}
	}
	
	outFile = argv[optind];
	printf ("optind = %d :: argv[optind] = %s\n", optind, argv[optind]);
	buff = calloc (1, MAXBUFF);
	if (buff == NULL) {
		errExit("calloc() failed to allocate buffer\n");
	}

	buff_init = buff;

	if (ifInterruptIgnore == 1) {
		signal(SIGINT, SIG_IGN);
	}

	flags = O_RDWR | O_CREAT | (ifAppend == 1 ? O_APPEND : O_TRUNC);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;	
	
	if (outFile != NULL) {
		printf ("outFile = %s\n", outFile);
		fout = open(outFile, flags, mode);
		if (fout == -1) {
			errExit("open() failed to open the output file\n");	
		
		}
	}

	numRead = read(STDIN_FILENO, buff, MAXBUFF); 
	if (numRead < 0) {
		errExit ("error in reading input file\n");
	}
	
	/* write to stdout */
	numWrite = write (STDOUT_FILENO, buff_init, numRead);
	if (numWrite == -1) {
		errExit ("write to stdout failed\n");
	}
	
	numWrite = 0;
	
	/* write to out file if specified */
	if (fout != -1) {
		numWrite = write (fout, buff_init, numRead);
		if (numWrite == -1) {
			errExit ("write to file failed\n");
		}
	}
	
	if (buff != NULL) {
		free (buff);
	}
	
	buff_init = NULL;
	
	if (fout != -1) {
		close (fout);
	}

	printf ("\n\ntee successful\n\n");
	return 0;
}
