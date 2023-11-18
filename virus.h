// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#ifndef TRABALHOP_VIRUS_H
#define TRABALHOP_VIRUS_H
#include "espaco.h"
#include "pessoas.h"
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

void taxa_diss(ppessoa p,sala *sa, int total);
void taxasinfo(ppessoa p);
void PRecuperacao(ppessoa p);
void Duracao_Maxima(ppessoa p);
void TaxaImune(ppessoa p);
void DisPessoaSala(ppessoa p, sala *tab, int global);
piter avancar(ppessoa p, sala *sal, int global,piter lista);
#endif //TRABALHOP_VIRUS_H
