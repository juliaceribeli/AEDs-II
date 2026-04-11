#include <stdio.h>
#include <stdbool.h>

bool ehFim (char* s){
    return(s[0] == 'F' && s[1] == 'I' && s[2] == 'M');
}

int contador(char* s){
    int cont = 0;
    for (int i = 0; s[i] != '\0' && s[i] != '\n'; i++){
        cont++;
    }

    return cont;
}

void separador (char* linha, char* s1, char* s2){
    int i = 0, j = 0;

    while(linha[i] != ' ' && linha[i] != '-' && linha[i] != '\0' ){
        if (linha[i]>= 'A' && linha[i] <= 'Z'){
            linha[i] += 32;
        }
        
        s1[i] = linha[i];
        i++;
    }
    s1[i] = '\0';
    
    while(linha[i] == ' ' || linha[i] == '-' || linha[i] == '\n'){
        i++;
    }
    
    while (linha[i] != '\0' && linha[i] != '\n'){
        if (linha[i]>= 'A' && linha[i] <= 'Z'){
            linha[i] += 32;
        }        
        s2[j] = linha[i];
        j++; i++;
    }
    s2[j] = '\0';
}

bool ehAnagrama (char* s1, char* s2){
    int tam1 = contador(s1);
    int tam2 = contador(s2);
    bool anagrama = true;

    if (tam1 != tam2){
        anagrama = false;
    } else {
        char copiaS2[50];
        
        for (int k = 0; k < tam2; k++) copiaS2[k] = s2[k]; 

        for (int i = 0; i < tam1; i++){
            bool achei = false;

            for (int j = 0; j < tam2; j++){
                if(s1[i] == copiaS2[j]){
                    achei = true;

                    copiaS2[j] = '*';
                    j = tam2;
                }
            }

            if (achei == false) anagrama = false;
        }
    }
    
    return anagrama;
}

int main(){

    char linha [50];
    fgets(linha, 50, stdin);
    
    while (!ehFim(linha)){       
        
        char s1 [50], s2 [50];
        
        separador(linha, s1, s2);
        
        if(ehAnagrama(s1, s2)){
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }

        fgets(linha, 50, stdin);
    }
    
    return 0;
}