
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CHAR ' '
#define STOP_CHAR '~'

char riddle[4096];
unsigned long attempts;

int check(const char *pass) {
	attempts++;
	return !strcmp(pass, riddle);
}

int bruteforce(char *s, unsigned n);

int main(void) {
	char *buf;
	unsigned n = 0;
	if (!fgets(riddle, sizeof riddle, stdin))
		return -1;
	if (scanf("%u", &n) == 1) {
		unsigned l = strlen(riddle);
		if (l > 0)
			if (riddle[l-1] == '\n') {
				riddle[l-1] =  '\0';
				n--;
			}
	} else {
		n = strlen(riddle);
		if (n > 0)
			if (riddle[n-1] == '\n') {
				riddle[n-1] =  '\0';
				n--;
			}
	}
	buf = (char *) malloc(n + 1);
	attempts = 0;
    if (bruteforce(buf, n + 1)) {
		puts(buf);
    } else {
		printf("%lu\n", attempts);
    }
	free(buf);
	return 0;
}

int bruteforce(char *buf, unsigned n) {
    unsigned a = 0, j;
    while (a < n) {
        buf[a] = '\0';
        a++;
    }
    if (n == 1) {
        if (check(buf)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    a = 0;
    if (!check(buf)) {
        buf[0] = START_CHAR;
        while (a < n - 1 && !check(buf)) {
            buf[0]++;
            for (j = 0; j < a && buf[j] == STOP_CHAR + 1; j++) {
                buf[j + 1]++;
                buf[j] = START_CHAR;
            }
            if (buf[a] == STOP_CHAR + 1) {
                buf[a] = START_CHAR;
                a++;
                if (a < n - 1) {
                    buf[a] = START_CHAR;
                }
            }
        }
    }
    if (a < n - 1) {
        return 1;
    } else {
        return 0;
    }
}
