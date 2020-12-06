#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int byr;
	int iyr;
	int eyr;
	int hgt;
	char pid[101];
	int cid;
	char hcl[101];
	char ecl[101];
} Passport;

void substr(char *input, int i, char *output) {
	int j;

	for (j = i; input[j] != ' ' && input[j] != EOF; j++) {
		output[j-i] = input[j];
	}

	output[j-i+1] = '\0';
}

int main(int argc, char **argv) {
	Passport *passes = (Passport*)malloc(sizeof(Passport));
	FILE *fp = fopen(argv[1], "r");
	char *ch = (char*)malloc(1);
	char sub[101] = {0};
	int i = 0, j = 0, valids = 0;

	passes[0].byr = -1;
	passes[0].iyr = -1;
	passes[0].eyr = -1;
	passes[0].hgt = -1;
	passes[0].hcl[0] = '\0';
	passes[0].ecl[0] = '\0';
	passes[0].pid[0] = '\0';
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
			sscanf(sub, "%d", &(passes[j].hgt));
			
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
			passes[j].hcl[0] = '\0';
			passes[j].ecl[0] = '\0';
			passes[j].pid[0] = '\0';
			passes[j].cid = -1;
		}
	}

	for (i = 0; i <= j; i++) {
		if (!(passes[i].byr == -1 || passes[i].iyr == -1 || passes[i].eyr == -1
			|| passes[i].hgt == -1 || passes[i].hcl[0] == '\0'
			|| passes[i].ecl[0] == '\0' || passes[i].pid[0] == '\0')) {
			valids++;
			printf("%s\n", passes[i].pid);
		} else {
			if (passes[i].byr == -1)
				printf("byr ");
			if (passes[i].iyr == -1)
				printf("iyr ");
			if (passes[i].eyr == -1)
				printf("eyr ");
			if (passes[i].hgt == -1)
				printf("hgt ");
			if (passes[i].hcl[0] == '\0')
				printf("hcl ");
			if (passes[i].ecl[0] == '\0')
				printf("ecl ");
			if (passes[i].pid[0] == '\0')
				printf("pid ");
			printf("\n");
		}
	}

	printf("Passports: %d\n", j+1);
	printf("Valid passports: %d\n", valids);

	free(ch);
	free(passes);
	fclose(fp);
	return 0;
}
