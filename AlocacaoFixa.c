/* 
 * Instituição: UERGS
 * Curso: Engenharia de computação
 * Arquivo: AlocacaoFixa.c
 * Autor: Guilherme
 * E-mail: guilhermelaguebmx@gmail.com
 * Descrição: Implementação de um algoritmo para alocação fixa de memória.
 *            Foi utilizada lista circular duplamente encadeada.
 * Criado em: 5 de Junho de 2017, 19:54
 */

#include <stdio.h>
#include <stdlib.h>

//================================================================================
// int id: id do bloco de memória
// int tam_bloco: tamanho do bloco de memória
// int id_processo: id do processo contido no bloco
// struct bloco *ant: ponteiro para o bloco de memória anterior
// struct bloco *prox: ponteiro para o bloco de memória posterior
//================================================================================
typedef struct bloco{
    int id;
    int tam_bloco;
    int id_processo;
    struct bloco *ant;
    struct bloco *prox;
}bloco;

//================================================================================
// int id: id do processo 
// int tam_processo: tamanho do processo
// int id_bloco: id do bloco onde o processo esta contido
// struct processo *ant: ponteiro para o processo anterior
// struct processo *prox: ponteiro para o processo posterior
//================================================================================
typedef struct processo{
    int id;
    int tam_processo;
    int id_bloco;
    struct processo *ant;
    struct processo *prox;
}processo;

//ponteiros para os blocos de memória
bloco *novo_b = NULL, *inicio_b = NULL;
//ponteiros para os processos
processo *novo_p = NULL, *inicio_p = NULL;

//protótipo da função
void inserir_bloco(int id, int tam);

//================================================================================
// Esta função cria um arquivo chamado memoria.txt, simulando uma memória com blocos ja determinados
// FILE* file: Ponteiro para o arquivo
//================================================================================
void cria_arquivo(FILE* file){
    file = fopen("C:/Users/Guilherme Lague/Desktop/memoria.txt","w+t");
    
    fprintf(file,"%d %d\n", 1, 10);
    fprintf(file,"%d %d\n", 2, 4);
    fprintf(file,"%d %d\n", 3, 20);
    fprintf(file,"%d %d\n", 4, 18);
    fprintf(file,"%d %d\n", 5, 7);
    fprintf(file,"%d %d\n", 6, 9 );
    fprintf(file,"%d %d\n", 7, 12);
    fprintf(file,"%d %d", 8, 13);
    fclose(file);
}

//================================================================================
// Esta função le o arquivo criado chamado memoria.txt
// FILE* file: Ponteiro para o arquivo
//================================================================================
void le_arquivo(FILE* file){
    int id, tam;
    
    file = fopen("C:/Users/Guilherme Lague/Desktop/memoria.txt","rt");
    while(!feof(file)){
        fscanf(file, "%d %d", &id, &tam);
        inserir_bloco(id, tam);
    }
    fclose(file); 
}

//================================================================================
// Esta função insere blocos de memória na lista dupla
// int id: id do bloco de memória
// int tam: tamanho do bloco de memória
//================================================================================
void inserir_bloco(int id, int tam){
    novo_b = (bloco*)malloc(sizeof(bloco));
    
    novo_b->id = id;
    novo_b->tam_bloco = tam;
    
    if(inicio_b == NULL) {
        inicio_b = novo_b;
        novo_b->ant = novo_b;
        novo_b->prox = novo_b;
    }
    else{
        novo_b->prox = inicio_b;
        novo_b->ant = inicio_b->ant;
        inicio_b->ant = novo_b;
        novo_b->ant->prox  = novo_b;
    }
}

//================================================================================
// Esta função insere processos em uma lista dupla
// int id: id do processo
// int tam: tamanho do processo
//================================================================================ 
void inserir_processo(int id, int tam){
    novo_p = (processo*)malloc(sizeof(processo));
    
    novo_p->id = id;
    novo_p->tam_processo = tam;

    if(inicio_p == NULL){
        inicio_p = novo_p;
        novo_p->ant = novo_p;
        novo_p->prox = novo_p;
    }
    else{
        novo_p->prox = inicio_p;
        novo_p->ant = inicio_p->ant;
        inicio_p->ant = novo_p;
        novo_p->ant->prox  = novo_p;
    }
}

