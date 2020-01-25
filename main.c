#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>

#include "./tbv.h"

void
help(void)
{
	printf("usage: tbv <command> [<args>]\n\n"
	       "\tcommit  Record changes to the repository\n"
	       "\tinit    Create an empty tbv repository\n"
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

		int err = tbvinit();
		if (err != 0) {
			fprintf(stderr, "FATAL: could not initialize\n");
			exit(EXIT_FAILURE);
		}

		char *cherr = getcwd(cwd, sizeof(cwd));
		if (cherr == NULL) {
			return 1;
		}
		printf("Initialised empty tbv repository in %s/.tbv\n", cwd);
	} else if (strcmp(argv[1], "commit") == 0) {

		char input[40];

		printf("Enter a commit name: ");
		fgets(input, sizeof(input), stdin);
		// strlcpy(input, "the commit name\n", sizeof(input));

		int err = tbvcommit(input, sizeof(input));
		if (err != 0) {
			fprintf(stderr, "FATAL: failed comitting\n");
			exit(EXIT_FAILURE);
		}
	} else if (strcmp(argv[1], "log") == 0) {
		tbvlog();
	} else {
		help();
		exit(EXIT_FAILURE);
	}

	return 0;
}