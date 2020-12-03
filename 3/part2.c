#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int i = 0, j = 0;
	int horzInc = atoi(argv[2]);
	int vertInc = atoi(argv[3]);
	int trees = 0;
	char line[32];
	FILE *fp = fopen(argv[1], "r");

	while (fscanf(fp, "%s", line) == 1) {
		printf("%s\n", line);
		
		if (j % vertInc == 0) {
			if (line[i % 31] == '#')
				trees++;

			i += horzInc;
		}

		j++;
	}

	printf("trees: %d\n", trees);

	fclose(fp);

	return 0;
}
