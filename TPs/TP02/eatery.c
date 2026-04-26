#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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

void ordenar_por_selecao(Restaurante** array, int n, int* comparacoes, int* movimentacoes) {
    for (int i = 0; i < n - 1; i++) {
        int indice_menor = i;
        
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            
            if (strcmp(array[j]->nome, array[indice_menor]->nome) < 0) {
                indice_menor = j;
            }
        }
        
        if (indice_menor != i) {
            Restaurante* temp = array[i];
            array[i] = array[indice_menor];
            array[indice_menor] = temp;
            
            (*movimentacoes) += 3; 
        }
    }
}

bool pesquisa_binaria(Restaurante** array, int n, char* nome_buscado, int* comparacoes) {
    bool achou = false;
    int esq = 0;
    int dir = n - 1;

    while(esq <= dir && !achou){
        int meio = (esq + dir) / 2;
        
        (*comparacoes)++;
        int comp = strcmp(nome_buscado, array[meio]->nome);

        if(comp == 0){
            achou = true;
        } else if(comp > 0){
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    return achou;
}

bool vem_antes(Restaurante* r1, Restaurante* r2, int* comparacoes) {
    (*comparacoes)++;
    if (r1->avaliacao < r2->avaliacao){
        return true;
    } else if (r1->avaliacao > r2->avaliacao){
        return false;
    } else {
        (*comparacoes)++;
        return strcmp(r1->nome, r2->nome) < 0;
    }
}

bool vem_depois(Restaurante* r1, Restaurante* r2, int* comparacoes){
    (*comparacoes)++;
    if (r1->avaliacao > r2->avaliacao){
        return true;
    } else if(r1->avaliacao < r2->avaliacao) {
        return false;
    } else {
        (*comparacoes)++;
        return strcmp(r1->nome, r2->nome) > 0;
    }
}

void quicksort(Restaurante** array, int esq, int dir, int* comparacoes, int* movimentacoes){
    int i = esq;
    int j = dir;
    
    Restaurante* pivo = array[(esq + dir) / 2];

    while (i <= j) {
        while (vem_antes(array[i], pivo, comparacoes)){
            i++;
        }
        while (vem_depois(array[j], pivo, comparacoes)){
            j--;
        }

        if (i <= j) {
            Restaurante* temp = array[i];
            array[i] = array[j];
            array[j] = temp;       
            (*movimentacoes) += 3;
            i++;
            j--;
        }
    }

    if (esq < j){
        quicksort(array, esq, j, comparacoes, movimentacoes);
    }
    if (i < dir){
        quicksort(array, i, dir, comparacoes, movimentacoes);
    }
}

int get_maior_capacidade(Restaurante** array, int n, int* comparacoes){
    int maior = array[0]->capacidade;
    for (int i = 1; i < n; i++){
        (*comparacoes)++;
        if (array[i]->capacidade > maior){
            maior = array[i]->capacidade;
        }
    }
    return maior;
}

void countingsort(Restaurante** array, int n, int* comparacoes, int* movimentacoes) {
    int maior = get_maior_capacidade(array, n, comparacoes);

    int* count = (int*) calloc((maior + 1), sizeof(int));
    Restaurante** ordenado = (Restaurante**) malloc(n * sizeof(Restaurante*));

    for (int i = 0; i < n; i++){
        count[array[i]->capacidade]++;
    }

    for (int i = 1; i <= maior; i++){
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--){
        int cap = array[i]->capacidade;
        int posicao = count[cap] - 1;
        
        ordenado[posicao] = array[i];
        count[cap]--;
        (*movimentacoes)++;
    }

    for (int i = 0; i < n; i++){
        array[i] = ordenado[i];
        (*movimentacoes)++;
    }

    free(count);
    free(ordenado);
}

typedef struct {
    Restaurante* array[1000];
    int n;
} Pilha;

void iniciar_pilha(Pilha* p){
    p->n = 0;
}

void empilhar(Pilha* p, Restaurante* r){
    p->array[p->n] = r;
    p->n++;
}

Restaurante* desempilhar(Pilha* p){
    if (p->n > 0){
        p->n--;
        return p->array[p->n];
    }
    return NULL;
}

void mostrar_pilha(Pilha* p){
    for (int i = p->n - 1; i >= 0; i--){
        char buffer_saida[2000];
        formatar_restaurante(p->array[i], buffer_saida);
        printf("%s\n", buffer_saida);
    }
    
}

int main() {
    Colecao_Restaurantes* colecao = ler_csv();

    Pilha pilha;
    iniciar_pilha(&pilha);

    char linha[200];
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
            while (!achou && indice < colecao->tamanho){
                if (colecao->restaurantes[indice]->id == id_procurado){
                    empilhar(&pilha, colecao->restaurantes[indice]);
                    achou = true;
                }
                indice++;
            }
        }
    }

    int num_comandos = 0;
    if (scanf(" %d", &num_comandos) == 1) {
        
        for (int k = 0; k < num_comandos; k++) {
            char comando[50];
            scanf(" %s", comando);

            if (strcmp(comando, "I") == 0) {
                int id_inserir;
                scanf(" %d", &id_inserir);

                bool achou = false;
                int indice = 0;
                while (!achou && indice < colecao->tamanho) {
                    if (colecao->restaurantes[indice]->id == id_inserir) {
                        empilhar(&pilha, colecao->restaurantes[indice]);
                        achou = true;
                    }
                    indice++;
                }

            } else if (strcmp(comando, "R") == 0) {
                Restaurante* removido = desempilhar(&pilha);
                
                if (removido != NULL) {
                    printf("(R)%s\n", removido->nome);
                }
            }
        }
    }

    mostrar_pilha(&pilha);

    return 0;
}