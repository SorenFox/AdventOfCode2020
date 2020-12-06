#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int byr;
	int iyr;
	int eyr;
	int hgt;
	char hgtCh;
	char pid[101];
	int cid;
	char hcl[101];
	char ecl[101];
} Passport;

void substr(char *input, int i, char *output) {
	int j;

	for (j = 0; j < 101; j++) {
		output[j] = '\0';
	}

	for (j = i; input[j] != ' ' && input[j] != EOF; j++) {
		output[j-i] = input[j];
	}

	output[j-i+1] = '\0';
}

int validHcl(char *input) {
	int result = 1;
	int i;

	if (input[0] != '#') {
		result = 0;
	}
	for (i = 1; input[i] != '\0'; i++) {
		if (!((input[i] < 58 && input[i] > 47) ||
			(input[i] < 103 && input[i] > 96))) {
			result = 0;
		}
	}
	if (i != 7)
		result = 0;

	return result;
}

int validPid(char *pid) {
	int result = 1;
	int i;

	for (i = 0; i < 9; i++) {
		if (pid[i] > 57 || pid[i] < 48)
			result = 0;
	}

	if (pid[9] != '\0')
		result = 0;

	return result;
}

int checkStr(char *in1, char *in2) {
	int result = 1;
	int i = -1;

	do {
		i++;
		if (in1[i] != in2[i])
			result = 0;
	} while (in1[i] != '\0' && in2[i] != '\0');

	return result;
}

int main(int argc, char **argv) {
	Passport *passes = (Passport*)malloc(sizeof(Passport));
	FILE *fp = fopen(argv[1], "r");
	char *ch = (char*)malloc(1);
	char sub[101] = {0};
	int i = 0, j = 0, valids = 0, valid;

	passes[0].byr = -1;
	passes[0].iyr = -1;
	passes[0].eyr = -1;
	passes[0].hgt = -1;
	passes[0].hgtCh = '\0';
	for (int k = 0; k < 101; k++) {
		passes[0].hcl[k] = '\0';
		passes[0].ecl[k] = '\0';
		passes[0].pid[k] = '\0';
	}
	passes[0].cid = -1;
	
	ch[0] = fgetc(fp);

	while (ch[i] != EOF) {
		i++;
		ch = (char*)realloc(ch, i+1);
		ch[i] = fgetc(fp);
	}

	i++;
	ch = (char*)realloc(ch, i+1);
	ch[i] = '\0';
	
	for (i = 4; ch[i] != EOF; i++) {
		if (ch[i-4] == 'b' && ch[i-3] == 'y') {
			substr(ch, i, sub);
			sscanf(sub, "%d", &(passes[j].byr));
		}
		if (ch[i-4] == 'i' && ch[i-3] == 'y') {
			substr(ch, i, sub);
			sscanf(sub, "%d", &(passes[j].iyr));
		}
		if (ch[i-4] == 'e' && ch[i-3] == 'y') {
			substr(ch, i, sub);
			sscanf(sub, "%d", &(passes[j].eyr));
		}
		if (ch[i-4] == 'h' && ch[i-3] == 'g') {
			substr(ch, i, sub);
			sscanf(sub, "%d%c", &(passes[j].hgt), &(passes[j].hgtCh));
		}
		if (ch[i-4] == 'h' && ch[i-3] == 'c') {
			substr(ch, i, sub);
			sscanf(sub, "%s", (passes[j].hcl));
		}
		if (ch[i-4] == 'e' && ch[i-3] == 'c') {
			substr(ch, i, sub);
			sscanf(sub, "%s", (passes[j].ecl));
		}
		if (ch[i-4] == 'p' && ch[i-3] == 'i') {
			substr(ch, i, sub);
			sscanf(sub, "%s", (passes[j].pid));
		}
		if (ch[i-4] == 'c' && ch[i-3] == 'i') {
			substr(ch, i, sub);
			sscanf(sub, "%d", &(passes[j].cid));
		}
		if (ch[i] == '\n' && ch[i+1] == '\n') {
			j++;
			passes = (Passport*)realloc(passes, (j+1)*sizeof(Passport));
			passes[j].byr = -1;
			passes[j].iyr = -1;
			passes[j].eyr = -1;
			passes[j].hgt = -1;
			passes[j].hgtCh = '\0';

			for (int k = 0; k < 101; k++) {
				passes[j].hcl[k] = '\0';
				passes[j].ecl[k] = '\0';
				passes[j].pid[k] = '\0';
			}

			passes[j].cid = -1;
		}
	}

	for (i = 0; i <= j; i++) {
		valid = 1;
		if (!(passes[i].byr < 2003 && passes[i].byr > 1919)) {
			valid = 0;
			printf("byr ");
		}
		if (!(passes[i].iyr < 2021 && passes[i].iyr > 2009)) {
			valid = 0;
			printf("iyr ");
		}
		if (!(passes[i].eyr < 2031 && passes[i].eyr > 2019)) {
			valid = 0;
			printf("eyr ");
		}
		if (!(passes[i].hgtCh == 'c' && passes[i].hgt < 194 && passes[i].hgt > 149 ||
			 passes[i].hgtCh == 'i' && passes[i].hgt < 77 && passes[i].hgt > 58)) {
			valid = 0;
			printf("hgt ");
		}
		if (!(validHcl(passes[i].hcl))) {
			valid = 0;
			printf("hcl ");
		}
		if (!(validPid(passes[i].pid))) {
			valid = 0;
			printf("pid ");
		}
		if (!(checkStr(passes[i].ecl, "amb") || checkStr(passes[i].ecl, "grn") ||
			  checkStr(passes[i].ecl, "blu") || checkStr(passes[i].ecl, "brn") ||
			  checkStr(passes[i].ecl, "gry") || checkStr(passes[i].ecl, "hzl") ||
			  checkStr(passes[i].ecl, "oth"))) {
			valid = 0;
			printf("ecl ");
		}
		
		valids += valid;
		printf("\n");
	}

	printf("Passports: %d\n", j+1);
	printf("Valid passports: %d\n", valids);

	free(ch);
	free(passes);
	fclose(fp);
	return 0;
}
