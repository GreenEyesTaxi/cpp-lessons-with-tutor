#include <stdio.h>
#include <stdlib.h>

int main()
{
	const size_t bufsz = 100;
	char *buf = malloc(bufsz);
	int ndigits = 0;

    const char marks[] = {'.', ',', ':', ';', '?', '!', '(', ')', '[', ']'};
    int nmarks = 0;

	if (!fgets(buf, bufsz, stdin))
		return 1;

	for (char *p = buf; *p; p++) {//видимо, все еще не до конца понимаю эту строчку
		if (*p >= '0' && *p <= '9') {
			ndigits++;
		}
		    
		else { // я не понимаю, как сюда подтянуть правильно те самые ASCII
            for (int i = 0; i < sizeof(marks); i++) {
                if (*p == marks[i]){
                    nmarks++;  
                }
            }
        }
	}
	printf("Found %d digits", ndigits);
    printf(" and %d punctuation marks\n", nmarks);//не работает, но комплится 
	return 0;
}
