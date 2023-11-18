// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#ifndef TRABALHOP_ESPACO_H
#define TRABALHOP_ESPACO_H

typedef struct sala sala, *psala;

struct sala{
    int id;
    int capacidade;
    int liga[3]; //-1 nao existe
};


sala *PreencherArray(sala *ex, int *global);
void validacao_sala(sala *tab, int total);
void imprimirsala(sala *tab, int total);

#endif //TRABALHOP_ESPACO_H
