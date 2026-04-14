#include <stdio.h>
#include <stdbool.h>

char paraMinusculo(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

bool ehVogalRecursivo(char *s, int i) {
    bool resp;
    char c = paraMinusculo(s[i]);

    if (s[i] == '\0' || s[i] == '\n') {
        resp = true;
    } else if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
        resp = false;
    } else {
        resp = ehVogalRecursivo(s, i + 1);
    }
    return resp;
}

bool ehVogal(char *s) {
    return ehVogalRecursivo(s, 0);
}

bool ehConsoanteRecursivo(char *s, int i) {
    bool resp;
    char c = paraMinusculo(s[i]);

    if (s[i] == '\0' || s[i] == '\n') {
        resp = true;
    } else if (!(c >= 'a' && c <= 'z') || (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) {
        resp = false;
    } else {
        resp = ehConsoanteRecursivo(s, i + 1);
    }
    return resp;
}

bool ehConsoante(char *s) {
    return ehConsoanteRecursivo(s, 0);
}

bool ehIntRecursivo(char *s, int i) {
    bool resp;
    if (s[i] == '\0' || s[i] == '\n') {
        resp = true;
    } else if (s[i] < '0' || s[i] > '9') {
        resp = false;
    } else {
        resp = ehIntRecursivo(s, i + 1);
    }
    return resp;
}

bool ehInt(char *s) {
    return ehIntRecursivo(s, 0);
}

bool ehFloatRecursivo(char *s, int i, int qtdponto) {
    bool resp;
    if (s[i] == '\0' || s[i] == '\n') {
        resp = (qtdponto <= 1); 
    } else if ((s[i] < '0' || s[i] > '9') && s[i] != '.' && s[i] != ',') {
        resp = false;
    } else {
        if (s[i] == '.' || s[i] == ',') qtdponto++;
        resp = ehFloatRecursivo(s, i + 1, qtdponto);
    }
    return resp;
}

bool ehFloat(char *s) {
    return ehFloatRecursivo(s, 0, 0);
}

bool ehFim(char *s) {
    return (s[0] == 'F' && s[1] == 'I' && s[2] == 'M');
}

int main() {
    char s[500];

    while (fgets(s, 500, stdin) && !ehFim(s)) {
        printf("%s ", ehVogal(s) ? "SIM" : "NAO");
        printf("%s ", ehConsoante(s) ? "SIM" : "NAO");
        printf("%s ", ehInt(s) ? "SIM" : "NAO");
        printf("%s\n", ehFloat(s) ? "SIM" : "NAO");
    }

    return 0;
}