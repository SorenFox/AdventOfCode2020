#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int size = 0, pos, pos2, result;
	int *nums = (int*)malloc(sizeof(int));
	FILE *fp = fopen(argv[1], "r");

	while (fscanf(fp, "%d", nums+size) == 1) {
		for (pos = 0; pos < size-1; pos++) {
			for (pos2 = pos + 1; pos2 < size-2; pos2++) {
				if (nums[pos] + nums[pos2] + nums[size] == 2020) {
					printf("%d + %d + %d = 2020\n", nums[pos], nums[pos2],
						   nums[size]);
					result = nums[pos] * nums[pos2] * nums[size];
				}
			}
		}

		size++;
		nums = (int*)realloc(nums, sizeof(int) * (size + 1));
	}

	printf("%d\n", result);
	free(nums);
	fclose(fp);

	return 0;
}
