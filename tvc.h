#include <unistd.h>
#include <stdlib.h>

int
randomid(char id[], int c)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	for (int i = 0; i < c - 1; i++) {
		int r;
		r = rand() % (sizeof(charset) - 1);
		id[i] = charset[r];
		printf("");
	}

	id[c] = '\0';

	return 0;
}

int
tvcinit()
{
	char *cherr;
	int err;

	err = system("mkdir -p .tvc");
	if (err != 0) {
		return 1;
	}

	return 0;
}

int
tvccommit(char *files[], char *message, int messagec)
{
	char id[5];

	randomid(id, sizeof(id));

	printf("id is %s\n",id);
	return 0;
}