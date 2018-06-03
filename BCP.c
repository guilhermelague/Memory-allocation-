/* 
 * Instituição: UERGS
 * Curso: Engenharia de computação
 * Arquivo: BCP.c
 * Autor: Guilherme Lague
 * E-mail: guilhermelaguebmx@gmail.com
 * Descrição: Implementação de um simples BCP - Bloco de controle de processos.
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
// char prioridade[20]: prioridade do processo
// int cpu_time: tempo de cpu
// struct processos *ant: ponteiro para o processo anterior
// struct processos *prox: ponteiro para o processo posterior
//================================================================================
typedef struct processos{
    int id;
    char nome[20];
    char status[20];
    char prioridade[20];
    int cpu_time;
    struct processos *ant;
    struct processos *prox;
}processos;

// ponteiros para os processos 
processos *novo = NULL, *inicio = NULL, *fim = NULL;

//================================================================================
// Função para inserir no final da lista de processos
// int id: id do processo
// char *nome: nome do processo
// char *status: status do processo
// char *prioridade: prioridade do processo
// int cpu_time: tempo de cpu
//================================================================================
void inserir(int id,char *nome, char *status, char *prioridade, int cpu_time){
    novo = (processos*)malloc(sizeof(processos));
    novo->id = id;
    strcpy(novo->nome,nome);
    strcpy(novo->status,status);
    strcpy(novo->prioridade,prioridade);
    novo->cpu_time = cpu_time;

    if(inicio == NULL){
        fim = novo;
        inicio = novo;
        novo->ant = NULL;
    }
    else{
        fim->prox = novo;
        novo->ant = fim;
        fim = fim->prox;
    }
    novo->prox = NULL;
}

//================================================================================
// Função para listar os processos contidos na lista dupla
//================================================================================
void listar(){
    if(inicio == NULL){
        printf("Lista vazia!\a\n\n");
    }
    else{
        novo = inicio;
        printf("===============LISTA DE PROCESSOS=========================================\n");
        printf("  ID |          PROCESSO          | STATUS |  PRIORIDADE  | TEMPO DE CPU =\n");
        printf("==========================================================================\n");
        
        while(novo!=NULL){
            printf("  %d  |  %s  |  %s  |  %s  |  %d  =\n",novo->id, novo->nome, novo->status, novo->prioridade, novo->cpu_time);
            printf("---------------------------------------------------------------\n");
            novo = novo->prox;
        }

        printf("===============================================================\n");
        printf("\n\n");
    }
}

//================================================================================
// Função para remover processos por id contidos na lista dupla
// int id: id do processo
//================================================================================
void excluir(int id){    
    processos *anterior, *atual;
    int foi_excluido = 0;
    if(inicio == NULL){
        printf("Lista vazia!\a\n\n");
    }
    else{
        anterior = inicio;     
        atual = inicio;
        while(atual != NULL){
            if(atual->id == id){
                if(atual == inicio){
                    inicio = inicio->prox;
                    free(atual);
                    foi_excluido = 1;
                    break;
                }
                else if(atual == fim){
                    fim = anterior;		
                }
                anterior->prox = atual->prox;
                free(atual);
                foi_excluido = 1;
                break;	
            }
            else{
                anterior = atual;
                atual = atual->prox;

            }
        }
        if(foi_excluido == 1){
                printf("Processo [%d] excluido!\n\n", id);
        }else{
                printf("Processo [%d] nao existe na lista de processos!\n\n\a", id);
        }
    }
}

//================================================================================
// Função principal
//================================================================================
int main(int argc, char const *argv[]){
    int op = 0, len, id = 0, cpu_time;
    char nome[20], status[20], prioridade[20];

    printf("-------------------MENU-------------------\n");
    printf("1- Inserir processo na lista\n");
    printf("2- Listar processos\n");
    printf("3- Encerrar processo\n");
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
                    fflush(stdin);
                    gets(nome);
                    gets(nome);
                    len = strlen(nome);
                    if(strcmp("0",nome) == 0){
                        break;
                    }
                    else if(len > 20){
                        printf("\n\tErro, o nome do processo deve conter menos de 20 caracteres!\a\n\n");
                        break;
                    }else{
                        printf("Digite o status do processo (Bloqueado, Suspenso ou Executando): ");
                        fflush(stdin);
                        gets(status);
                        printf("Digite a prioridade do processo (Baixa, Normal ou Alta): ");
                        fflush(stdin);
                        gets(prioridade);
                        printf("Digite o tempo de cpu do processo: ");
                        scanf("%d",&cpu_time);
                        inserir(id, nome, status, prioridade, cpu_time);	
                    }
                    id++;
                }
            break;
            case 2:
                listar();
            break;
            case 3:
                printf("Digite o id do processo para excluir:");
                scanf("%d",&id);
                excluir(id);
            break;
            case 4:
                exit(0);
            break;
            default: printf("Opcao invalida!\a\n\n");
        }
        printf("-------------------MENU-------------------\n");
        printf("1- Inserir processo na lista\n");
        printf("2- Listar processos\n");
        printf("3- Encerrar processo\n");
        printf("4- Sair\n");
        printf("------------------------------------------\n");
        printf("Opcao: ");
        scanf("%d",&op);
        printf("------------------------------------------\n\n");
    }
    return 0;
}