/* 
 * Instituição: UERGS
 * Curso: Engenharia de computação
 * Arquivo: BubleSort.c
 * Autor: Guilherme Lague
 * E-mail: guilhermelaguebmx@gmail.com
 * Descrição: Buble sort para organizar processos pelo tempo de execução.
 *            Foi utilizada lista duplamente encadeada. 
 * Criado em 9 de Abril de 2017, 23:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//================================================================================
// int id: id do processo
// char nome[20]: nome do processo
// char status[20]: status do processo
// int prioridade: prioridade do processo
// int t_ex: tempo de execução do processo
// int t_en: tempo de entrada do processo
// struct lista *ant: ponteiro para o processo anterior
// struct lista *prox: ponteiro para o processo posterior
//================================================================================
typedef struct lista{ // onde vai ser armazenado os processos de acordo com tempo de chegada
    int id;
    char nome[20];
    char status[20];
    int prioridade;
    int t_ex;
    int t_en;
    struct lista *ant;
    struct lista *prox;   
}lista;

int id = 1;
// ponteiros para os processos
lista *novo = NULL, *inicio = NULL, *fim = NULL;

//================================================================================
// Esta função insere processos em uma lista dupla
// int id: id do processo
// int tam: tamanho do processo
// int t_ex: tempo de execução do processo
// int t_en: tempo de entrada do processo
//================================================================================
void inserir(int id,char *nome, int t_ex, int t_en){ 
    novo = (lista*)malloc(sizeof(lista));
    novo->id = id;
    strcpy(novo->nome,nome);
    novo->t_ex = t_ex;
    novo->t_en = t_en;

    if(inicio == NULL){
        fim = novo;
        inicio = novo;
        novo->ant = NULL;
    }else{
        fim->prox = novo;
        novo->ant = fim;
        fim = fim->prox;
    }
    novo->prox = NULL;
}

//================================================================================
// Esta função organiza os processos segundo o algoritmo Buble-sort
//================================================================================
void buble_sort(){
    int id, prio, entrada, exec;
    char nome[3], status[20]; 
    
    if(inicio == NULL){
        printf("Lista vazia!\a\n\n");
    }
    else{
        lista *pivo = NULL, *atual = NULL;
        pivo = inicio;
        while(pivo != NULL){
            atual = pivo->prox;
            while(atual != NULL){
                if(pivo->t_ex > atual->t_ex){
                    id = pivo->id;
                    pivo->id = atual->id;
                    atual->id = id;
                    
                    strcpy(nome, pivo->nome);
                    strcpy(pivo->nome,atual->nome);
                    strcpy(atual->nome, nome);
                    
                    strcpy(status, pivo->status);
                    strcpy(pivo->status,atual->status);
                    strcpy(atual->status, status);
                    
                    prio = pivo->prioridade;
                    pivo->prioridade = atual->prioridade;
                    atual->prioridade = prio;
                    
                    entrada = pivo->t_en;
                    pivo->t_en = atual->t_en;
                    atual->t_en = entrada;
                    
                    exec = pivo->t_ex;
                    pivo->t_ex = atual->t_ex;
                    atual->t_ex = exec;
                }
                atual = atual->prox;
            } 
           pivo = pivo->prox;
        }
    }
}

//================================================================================
// Esta função lista todos os processos da lista 
//================================================================================
void listar(){
    if(inicio==NULL){
        printf("Lista vazia!\a\n\n");
    }
    else{
        novo = inicio;
        printf("==================================LISTA DE PROCESSOS=================================\n");
        printf("=====================================================================================\n");
        printf("  ID |          PROCESSO          | TEMPO DE CHEGADA | TEMPO DE CPU =\n");
        printf("=====================================================================================\n");
        while(novo!=NULL){
            printf("  %d  |             %s             |       %d      |       %d        =\n",novo->id, novo->nome, novo->t_en, novo->t_ex);
            printf("---------------------------------------------------------------------------------\n");
            novo = novo->prox;
        }
        printf("=====================================================================================\n");
        printf("\n\n");
    }
}

//================================================================================
// Função principal
//================================================================================
int main(int argc, const char* argv[]){
    int op = 0, len, t_ex, t_en;
    char nome[20];
    
    printf("-------------------MENU-------------------\n");
    printf("1- Inserir processos\n");
    printf("2- Listar processos\n");
    printf("3- organizar por tempo de execução\n");
    printf("4- Sair\n");
    printf("------------------------------------------\n");
    printf("Opcao: ");
    scanf("%d",&op);
    printf("------------------------------------------\n\n");

    while(op != 0){
        switch(op){
            case 1:
                while(op == 1){
                    printf("Digite o nome do processo ou 0 (zero) para parar de inserir: ");
                    scanf("%s",&nome);
                    
                    len = strlen(nome);
                    if(strcmp("0",nome) == 0){
                        break;
                    }else{
                        printf("Digite o tempo de chegada do processo: ");
                        scanf("%d",&t_en);
                        printf("Digite o tempo de cpu do processo: ");
                        scanf("%d",&t_ex);
                        inserir(id, nome,t_ex, t_en);
                    }
                    id++;
                }
            break;
            case 2:
                listar();
            break;
            case 3:
                buble_sort();
                listar();
            break;
            case 4:
                exit(0);
            break;
            default: printf("Opcao invalida!\a\n\n");
        }
        printf("-------------------MENU-------------------\n");
        printf("1- Inserir processos\n");
        printf("2- Listar processos\n");
        printf("3- organizar por tempo de execução\n");
        printf("4- Sair\n");
        printf("------------------------------------------\n");
        printf("Opcao: ");
        scanf("%d",&op);
        printf("------------------------------------------\n\n");
    }
    return(EXIT_SUCCESS);
}