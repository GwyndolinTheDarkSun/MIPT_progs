#include <stdio.h>

int isLatin(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return 1;
	return 0;
}

//6) Text doesn't contain any characters except digits and Latin characters
int check(const char *s) {
	int i;
	for (i = 0; s[i]; i++)
		if (!((s[i] >= '0' && s[i] <= '9') || isLatin(s[i])))
			return 0;
	return 1;
}

//2) Replace each digit (except 0) with corresponding lower-case Latin character (1 -> a, 2 -> b, ..., 9 -> i)
void rule1(char *s) {
	int i;
	for (i = 0; s[i]; i++)
		if (s[i] >= '1' && s[i] <= '9')
			s[i] = 'a' + s[i] - '1';
}

//5) Leave only that characters, that appears only once
void rule2(char *s) {
	int i, j, A[256];
	for (i = 0; i < 256; i++)
		A[i] = 0;
	for (i = 0; s[i]; i++)
		A[(int)s[i]]++;
	for (i = j = 0; s[j]; i++, j++) {
		if (A[(int)s[j]] > 1)
			i--;
		else
			s[i] = s[j];
	}
	s[i] = '\0';
}

const char *test(int i) {
	switch (i) {
		case 1:
			return "Qwe123RTY";
		case 2:
			return "QWE011rty";
		case 3:
			return "ABqwe911-0YZ";
		default:
			return "";
	}
}

int main(void) {
	char s[102];
	int n;
	fgets(s, sizeof s, stdin);
	for (n = 0; s[n]; n++); //n = strlen(s);
	while (n > 0 && (s[n-1] == '\r' || s[n-1] == '\n'))
		s[--n] = '\0';
	puts(s);
	if (check(s))
		rule1(s);
	else
		rule2(s);
	puts(s);
	return 0;
}
