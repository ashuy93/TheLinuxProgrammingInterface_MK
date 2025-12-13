#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE			/* Allow cc -D to override definiton*/
#define BUF_SIZE 1024
#endif



int 
main(int argc, char *argv[])
{
	int inputFd, outputFd, openFlags;
	ssize_t numRead;
	ssize_t numWrite;
	mode_t  filePerms;
	char buf[BUF_SIZE];

	if(argc != 3 || strcmp(argv[1],"--help") ==0 )
		usageErr("%s oldfile newfile\n", argv[0]);
	
	/* Open input and output files */
	

	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
		errExit("failed opening file %s\n ",argv[1]);

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH ; 
 
	outputFd = open(argv[2], openFlags, filePerms);
	if(outputFd == -1)
		errExit("failed opening file %s\n", argv[2]);
		
		/* Transfer data until we encounter end of input or an error */
	while(numRead = read(inputFd, buf, BUF_SIZE))
	{	if(write(outputFd, buf, numRead) != numRead)
			errExit("couldn't write whole buffer\n");
	}
	if(numRead == -1)
		errExit("read failed\n");	
	
	if(close(inputFd) == -1)
		errExit("close failed for oldfile\n");
		
	if(close(outputFd) == -1)
		errExit("close failed for newfile\n");
			
			
	exit(EXIT_SUCCESS);
}

