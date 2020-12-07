#include <stdio.h>
#include <stdlib.h>

int decodeRow(char *input) {
	int result = 0;
	int i;

	for (i = 0; i < 7; i++) {
		result = result | ((input[i] == 'B')<<(6-i));
	}

	return result;
}

int decodeCol(char *input) {
	int result = 0;
	int i;

	for (i = 7; i < 10; i++) {
		result = result | ((input[i] == 'R')<<(9-i));
	}

	return result;
}

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	char ticket[11];
	int largest = 0, current;

	while (fscanf(fp, "%s", ticket) == 1) {
		current = decodeRow(ticket) * 8 + decodeCol(ticket);
		
		if (current > largest)
			largest = current;
	}

	printf("Largest seat ID: %d\n", largest);
	fclose(fp);

	return 0;
}
	
