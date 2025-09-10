#include <stdio.h>

int main()
{
    int merkki;

    while ((merkki = getchar()) != EOF) {
        if (merkki != '\n') merkki = (unsigned char)merkki - 2;
        putchar(merkki);
    }

    return 0;
}
