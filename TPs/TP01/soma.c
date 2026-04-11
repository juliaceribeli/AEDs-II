#include <stdio.h>

int somadorRec(int n, int soma){
    if (n / 10 != 0 ){
        soma += (n % 10) + somadorRec(n/10, soma);
    } else {
    	soma += (n % 10);
    }	

    return soma;
}

int somador (int n) {
    return somadorRec(n, 0);
}

int main(){
    int numero;
	
    while(scanf("%d", &numero) != EOF){
    	int soma = somador(numero);
    	printf("%d\n", soma);
    }	

    return 0;
}
