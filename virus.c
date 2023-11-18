// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#include "virus.h"

void taxa_diss(ppessoa p,sala *sa, int total) {
    int pessoas_sala = 0, conta_doentes = 0, taxa_d = 0;
    float res;
    int *ids = malloc(sizeof (int) * total);

    for (int i = 0; i < total; i++) {
        ids[i] = sa[i].id;

    }

    for (int i = 0; i < total; i++) {
        ppessoa aux = p;


        while (aux != NULL) {
            if (ids[i] == aux->sala->id) {
                pessoas_sala++; // conta pessoas por sala
                if (aux->estado == 'D') { // conta doentes por sala
                    conta_doentes++;
                }
            }

            aux = aux->prox;
        }
        res = (float) pessoas_sala * 0.05; // numero de pessoas que um doente infeta
        taxa_d = conta_doentes * (int) res; // total de pessoas que irão ficar doente em cada sala

        ppessoa novo = p;
        while(taxa_d > 0 && novo != NULL){ // enquanto houver pessoas para ficarem doentes numa sala && novo nao chegar ao fim
            if(ids[i] == novo->sala->id){ // se as pessoas estiverem na mesma sala
                if(novo->estado == 'S'){ // se o estado for S , torna-se D e a ha menos 1 pessoa a ficar infetada
                    novo->estado = 'D';
                    taxa_d--;
                }
            }
            novo = novo->prox;
        }

        pessoas_sala = 0;
        conta_doentes = 0;
        res = 0;
        taxa_d = 0;
    }


}


void prob_rec(ppessoa p){
    int prob;

    for(int i = 0;i<sizeof(p) ;i++) {
        prob = (1 / (p[i].idade));
    }
}

void dur_infc(ppessoa p){
    int dias;

    for(int i=0;i<sizeof(p);i++){
        dias = (5+ (p[i].idade%2));
    }
}

void taxasinfo(ppessoa p) {

    int saudavel = 0, doente = 0, imune = 0, total_pessoas = 0, recuperado = 0;
    double taxa_saudavel = 0, taxa_doente = 0, taxa_imune = 0, taxa_recuperado = 0;

    while (p != NULL) {
        total_pessoas++;
        if (p->estado == 'S') {
            saudavel++;
        } else if (p->estado == 'D') {
            doente++;
        } else if (p->estado == 'I') {
            imune++;
        } else if (p->estado == 'R') {
            recuperado++;
        }
        p = p->prox;
    }
    taxa_saudavel = saudavel / (double) total_pessoas;
    taxa_doente = doente / (double) total_pessoas;
    taxa_imune = imune / (double) total_pessoas;
    taxa_recuperado = recuperado / (double) total_pessoas;
    printf("========================\n");
    printf("Taxa de saudaveis: %.2f\n", taxa_saudavel);
    printf("Taxa de doentes: %.2f\n", taxa_doente);
    printf("Taxa de imunes: %.2f\n", taxa_imune);
    printf("Taxa de recuperados: %.2f\n", taxa_recuperado);
}



void PRecuperacao(ppessoa p) {
    int idd = 0;
    float resultado;

    if (p->estado == 'D') {
        idd = p->idade;
        resultado = 1 / (double) idd;
        if (probEvento(resultado) == 1) {
            p->estado = 'R';
        }
    }

}


void Duracao_Maxima(ppessoa p) {
    int idade = 0, dias_doente = 0;
    float resultado;

    if (p->estado == 'D') {
        idade = p->idade;
        dias_doente = p->dias_doente;
        resultado = ((double) idade / 10) + 5;
        if ((int) resultado <= dias_doente) {
            p->estado = 'R';
        }
    }

}


void TaxaImune(ppessoa p){
    if (p->estado == 'R') {
        if (probEvento(0.2) == 1) {
            p->estado = 'I';
            printf("\nDoente:%s esta imune\n", p->nome);
        }
    }
}

void DisPessoaSala(ppessoa p, sala *sal, int global) {
    int pessoas_sala = 0;
    int *ids = malloc(sizeof (int) * global);

    for (int i = 0; i < global; i++) {
        ids[i] = sal[i].id;
    }
    for (int i = 0; i < global; i++) {
        ppessoa aux = p;

        while (aux != NULL) {
            if (ids[i] == aux->sala->id) {
                pessoas_sala++;
            }
            aux = aux->prox;
        }
        printf("Nr Pessoas:%d   sala:%d\n", pessoas_sala, ids[i]);
        pessoas_sala = 0;
    }
    printf("========================\n");
}


piter avancar(ppessoa p, sala *sal, int global,piter lista){
    taxa_diss(p,sal,global);
    ppessoa  aux=p;
    while(p != NULL){
        if(p->estado == 'D'){
            p->dias_doente++;
        }
        PRecuperacao(p);
        Duracao_Maxima(p);
        TaxaImune(p);
        p = p->prox;
    }
    lista=adicionateracao(aux, lista);
    mostrasimulacao(lista);
    return lista;
}




