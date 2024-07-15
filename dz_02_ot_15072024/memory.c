#include <stdio.h>
#include <stdlib.h>

int main()
{
	const size_t bufsz = 100;
	char *buf = malloc(bufsz);
	int ndigits = 0;

	if (!fgets(buf, bufsz, stdin))
		return 1;
	for (char *p = buf; *p; p++) {
		if (*p >= '0' && *p <= '9')
		    ndigits++;
	}
	printf("Found %d digits\n", ndigits);
	return 0;
}
