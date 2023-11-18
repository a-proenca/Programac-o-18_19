// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783


#include "espaco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ferramentas.h"

sala *PreencherArray(sala *ex, int *global) {
    sala *p = NULL;
    FILE *fp;
    int dim;
    char file[32];
    int flag = 0;
    char c;

    do {
        printf("\nIndique o nome do ficheiro:");
        flag = 0;
        if (((scanf(" %31[^\n]%c", file, &c)) > 32) || c != '\n') {
            flag = 1;
            limpar_buffer();
        }
        fp = fopen(file, "rb");
        if (fp == NULL) {
            printf("Ficheiro (%s) nao existe!",file);
        }


    } while (flag == 1 || fp == NULL);

    //Ir ao final do ficheiro
    fseek(fp, 0, SEEK_END);

    dim = ftell(fp);

    //Quantas estruturas existentes
    *global = dim / sizeof (sala);

    p = malloc(sizeof (sala) * *(global));

    if (p == NULL) {
        return ex;
    }
    ex = p;
    fseek(fp, 0, SEEK_SET);



    for (int i = 0; i < *global; i++) {
        fread(&ex[i], sizeof (sala), 1, fp);
    }

    fclose(fp);


    return ex;

}

void validacao_sala(sala *tab, int total) {

    int id_adjacente;

    // para cada sala no array de salas
    for (int i = 0; i < total; i++) {


        for (int x = i + 1; x < total; x++) {

            if (tab[i].id == tab[x].id) {
                printf("Há ids repetidos");
                return;
            }
        }


        // procura se ha ids negativos
        if (tab[i].id < 0) {
            printf("Os ids dos locais tem de ser sempre positivos\n");
            return;
        }




        sala sala1 = tab[i];
        int id_sala1 = sala1.id;


        for (int j = 0; j < 3; j++) {

            if (sala1.liga[j] != -1) {
                id_adjacente = sala1.liga[j];
            }



            for (int k = 0; k < total; k++) {
                sala sala2 = tab[k];


                if (sala2.id == id_sala1) continue;

                int sala1_encontrada = 0;


                if (sala2.id == id_adjacente) {


                    for (int l = 0; l < 3; l++) {

                        //se encontrar poe a flag a 1
                        if (sala2.liga[l] == id_sala1) {
                            sala1_encontrada = 1;
                            break;
                        }
                    }
                }

                if (sala1_encontrada)break;


                else return;

            }
        }

    }

}

void imprimirsala(sala *tab, int total) {

    printf("========SALAS=======\n");
    for (int i = 0; i < total; i++) {
        printf("Id: %d\n", tab[i].id);
        printf("Capacidade: %d\n", tab[i].capacidade);
        for (int j = 0; j < 3; j++) {
            if (tab[i].liga[j] >= 0) {
                printf("Liga: %d\n", tab[i].liga[j]);

            }

        }
        printf("====================\n");

    }
}