// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#ifndef TRABALHOP_FERRAMENTAS_H
#define TRABALHOP_FERRAMENTAS_H
#include <stdio.h>
#include "pessoas.h"
#include "pessoas.h"
#include "virus.h"

void limpar_buffer();
void cabecalho();
void libertamemoria_list_list(piter sim);
void libertamemoria(ppessoa pess);
int menu_inicial(ppessoa p,sala *sal,int global, piter simulacao);
int menu_simulacao(ppessoa p, sala *sal, int global,piter simulacao);

#endif //TRABALHOP_FERRAMENTAS_H
