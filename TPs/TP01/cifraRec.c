#include <stdio.h>
#include <stdbool.h>

bool isFim(char* s) {
    return (s[0] == 'F' && s[1] == 'I' && s[2] == 'M');
}

void cifrarRec(char* frase, int i) {
    if (frase[i] != '\0' && frase[i] != '\n') {
        char letraCifrada = (char)(frase[i] + 3);
        printf("%c", letraCifrada);
        
        cifrarRec(frase, i + 1);
    }
    
    if (frase[i] == '\n') printf("\n"); 
}

void cifrar(char* frase) {
    cifrarRec(frase, 0);
}

int main() {
    char frase[500];

    if (fgets(frase, 500, stdin) != NULL) {
        while (!isFim(frase)) {
            
            cifrar(frase);
            fgets(frase, 500, stdin);
        }
    }

    return 0;
}