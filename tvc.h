#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int
now(char *out, int outc)
{
	struct tm *to;
	time_t t;
	t = time(NULL);
	to = localtime(&t);
	strftime(out, outc, "%Y-%m-%d %H:%M:%S", to);

	return 0;
}

int
fileappend(char path[], char buffer[], int bufferc)
{
	FILE *pFile = fopen(path, "a");
	if (pFile == NULL) {
		fprintf(stderr, "E: pFile is null\n");
		return 1;
	}

	int c = fprintf(pFile, "%s", buffer);
	if (c == 0) {
		fprintf(stderr, "E: failed printing to pFile\n");
		return 1;
	}

	int err = fclose(pFile);
	if (err != 0) {
		fprintf(stderr, "E: failed closing file\n");
		return 1;
	}

	return 0;
}

int
randomid(char id[], int c)
{
	const char charset[] = "abcdef0123456789";
	srand(time(NULL));

	for (int i = 0; i < c - 1; i++) {
		int r;
		r = rand() % (sizeof(charset) - 1);
		id[i] = charset[r];
	}

	id[c] = '\0';

	return 0;
}

int
tvcinit()
{
	char *cherr;
	int err;

	err = system("mkdir -p .tvc/logs");
	if (err != 0) {
		return 1;
	}

	err = system("touch .tvc/logs/HEAD");
	if (err != 0) {
		return 1;
	}

	return 0;
}

int
tvccommit(char *files[], char *message, int filesc, int messagec)
{
	char id[6];
	char cmd[50];

	randomid(id, sizeof(id));

	strlcpy(cmd, "tar --exclude=.tvc -czf .tvc/", sizeof(cmd));
	strlcat(cmd, id, sizeof(cmd));
	strlcat(cmd, ".tgz ", sizeof(cmd));

	for (size_t i = 0; i < filesc; i++) {
		strlcat(cmd, files[i], sizeof(cmd));
		if (i == filesc - 1) {
			break;
		}
		strlcat(cmd, " ", sizeof(cmd));
	}

	int err = system(cmd);
	if (err != 0) {
		fprintf(stderr, "E: failed creating tar\n");
		return 1;
	}

	char time[20];
	now(time, sizeof(time));

	err = fileappend(".tvc/logs/HEAD", time, sizeof(time));
	if (err != 0) {
		fprintf(stderr, "E: failed appending to HEAD\n");
		return 1;
	}

	fileappend(".tvc/logs/HEAD", ",", sizeof(""));
	fileappend(".tvc/logs/HEAD", id, sizeof(id));
	fileappend(".tvc/logs/HEAD", ",", sizeof(""));
	fileappend(".tvc/logs/HEAD", message, messagec);

	return 0;
}

int
tvclog()
{
	char cmd[] =
	    "tac .tvc/logs/HEAD | sed 's/$/\\n/g; s/,/\\n\\t/g' | less -X -F";

	int err = system(cmd);

	if (err != 0) {
		return 1;
	}

	return 0;
}