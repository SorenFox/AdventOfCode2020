#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int i = 0;
	int trees = 0;
	char line[32];
	FILE *fp = fopen(argv[1], "r");

	while (fscanf(fp, "%s", line) == 1) {
		printf("%s\n", line);
		
		if (line[i % 31] == '#')
			trees++;

		i += 3;
	}

	printf("trees: %d\n", trees);

	fclose(fp);

	return 0;
}
