#include <stdio.h>
#include <stdbool.h>

bool ehFim(char * string){
    return string[0] == 'F' && string[1] == 'I' && string[2] == 'M'; 
}

int contador(char * string){
    int cont = 0;
    for (int i = 0; string[i] != '\0' && string[i] != '\n'; i++){
        cont++;
    }

    return cont;
}

int substring(char * s){
    int maior = 0;
    int inicio = 0;
    int tam = contador(s);

    for (int i = 0; i < tam; i++){
        for (int j = inicio; j < i; j++){

            if (s[i] == s[j]){          
                inicio = j + 1;
                j = i;
            } 
        }

        int tamanho = i - inicio + 1;
    
        if (tamanho > maior){
            maior = tamanho;
        }
    }

    return maior;
}


int main(){
    char string [50];
    fgets(string, 50, stdin);

    while (!ehFim(string)){
        int maior = substring(string);

        printf("%d\n", maior);

        fgets(string, 50, stdin);
    }
    
    return 0;
}
