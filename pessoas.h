// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783
#ifndef TRABALHOP_PESSOAS_H
#define TRABALHOP_PESSOAS_H
#include "espaco.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>

typedef struct pessoas pessoas, *ppessoa;
struct pessoas{
    char nome[100]; // nome
    int idade; // idade da pessoa
    char estado; // Estado: 'S' -> Saudavel, 'D' -> Doente, 'I' -> Imune
    int dias_doente; // caso esteja doente, mostra ha quantos dias foi infetado
    ppessoa prox; // ponteiro que aponta para o proximo elemento da lista
    psala sala; // ponteiro que aponta para a estrutura referente ao espaço
};
typedef struct iteracoes iteracoes, *piter;
struct iteracoes{
    int num_iter;
    ppessoa atual;
    piter prox;
};
int getlastnumber(piter lista);
piter adicionateracao( ppessoa lista_atual, piter lista);
void mostradados(ppessoa aux);
void mostrasimulacao(piter lista);
ppessoa escrevelista( ppessoa vetor);
void  inserirpessoa(sala *sal, ppessoa p, int global);
ppessoa criapessoa(ppessoa p, sala *sal, int global);
int verpessoas(sala *tab, ppessoa p, int total);
ppessoa transf_pess(sala *pss, ppessoa p,int total);
void term_sim(ppessoa p);
void print_last(ppessoa p);
piter recua(piter lista_rec,int recua);
ppessoa actualiza(piter sim,ppessoa p);
int verificanomeexiste( char *nome, ppessoa lista);
#endif //TRABALHOP_PESSOAS_H
