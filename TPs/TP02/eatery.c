#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int ano;
    int mes;
    int dia;
} Data;

Data parse_data(char* s){
    Data d;

    sscanf(s, "%d-%d-%d", &d.ano, &d.mes, &d.dia);

    return d;
}

void formatar_data(Data* d, char* buffer){
    sprintf(buffer, "%02d/%02d/%04d", d->dia, d->mes, d->ano);
}

typedef struct {
    int hora;
    int minuto;
} Hora;

Hora parse_hora(char* s){
    Hora h;

    sscanf(s, "%d:%d", &h.hora, &h.minuto);

    return h;
}

void formatar_hora(Hora* h, char* buffer){
    sprintf(buffer, "%02d:%02d", h->hora, h->minuto);
}

typedef struct {
    int id;
    char* nome;
    char* cidade;
    int capacidade;
    double avaliacao;
    int n_tipos_cozinha;
    char** tipos_cozinha;
    int faixa_preco;
    Hora horario_abertura;
    Hora horario_fechamento;
    Data data_abertura;
    bool aberto;

} Restaurante;

Restaurante* parse_restaurante(char* s){
    
    Restaurante* r = (Restaurante*) malloc(sizeof(Restaurante));
    char parte[300];
    int p_parte = 0;

    int coluna = 0;

    for (int i = 0;  s[i] != '\0'; i++){

        if (s[i] == ','){
            parte[p_parte] = '\0';

            if (coluna == 0) { //id
                sscanf(parte, "%d", &r->id);
            } else if (coluna == 1){ //nome
                int tam = 0;
                while (parte[tam] != '\0') tam++;

                r->nome = (char*) malloc((tam+1) * sizeof(char));
                strcpy(r->nome, parte);
            } else if (coluna == 2){ //cidade
                int tam = 0;
                while (parte[tam] != '\0') tam++;
                
                r->cidade = (char*) malloc((tam+1) * sizeof(char));
                strcpy(r->cidade, parte);
            } else if (coluna == 3){ //capacidade
                sscanf(parte, "%d", &r->capacidade);
            } else if (coluna == 4){ //avaliacao
                sscanf(parte, "%lf", &r->avaliacao);
            } else if (coluna == 5){ //tipos_cozinha
                //conta qtd de palavras pra criar vetor
                int qtd = 1;
                for (int i = 0; parte[i] != '\0'; i++){
                    if (parte[i] == ';') qtd++;
                }

                r->n_tipos_cozinha = qtd;

                //alloca vetor de char(string) de vetor de char (string) com o tamanho de cozinha
                char** cozinha = (char**) malloc(qtd * sizeof(char*));

                //varre e guarda letras com vetor temporário


                char tmp[500];
                int pos_tmp = 0;
                int tipo_atual = 0;

                for (int j = 0; parte[j] != '\0'; j++){
                    char letra = parte[j];

                    if (letra == ';'){
                        tmp[pos_tmp] = '\0';

                        cozinha[tipo_atual] = (char*) malloc((pos_tmp + 1) * sizeof(char));
                        
                        for (int k = 0; k <= pos_tmp; k++){
                            cozinha[tipo_atual][k] = tmp[k];
                        }

                        tipo_atual++;
                        pos_tmp = 0;
                    } else {
                        tmp[pos_tmp] = letra;
                        pos_tmp++;
                    }
                }

                tmp[pos_tmp] = '\0';
                cozinha[tipo_atual] = (char*) malloc((pos_tmp+1) * sizeof(char));
            
                for (int j = 0; j <= pos_tmp; j++){
                    cozinha[tipo_atual][j] = tmp[j];
                }

                r->tipos_cozinha = cozinha;

            } else if (coluna == 6){ //faixa_preco
                int preco = 0;
                for (int i = 0; parte[i] != '\0'; i++) preco++;

                r->faixa_preco = preco;
            } else if (coluna == 7){ //horario
            char tmp_ab[6];
            char tmp_fe[6];
            int j = 0;
            
            while (parte[j] != '-'){
                tmp_ab[j] = parte[j];
                j++;
            }
            tmp_ab[j] = '\0';
            
            j++;
            
            int k = 0;
            while (parte[j] != '\0'){
                tmp_fe[k] = parte[j];
                j++;
                k++;
            }
            tmp_fe[k] = '\0';
            
            r->horario_abertura = parse_hora(tmp_ab);
            r->horario_fechamento = parse_hora(tmp_fe);
            } else if (coluna == 8){ //data_abertura
                r->data_abertura = parse_data(parte);    
            }
            coluna++;
            p_parte = 0;
        } else {
            if (s[i] != '\n' && s[i] != '\r') {
                parte[p_parte] = s[i];
                p_parte++;
            }
        }
    }
    //aberto 
    parte[p_parte] = '\0';
    r->aberto = (strcmp(parte, "true") == 0) ? true : false;

    return r;
}

