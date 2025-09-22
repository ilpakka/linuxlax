#include <stdio.h>
#include <string.h>

int main()
{
    const char rsi[] = "lAmBdA";
    char rdx[] = {2, 3, 2, 3, 5, 0};
    char salasana[sizeof(rsi)];
    int i;

    for (i = 0; i < strlen(rsi); i++) {
        salasana[i] = rsi[i] + rdx[i];
    }

    printf(salasana);
    return 0;
}
