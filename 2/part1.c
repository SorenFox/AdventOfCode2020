#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validPass(int min, int max, char ch, char *password);

int main(int argc, char **argv) {
	int valids = 0;
	char *password = (char*)malloc(101);
	char ch;
	int min, max;
	FILE *fp = fopen(argv[1], "r");
	
	while (fscanf(fp, "%d-%d %c: %s", &min, &max, &ch, password) == 4) {
		if (validPass(min, max, ch, password)) {
			valids++;
			printf("%s is valid\n", password);
		}
	}

	printf("Valid passwords: %d", valids);
	
	fclose(fp);
	
	return 0;
}

int validPass(int min, int max, char ch, char *password) {
	int i = 0;
	int num = 0;
	int valid = 0;

	while (password[i] != '\0') {
		if (password[i] == ch)
			num++;
		i++;
	}

	if (num <= max && num >= min)
		valid = 1;

	return valid;
}
