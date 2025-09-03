// passtr - a simple static analysis warm up exercise
// Copyright 2024 Tero Karvinen https://TeroKarvinen.com

#include <stdio.h>
#include <string.h>

void definitely_not_rot13(char *s) {
	for (int i = 0; s[i] != '\0'; i++) {
	if ((s[i] >= 'A' && s[i] <= 'Z')) {
            s[i] = ((s[i] - 'A' + 13) % 26) + 'A';
        } else if ((s[i] >= 'a' && s[i] <= 'z')) {
            s[i] = ((s[i] - 'a' + 13) % 26) + 'a';
        }
    }
}

int main() {
	char password[20];
	
	char funny_password[] = "fnyn-unxxrev-321";
    	char funny_flag[] = "SYNT{Greb-q75rr66ns0n68663s15539rp0s46r3o1}";
    	
    	definitely_not_rot13(funny_password);
    	definitely_not_rot13(funny_flag);
	
	printf("Gib password please.\n");
	scanf("%19s", password);
	if (0 == strcmp(password, funny_password)) {
		printf("Hey good for you! %s\n", funny_flag);
	} else {
		printf("Yeah that's gonna be a no from me dawg.\n");
	}
	return 0;
}
