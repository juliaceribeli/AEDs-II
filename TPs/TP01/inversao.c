#include <stdio.h>

int contador (char* s){
	int cont = 0;
	while(s[cont] != '\0'){
		cont++;
	}
	
	if (cont > 0 && s[cont-1] == '\n'){
		cont--;
	}

	return cont;
}


void inversor(char* s){
	int tam = contador(s);
	char invertida [tam + 1];
	int pos = 0;

	for(int i = tam - 1; i >= 0; i--){
		invertida[pos] = s[i];
		pos++;	
	} 
	invertida[pos] = '\0';

	printf("%s\n", invertida);
}

int main() {
	char frase [50];

	fgets(frase, 50, stdin);

	while (!(frase[0] == 'F' && frase[1] == 'I' && frase[2] == 'M')){
		inversor(frase);
	
		fgets(frase, 50, stdin);
	}

	return 0;
}
