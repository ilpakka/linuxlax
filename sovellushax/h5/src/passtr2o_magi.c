#include <stdio.h>
#include <string.h>

int main()
{
    const char vanha[] = "anLTj4u8";
    char salasana[sizeof(vanha)];
    int c;

    for (int i = 0; i < strlen(vanha); i++) {
        c = (char)vanha[i];
        
        if (i % 2 == 0) {
            c = c + 3;
        }
        else {
            c = c - 7;
        }
        
        salasana[i] = (char)c;
    }
    
    puts(salasana);
    return 0;
}
