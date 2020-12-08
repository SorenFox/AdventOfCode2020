#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	char instruction[4];
	char inst[1000] = {'n'};
	int nums[1000] = {0};
	int done[1000] = {0};
	int i = 0, acc = 0;

	while (fscanf(fp, "%s %d", instruction, &(nums[i])) == 2) {
		printf("%c %d\n", instruction[0], nums[i]);
		inst[i] = instruction[0];
		i++;
	}

	i = 0;

	while (done[i] == 0) {
		done[i] = 1;
		
		switch (inst[i]) {
		  case 'a':
		  	acc += nums[i];
			i++;
			break;
		  case 'j':
		  	i += nums[i];
			break;
		  default:
		  	i++;
		}
	}

	printf("Accumulator: %d\n", acc);

	fclose(fp);

	return 0;
}
