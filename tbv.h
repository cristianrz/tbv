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

	// printf("=====\n");
	// printf("message: '%s'", buffer);
	// printf("=====\n");

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
tbvinit()
{
	char *cherr;
	int err;

	err = system("mkdir -p .tbv/logs");
	err = system("mkdir -p .tbv/objects");
	if (err != 0) {
		return 1;
	}

	err = system("touch .tbv/logs/HEAD");
	if (err != 0) {
		return 1;
	}

	return 0;
}

int
tbvcommit(char *message, int messagec, char *id, int idc)
{
	char cmd[100], time[20], line[150];
	int linec = sizeof(line);

	randomid(id, idc);

	strlcpy(cmd, "tar --exclude=.tbv -czf .tbv/objects/", sizeof(cmd));
	strlcat(cmd, id, sizeof(cmd));
	strlcat(cmd, ".tgz .", sizeof(cmd));

	int err = system(cmd);
	if (err != 0) {
		fprintf(stderr, "E: failed creating tar\n");
		return 1;
	}

	now(time, sizeof(time));

	(void)strlcat(line, id, linec);
	(void)strlcat(line, ",", linec);
	(void)strlcat(line, time, linec);
	(void)strlcat(line, ",", linec);
	(void)strlcat(line, message, linec);
	(void)strlcat(line, "\n", linec);

	err = fileappend(".tbv/logs/HEAD", line, sizeof(line));
	if (err != 0) {
		fprintf(stderr, "E: Failed to commit\n");
		return 1;
	}

	printf("[%s] %s\n", id, message);

	return 0;
}

int
tbvlog()
{
	char cmd[] =
	    "tac .tbv/logs/HEAD | sed 's/$/\\n/; s/^/commit /; s/,/\\nDate: /; s/,/\\n\\n\\t/' | less";

	int err = system(cmd);

	if (err != 0) {
		return 1;
	}

	return 0;
}