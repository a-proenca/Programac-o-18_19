// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#include <stdio.h>
#include <stdlib.h>
#include "Ferramentas.h"
#include "pessoas.h"
#include "utils.h"
#include "virus.h"

int main(){

    sala *sala=NULL;
    ppessoa pessoas=NULL;
    piter  simulacao=NULL;
    int global=0;
    cabecalho();
   sala = PreencherArray(sala,&global);
   if(sala==0){
       printf("ERRO!,Sala vazia");
   }
//SALAS
    validacao_sala(sala,global);
    imprimirsala(sala,global);

//PESSOAS
ppessoa vetorpessoas= NULL;
vetorpessoas = escrevelista(vetorpessoas);
initRandom();
inserirpessoa(sala,vetorpessoas,global);

//MENU
int res= menu_inicial(vetorpessoas,sala,global,simulacao);
if(res==-1){ // Libertar memória aqui
    free(sala);
    libertamemoria(pessoas);
    libertamemoria_list_list(simulacao);
    mostradados(pessoas);
}
return 0;
}

