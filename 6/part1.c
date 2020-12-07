#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	char *text = (char*)malloc(1);
	int i = 0, j;
	int yesses[26] = {0};
	int sum = 0;

	text[i] = fgetc(fp);
	
	while (text[i] != EOF) {
		i++;
		text = (char*)realloc(text, i+1);
		text[i] = fgetc(fp);
	}
	
	text = (char*)realloc(text, i+1);
	text[i] = '\0';

	for (i = 0; text[i] != '\0'; i++) {
		if (text[i+1] != '\0' && text[i] == '\n' && text[i+1] == '\n') {
			for (j = 0; j < 26; j++) {
				yesses[j] = 0;
			}
		}

		if (text[i] > 96 && yesses[text[i] - 97] == 0) {
			sum++;
			yesses[text[i] - 97] = 1;
		}
	}

	printf("Sum of group yesses: %d\n", sum);
	
	free(text);
	fclose(fp);

	return 0;
}
