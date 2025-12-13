#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc, char *argv[])
{
		size_t len;
		off_t offset;
		char *buf;
		ssize_t numRead, numWritten;
		int fd,ap,j,openFlags;
		mode_t filePerms;
		
		
		if (argc < 3 || strcmp(argv[1],"--help") == 0)
			usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[1]);
		
		openFlags = O_RDWR | O_CREAT;
		filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		
		fd = open(argv[1], openFlags, filePerms);
			if (fd == -1)
				errExit("open Failed for %s\n",argv[1]);
		for (ap = 2; ap < argc; ap++){
			switch (argv[ap][0]){
				case 'r': /* Display bytes at current offset, as text */
				case 'R': /* Display bytes at current offset, in hex  */
					len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
					buf = malloc(len);
					if (buf == NULL)
						errExit("malloc failed\n");
					
					numRead = read(fd, buf, len);
						if (numRead == -1)
							errExit("read() failed\n");
					
					if (numRead == 0)
						errExit("%s: end-of-file\n",argv[ap]);
				
					else{
							printf("%s: ", argv[ap]);
							for (j = 0; j < numRead; j++ ){
									if (argv[ap][0] == 'r')
										printf("%c", isprint((unsigned char) buf[j]) ?	buf[j] : '?');
									else
										printf("%02x ", (unsigned int) buf[j]);
								}
								printf("\n");
									
						}
						free(buf);
						break;
					
					case 'w': /* Write string at current offset */
						numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
							if (numWritten == -1)
								errExit("write() failed\n");
							printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
							break;
					
					case 's': /* Change file offset */
						offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
							if(lseek(fd, offset, SEEK_SET) == -1)
								errExit("lseek() failed\n");
						printf("%s: seek succeeded\n",argv[ap]);
						break;
					
					default:
						printf("Argument must start with [rRws]: %s\n", argv[ap]);
				}
			
			}
			
			exit(EXIT_SUCCESS);
		
} 
