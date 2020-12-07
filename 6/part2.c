/* input file MUST have one blank line at the end
   I know I know but it works
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	char *text = (char*)malloc(1);
	int i = 0, j = 0, k;
	long yesses[100] = {0};
	long subSum = 0;
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
			subSum = 2147483647;

			/* find only digits that are ALL 1/yes */
			for (k = 0; k <= j; k++) {
				subSum &= yesses[k];
				printf("%ld\n", yesses[k]);
			}

			printf("subSum=%ld\n", subSum);
			
			/* find the number of 1s/yesses in that number */
			for (k = 0; k < 26; k++) {
				if ((subSum & (1<<k)) > 0) {
					sum++;
				}
			}

			/* erase list to start over with new group */
			for (j = 0; j < 100; j++) {
				yesses[j] = 0;
			}

			j = -1;
			printf("\n\n");

		} else if (text[i] == '\n') { /* new line in same group */
			j++;
		}

		if (text[i] > 96) {
			yesses[j] = yesses[j] | 1<<(text[i]-97);
		}
	}

	printf("Sum of group yesses: %d\n", sum);
	
	free(text);
	fclose(fp);

	return 0;
}
