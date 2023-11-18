// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#include "Ferramentas.h"

void cabecalho() {
    printf("--->Simulacao da Propagacao de Virus<---\n");
    printf("Trabalho realizado por Andre Proenca - 2016018783\n");
}

void limpar_buffer() {
    while (getchar() != '\n');
}

void libertamemoria(ppessoa pess) {
    ppessoa aux;
    while (pess != NULL) {
        aux = pess;
        pess = pess->prox;
        free(aux);
    }
}

void libertamemoria_list_list(piter sim) {
    piter aux;
    while (sim != NULL) {
        aux = sim;
        sim = sim->prox;
        libertamemoria(aux->atual);
        free(sim);
    }
}

int menu_inicial(ppessoa p, sala *sal, int global, piter simulacao) {
    int opcao = 0;
    int res = 0;
    int flag = 0;
    char c;
    do {
        printf("\t\n---MENU---\n");
        printf("1- Simulacao\n");
        printf("2- Sair\n");
        printf("opcao:");

        do {
            flag = 0;
            if (((scanf(" %d%c", &opcao, &c)) != 2) || c != '\n') {
                flag = 1;
                limpar_buffer();
                opcao = 0;
            }
            flag = 0;
        } while (flag == 1);

        switch (opcao) {
            case 1:
                res = menu_simulacao(p, sal, global, simulacao);
            case 2:
                res = -1;
                break;
            default:
                break;
        }
        if (res == -1) {
            return -1;
        }

    } while (opcao != 2);
}

int menu_simulacao(ppessoa p, sala *sal, int global, piter simulacao) {
    int op = 0;
    int flag = 0;
    int res = 0;
    int iteracao = 0;
    char c;
    do {
        printf("\n-------MENU SIMULACAO-------\n");
        printf("1- Avancar uma iteracao na simulacao\n");
        printf("2- Apresentar estatistica\n");
        printf("3- Mostrar Pessoas\n");
        printf("4- Adicionar doente\n");
        printf("5- Transferir pessoas\n");
        printf("6- Recuar x Iteracoes\n");
        printf("7- Terminar Simulacao\n");
        printf("opcao:");

        if (scanf(" %d%c", &op, &c) != 2 || c != '\n') {
            limpar_buffer();
            op = 0;
        }

        switch (op) {
            case 1:
                simulacao = avancar(p, sal, global, simulacao);
                break;
            case 2:
                taxasinfo(p);
                DisPessoaSala(p, sal, global);
                break;
            case 3:
                mostradados(p);
                break;
            case 4:
                p = criapessoa(p, sal, global);
                break;
            case 5:
                p = transf_pess(sal, p, global);
                mostradados(p);
                break;
            case 6:
                if (simulacao != NULL) {
                    if (getlastnumber(simulacao) != 0) {
                        do {
                            flag = 0;
                            printf("\nInsira Quantas iteracoes quer recuar (MAX 3):");
                            if (scanf(" %d%c", &iteracao, &c) != 2 || c != '\n') {
                                limpar_buffer();
                                iteracao = 5;
                                flag == 1;
                            }

                            res = getlastnumber(simulacao) - iteracao;

                        } while (iteracao > 3 || res < 0 || flag == 1);
                        simulacao = recua(simulacao, iteracao);
                        mostrasimulacao(simulacao);
                        p = actualiza(simulacao, p);
                    }else{
                        printf("Apenas existe uma iteracao da simualacao\n");
                    }
                } else {
                    printf("Nao existe qualquer simulacao\n");
                }
                break;
            case 7:
                term_sim(p);
                print_last(p);
                return -1;
            default:
                break;
        }

    } while (op != 7);
}