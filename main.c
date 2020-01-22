#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include "./tvc.h"

void
help(void)
{
	printf("usage: tvc <command> [<args>]\n\n"
	       "\tcommit  Record changes to the repository\n"
	       "\tinit    Create an empty tvc repository\n"
	       "\tlog     Show commit logs\n");
}

int
main(int argc, char *argv[])
{
	if (argc == 1) {
		help();
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "init") == 0) {
		char cwd[100];

		int err = tvcinit();
		if (err != 0) {
			fprintf(stderr, "E: could not initialize\n");
			exit(EXIT_FAILURE);
		}

		char *cherr = getcwd(cwd, sizeof(cwd));
		if (cherr == NULL) {
			return 1;
		}
		printf("Initialised empty tvc repository in %s/.tvc\n", cwd);
	} else if (strcmp(argv[1], "commit") == 0) {
		if (argc < 3) {
			fprintf(stderr, "nothing to commit, exiting\n");
			exit(EXIT_FAILURE);
		}


		char input[40];
		char *files[argc - 2];

		printf("Enter a commit name: ");
		// fgets(input, sizeof(input), stdin);
		strlcpy(input,"the commit name",sizeof(input));

		for (int i = 2; i < argc; i++) {
			files[i - 2] = argv[i];
		}

		int err = tvccommit(files, input, sizeof(input));
		if (err != 0) {
			fprintf(stderr, "E: failed comitting\n");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}