//================================================================================
//
//================================================================================
void alocar(){
    int n_processos, i, tam_processo;
    
    printf("\n\nQuantos processos quer alocar? ");
    scanf("%d", &n_processos);
    
    for(i = 1; i <= n_processos; i++){
        printf("\nDigite o tamanho do processo %d: ", i);
        scanf("%d", &tam_processo);
        inserir_processo(i, tam_processo);
    }
    printf("\n\n");
    
    novo_p = inicio_p;
    do{
        novo_b = inicio_b;
        do{
            if(novo_b->tam_bloco >= novo_p->tam_processo && novo_b->id_processo == 0){
                printf("O processo %d esta alocado no bloco %d\n",novo_p->id, novo_b->id);
                novo_b->id_processo = novo_p->id;
                novo_p->id_bloco = novo_b->id;
                break;
            }
            novo_b = novo_b->prox;
        }while(novo_b != inicio_b);
        novo_p = novo_p->prox;
    }while(novo_p != inicio_p);
}

//================================================================================
// Esta função imprime na tela os dados da memória
//================================================================================
void listar_memoria(){
    if(inicio_b == NULL){
        printf("Lista vazia!\a\n\n");
    }
    else{
        novo_b = inicio_b;
        printf("========== MEMORIA =============\n");
        printf("================================\n");
        printf("  ID |  TAMANHO  |  ID PROCESSO \n");
        printf("================================\n");
        do{
            printf("  %d  |     %2d    |      %d    =\n",novo_b->id, novo_b->tam_bloco, novo_b->id_processo);
            printf("--------------------------------\n");
            novo_b = novo_b->prox;
        }while(novo_b != inicio_b);
        printf("================================\n");
        printf("\n\n");
    }
}

//================================================================================
// Esta função lista todos os processos inseridos na memória
//================================================================================
void listar_processos(){
    if(inicio_p == NULL){
        printf("Lista vazia!\a\n\n");
    }
    else{
        novo_p = inicio_p;
        printf("========== PROCESSOS ===========\n");
        printf("================================\n");
        printf("  ID |  TAMANHO  |  ID BLOCO    \n");
        printf("================================\n");
        do{
            printf("  %d  |     %2d    |      %d    =\n",novo_p->id, novo_p->tam_processo, novo_p->id_bloco);
            printf("--------------------------------\n");
            novo_p = novo_p->prox;
        }while(novo_p != inicio_p);
        printf("================================\n");
        printf("\n\n");
    }
}

//================================================================================
// Função principal
//================================================================================
int main(int argc, char** argv) {
    int op;
    FILE *file;
    
    cria_arquivo(file);
    le_arquivo(file);
    
    printf("-------------------MENU-------------------\n");
    printf("1- Mostrar dados da memoria\n");
    printf("2- Mostrar dados dos processos\n");
    printf("3- Alocar processos\n"); 
    printf("4- Sair\n");
    printf("------------------------------------------\n");
    printf("Opcao: ");
    scanf("%d",&op);
    printf("------------------------------------------\n\n");
    
    while(op != 0){
        switch(op){
            case 1:
                listar_memoria();
            break;
            case 2:
                listar_processos();
            break;
            case 3:
                alocar();
            break;
            case 4:
                exit(0);
            break;
            default: printf("opcao invalida! \a\n\n");
        }
        printf("-------------------MENU-------------------\n");
        printf("1- Mostrar dados da memoria\n");
        printf("2- Mostrar dados dos processos\n");
        printf("3- Alocar processos\n"); 
        printf("4- Sair\n");
        printf("------------------------------------------\n");
        printf("Opcao: ");
        scanf("%d",&op);
        printf("------------------------------------------\n\n");
    }
    return (EXIT_SUCCESS);
}