void formatar_restaurante(Restaurante* r, char* buffer){

    //formatando tipos de cozinha
    char tmp[50];
    int pos_tmp = 0;
    for(int i = 0; i < r->n_tipos_cozinha; i++){
        for(int j = 0; r->tipos_cozinha[i][j] != '\0'; j++){
            tmp[pos_tmp] = r->tipos_cozinha[i][j];
            pos_tmp++;
        }
        if((i + 1) < r->n_tipos_cozinha){
            tmp[pos_tmp] = ',';
            pos_tmp++;
        } else {
            tmp[pos_tmp] = '\0';
        }
    }
    int cont = 0;
    for(int i = 0; tmp[i] != '\0'; i++) cont++;

    char cozinhas_formatada[cont + 1];
    for(int i = 0; i < cont; i++){
        cozinhas_formatada[i] = tmp[i];
    }
    cozinhas_formatada[cont] = '\0';
    
    //formatando faixa para '$'
    int tam = r->faixa_preco;
    char faixa_formatada[tam + 1];
    for(int i = 0; i < tam; i++){
        faixa_formatada[i] = '$';
    }
    faixa_formatada[tam] = '\0';

    char abertura_formatado[6];
    char fechamento_formatado[6];
    char data_formatada[11];

    formatar_hora(&r->horario_abertura, abertura_formatado);
    formatar_hora(&r->horario_fechamento, fechamento_formatado);
    formatar_data(&r->data_abertura, data_formatada);


    sprintf(buffer, "[%d ## %s ## %s ## %d ## %.1lf ## [%s] ## %s ## %s-%s ## %s ## %s]",
            r->id,
            r->nome,
            r->cidade,
            r->capacidade,
            r->avaliacao,
            cozinhas_formatada,
            faixa_formatada,
            abertura_formatado,
            fechamento_formatado,
            data_formatada,
            r->aberto ? "true" : "false"
    );
}

typedef struct{
    int tamanho;
    Restaurante** restaurantes;
} Colecao_Restaurantes;

void ler_csv_colecao(Colecao_Restaurantes* colecao, char* path) {
    FILE* arquivo = fopen(path, "r");
    
    if (arquivo != NULL) {
        char linha[1000];

        fgets(linha, 1000, arquivo);

        while (fgets(linha, 1000, arquivo) != NULL) {
            
            Restaurante* r = parse_restaurante(linha);

            colecao->restaurantes[colecao->tamanho] = r;
            colecao->tamanho++;
        }
        
        fclose(arquivo);
    }
}

Colecao_Restaurantes* ler_csv() {
    Colecao_Restaurantes* colecao = (Colecao_Restaurantes*) malloc(sizeof(Colecao_Restaurantes));
    colecao->tamanho = 0;
    
    colecao->restaurantes = (Restaurante**) malloc(1000 * sizeof(Restaurante*));

    ler_csv_colecao(colecao, "/tmp/restaurantes.csv");

    return colecao;
}

int main() {
    Colecao_Restaurantes* colecao = ler_csv();

    char linha[20];
    bool ler_entrada = true;

    while (ler_entrada && scanf(" %s", linha) == 1) {
        
        if (strcmp(linha, "-1") == 0) {
            ler_entrada = false;
        } else {
            int id_procurado = 0;
            for(int i = 0; linha[i] != '\0'; i++) {
                if(linha[i] >= '0' && linha[i] <= '9') {
                    id_procurado = (id_procurado * 10) + (linha[i] - '0');
                }
            }

            bool achou = false;
            int indice = 0;

            while (!achou && indice < colecao->tamanho) {
                if (colecao->restaurantes[indice]->id == id_procurado) {
                    
                    char buffer_saida[2000];
                    formatar_restaurante(colecao->restaurantes[indice], buffer_saida);
                    printf("%s\n", buffer_saida);
                    
                    achou = true;
                }
                indice++;
            }
        }
    }

    return 0;
}