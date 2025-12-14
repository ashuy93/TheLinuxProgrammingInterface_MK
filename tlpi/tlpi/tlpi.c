#define _XOPEN_SOURCE 600
#include "tlpi_hdr.h"
#include <libgen.h>
#include <ftw.h>

#define SRC_PATH "./src"

char *program_name = NULL;
char **argv_to_program = NULL;

void
print_help()
{
	usageErr ("\n./tlpi ChapterNum-ExerciseNum argv ...");
}

int
invoke_program (const char *pathname, const struct stat *statbuf,
					int typeflag, struct FTW *ftwb)
{
	int ret;
	char *basename_of_path = basename((char *)pathname);

	if (strncmp(basename_of_path, program_name, strlen(basename_of_path))) {
		return 0;
	} else {
		if (fork() == 0) {
			execv(pathname, argv_to_program);
		} else {
			wait(&ret);
		}
	}

	return 0;
}

int
main (int argc, char *argv[])
{
	char name[20];

	if (argc < 2) {
		print_help();
	}

	memcpy(name, argv[1], strlen(argv[1]));

	program_name = name;

	argv_to_program = &argv[1];

	if (nftw(SRC_PATH, invoke_program, 10, 0) == -1) {
		errExit ("nftw() failed\n");
	}

	exit(EXIT_SUCCESS);
}
