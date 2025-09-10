#include <stdio.h>

int main()
{
    int merkki;

    while ((merkki = getchar()) != EOF) {
        if (merkki != '\n') merkki = (unsigned char)merkki - 1;
        putchar(merkki);
    }

    return 0;
}
