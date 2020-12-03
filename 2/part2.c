#include <stdio.h>
#include <stdlib.h>

int validPass(int min, int max, char ch, char *password);

int main(int argc, char **argv) {
	int valids = 0;
	char *password = (char*)malloc(101);
	char ch;
	int pos1, pos2;
	FILE *fp = fopen(argv[1], "r");
	
	while (fscanf(fp, "%d-%d %c: %s", &pos1, &pos2, &ch, password) == 4) {
		if (validPass(pos1, pos2, ch, password)) {
			valids++;
			printf("%s is valid\n", password);
		}
	}

	printf("Valid passwords: %d", valids);
	
	fclose(fp);
	free(password);

	return 0;
}

int validPass(int pos1, int pos2, char ch, char *password) {
	int i = 0;
	int num = 0;
	int valid = 0;

	while (password[i] != '\0') {
		if (password[i] == ch && (i == (pos1-1) || i == (pos2-1)))
			num++;
		i++;
	}

	if (num == 1)
		valid = 1;

	return valid;
}
