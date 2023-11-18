// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020
//André Proença - 2016018783

#include "pessoas.h"
#include "Ferramentas.h"


void mostradados(ppessoa aux) {
    ppessoa p = aux;
    while (p != NULL) {// cas
        printf("\nNome:%s Idade:%d Estado:%c ", p->nome, p->idade, p->estado);
        if (p->estado == 'D') {
            printf("Dias:%d", p->dias_doente);
        }
        printf("Sala:%d",p->sala->id);
        printf("\n");
        p = p->prox;
    }
}

ppessoa actualiza(piter sim,ppessoa p){
    piter a=sim;
    ppessoa aux=NULL;
    ppessoa act=NULL;
    ppessoa list=NULL;
    ppessoa auxi=NULL;

    while(a!=NULL){
        aux=a->atual;
        a=a->prox;
    }
    libertamemoria(p);
    while(aux!=NULL){
        act=(ppessoa) malloc(sizeof(pessoas));
        if(act==NULL){
            printf("Erro na alocacacao de memoria");
            return list;
        }

        act->prox=NULL;
        act->sala= aux->sala;
        act->estado=aux->estado;
        act->dias_doente=aux->dias_doente;
        act->idade=aux->idade;

        for(int u=0; u<sizeof(aux->nome); u++){
            act->nome[u]=aux->nome[u];
        }
        //preeche campos
        if (list==NULL){
            list=act;
        }else {
            auxi=list;
            while(auxi->prox!=NULL){
                auxi= auxi->prox;
            }
            auxi->prox=act;
        }
        aux=aux->prox;
    }
    return list;
}

ppessoa escrevelista(ppessoa vetor) {
    FILE *fp;
    char file[32];
    int flag=0;
    char c;

    // o p será o primeiro nó
    ppessoa novo = NULL; // novo nó
    ppessoa anterior = NULL; // nó anterior
    pessoas lida;
    do {
        printf("\nQual e o nome do ficheiro: ");
        flag = 0;
        if (((scanf(" %31[^\n]%c", file, &c)) > 32) || c != '\n') {
            flag = 1;
            limpar_buffer();
        }
        fp = fopen(file, "r");
        if (fp == NULL) {
            printf("Ficheiro (%s) nao existe!",file);
        }


    } while (flag == 1 || fp == NULL);

    while (fscanf(fp, "%s %d %c", lida.nome, &lida.idade, &lida.estado) ==3) {
        if (lida.estado == 'D') {
            fscanf(fp, " %d", &lida.dias_doente);
        }
        novo = (ppessoa) malloc(sizeof(pessoas)); //aloca espaço de memoria para o novo nó
        if (novo == NULL) {
            printf("Erro na alocacao de memoria\n");
            fclose(fp);
            return vetor;
        }
        for(int i=0;i<sizeof(lida.nome);i++){
            novo->nome[i]=lida.nome[i];//copiar apenas os digitos preenchidos
        }
        novo->idade = lida.idade;
        novo->estado = lida.estado;
        novo->dias_doente = lida.dias_doente;
        novo->prox = NULL; // o novo nó é o ultimo inicialmente
        if (vetor == NULL) { // se a lista estiver vazia o p é o ultimo nó
            vetor = novo;
        } else {
            anterior = vetor;
            while (anterior->prox != NULL) {
                anterior = anterior->prox;
            }
            anterior->prox = novo;
        }
    }
    return vetor;
}

void  inserirpessoa(sala *sal, ppessoa p, int global){
    int capacidade = 0, indice;
    ppessoa aux = p;
    while(p != NULL){
        do{
            indice = intUniformRnd(0,global-1);
            capacidade = sal[indice].capacidade;
            p->sala = &sal[indice];

        }while(verpessoas(sal,aux,global) > capacidade);
        p->sala->id = sal[indice].id; // a pessoa é então inserida numa sala
        p = p->prox; // passa para a proxima pessoa
    }
}
int verificanomeexiste( char *nome, ppessoa lista){
    ppessoa aux=lista;
    while(aux!=NULL){
        if(strcmp(aux->nome,nome)==0){
            return 1;
        }
        aux=aux->prox;
    }
    return 0;
}


ppessoa criapessoa(ppessoa p, sala *sal, int global){
    ppessoa novo;
    novo = malloc(sizeof(pessoas));
    char c;
    if(novo  == NULL){
        printf("Erro na alocacao de memória\n");
        return p;
    }
    else{ // adiciona uma pessoa nova na lista ligada
        int flag = 1;
        int id = 0;
        int res=0;
        novo->prox = p;
        p = novo;
        char nome[100];

        while(flag){
            do{
                printf("Id do local: ");
                if(scanf(" %d%c", &id, &c) != 2 || c != '\n'){
                    limpar_buffer();
                    id=0;
                }
            }while(id<=0 && id>global);
            for(int i = 0; i < global; i++){
                if(id == sal[i].id){
                    p->sala = &sal[i];
                    flag = 0;
                    break;
                }
            }
        }
        do{
            flag=0;
            printf("Nome: ");
            if (((scanf(" %99[^\n]%c", nome, &c)) > 100) || c != '\n') {

                flag = 1;
                limpar_buffer();
            }
            res= verificanomeexiste(nome,p);
            if(res==1){
                printf("A pessoa que pretende adicionar ja existe\n");

            }
        }while(flag == 1 || res==1);
        for(int i=0; i <sizeof(nome);i++){
            p->nome[i]= nome[i];
        }


        do{
            printf("Idade: ");
            if(scanf(" %d%c", &p->idade, &c) != 2 || c != '\n'){
                limpar_buffer();
                p->idade=0;
            }
        }while(p->idade<=0);
        p->estado = 'D';
        do{
            printf("Dias doente: ");
            if(scanf(" %d%c", &p->dias_doente, &c) != 2 || c != '\n'){
                limpar_buffer();
                p->dias_doente=0;
            }
        }while(p->dias_doente<=0);
    }
    return p;
}

int verpessoas(sala *tab, ppessoa p, int total) {
    int pessoas_sala = 0;
    if (tab->id == p->sala->id) {
        pessoas_sala++;
    }
    p = p->prox;
    return pessoas_sala;
}
int verificaexiste(int vetor[], int tam, int numero ){
    for(int i=0; i<tam;i++){
        if(vetor[i]==numero){
            return 1;
        }
    }
    return 0;
}

ppessoa  transf_pess(sala *pss, ppessoa p,int total) {
    ppessoa r = p;
    int transf=0;
    sala *f=pss;
    char c;
    int npessoas = 0, salaid = 0, sala_id = 0;
    do{
        printf("\nInsira o Numero de pessoas que pretende transferir:");
        if(scanf(" %d%c", &npessoas, &c) != 2 || c != '\n'){
            limpar_buffer();
            npessoas=0;
        }
    }while(npessoas<=0);
    do{
        printf("\nInsira a sala de origem:");
        if(scanf(" %d%c", &salaid, &c) != 2 || c != '\n'){
            limpar_buffer();
            salaid=0;
        }
    }while(salaid<=0);
    do{
        printf("\nInsira a sala de destino:");
        if(scanf(" %d%c", &sala_id, &c) != 2 || c != '\n'){
            limpar_buffer();
            sala_id=0;
        }
    }while(sala_id<=0);
    int conta = 0;
    int random[npessoas];
    int res=1;
    int conta_dest=0;
    ppessoa a=p;
    ppessoa v=p;
    int conta_pessoas=0;
    for(int y=0;y<npessoas;y++){
        random[y]=-1;
    }

    for (int i = 0; i < total; i++) { // verifica se as salas ligam  e conta o número de pessoas na sala
        if (pss[i].id == salaid) {// sala atual
            for (int j = 0; j < 3; ++j) {
                if (pss[i].liga[j] == sala_id) {//VER SE AS SALAS LIGAVAM
                    transf= i;
                    while (r != NULL) {
                        if (r->sala->id == salaid) {
                            conta++;
                        }
                        r = r->prox;
                    }
                }
            }
            if (conta==0){
                printf("Nao existem pessoas para transferir ou as salas nao ligam\n");
                return p;
            }
        }
    }
    while(a != NULL){//conta o numero de pessoas na sala de destino
        if(a->sala->id == sala_id){
            conta_dest++;
        }
        a=a->prox;
    }
    while(v !=NULL){
        conta_pessoas++;
        v=v->prox;
    }
    ppessoa li=p;
    int ve[conta];
    int pos=0,index=1;
    int nr=0;

    if (npessoas <= conta && pss[transf].capacidade >= conta_dest+npessoas) {
        while(li!=NULL){
            if( li->sala->id == salaid) {
                ve[pos]=index;
                pos++;
            }
            index++;
            li=li->prox;

        }
        for (int i = 0; i < npessoas; i++) {
            do {
                nr=intUniformRnd(0, conta-1);
                res= verificaexiste(random,npessoas,ve[nr]);
            } while (res==1);
            random[i]= ve[nr];
        }
    } else {// caso não tenha capacidade, ou não tenha pessoas suficientes
        printf("\nA sala de destino nao tem capacidade ou o numero de pessoas que pretende transferir é superior ao numero de pessoas na sala de origem");
        return p;
    }
    li=p;
    index=1;
    res=0;
    for (int i=0; i< total; i++){
        if(sala_id==pss[i].id){
            while (li!=NULL){
                res=verificaexiste(random,npessoas,index);
                if(res==1){
                    li->sala=&pss[i];
                }
                index++;
                li=li->prox;
            }

        }

    }
    return p;

}




void term_sim(ppessoa p){
    FILE * pf;
    pf = fopen("report.txt", "w");
    if(pf == NULL){
        printf("Erro ao criar o ficheiro.\n");
        exit(EXIT_FAILURE);
    }
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
    fprintf(pf,"-----ESTATISTICA-----\n\n");
    fprintf(pf,"SAUDAVEL:%f\n",taxa_saudavel);
    fprintf(pf,"DOENTE:%f\n",taxa_doente);
    fprintf(pf,"IMUNE:%f\n",taxa_imune);
    fprintf(pf,"RECUPERADO:%f\n",taxa_recuperado);
    fclose(pf);
}

void print_last(ppessoa p){
    char nomefich[100];
    printf("\nInsira o nome do ficheiro que quer guardar:");
    scanf(" %31[^\n]",nomefich);
    FILE *pd;
    pd = fopen(nomefich, "w");
    if(pd == NULL) {
        printf("Erro ao criar o ficheiro.\n");
        exit(EXIT_FAILURE);
    }
    while (p!= NULL){
        fprintf(pd,"Nome: %s Idade: %d Estado: %c ", p->nome, p->idade, p->estado);
        if (p->estado == 'D') {
            fprintf(pd,"dias: %d", p->dias_doente);
        }
        fprintf(pd,"\n");
        p = p->prox;
    }
    fclose(pd);
}

int getlastnumber(piter lista)
{
    piter aux= lista;
    int iter=0;
    if (lista==NULL){
        return -1;
    }else{
        while (aux->prox!=NULL){
            aux= aux->prox;
            iter= aux->num_iter;
        }
        return iter;
    }
}
piter adicionateracao( ppessoa lista_atual, piter lista){
    int num_iter= getlastnumber(lista);
    num_iter+=1;// acrescenta um á iteração anterior
    piter novo= NULL,  aux=NULL;
    ppessoa  novopesssoa=NULL;
    ppessoa a=lista_atual,auxi=NULL;
    novo= (piter) malloc(sizeof(iteracoes));
    if(novo==NULL){
        printf("Erro na alocacacao de memoria");
        return lista;
    }
    novo->atual=NULL;
    novo->num_iter=num_iter;
    novo->prox= NULL;
    while (lista_atual != NULL) {// percorremis a lista de pessoas e copia nó a nó
        novopesssoa=(ppessoa) malloc(sizeof(pessoas));
        if(novopesssoa==NULL){
            printf("Erro na alocacacao de memoria");
            return lista;
        }
        novopesssoa->prox=NULL;
        novopesssoa->sala= lista_atual->sala;
        novopesssoa->estado=lista_atual->estado;
        novopesssoa->dias_doente=lista_atual->dias_doente;
        novopesssoa->idade=lista_atual->idade;
        for(int u=0; u<sizeof(novopesssoa->nome); u++){
            novopesssoa->nome[u]=lista_atual->nome[u];
        }
        //preeche campos
        if (novo->atual==NULL){
            novo->atual=novopesssoa;
        }else {
            auxi=novo->atual;
            while(auxi->prox!=NULL){
                auxi= auxi->prox;
            }
            auxi->prox=novopesssoa;
        }
        lista_atual = lista_atual->prox;
    }

    if(lista==NULL){
        lista=novo;
    }else{
        aux= lista;
        while (aux->prox!=NULL){
            aux= aux->prox;
        }
        aux->prox=novo;
    }
    return  lista;
}
void mostrasimulacao(piter lista){
    piter aux= lista;
    while (aux!=NULL){
        printf("\nNUMERO SIMULACAO %d",aux->num_iter);
        mostradados(aux->atual);
        printf("\n\n");
        aux= aux->prox;
    }
}
piter recua(piter lista_rec,int recua){
    piter aux=lista_rec;
    int num_iter= getlastnumber(lista_rec);//obtem o numero da ultima iteração
    int posatual= num_iter-recua;

    while(aux!=NULL){
        if(aux->num_iter == posatual){
            //vai percorrer o resto da lista e elimina
            piter  remove=aux->prox;
            aux->prox=NULL;
            while (remove!=NULL){
                aux = remove;
                remove = remove->prox;
                free(aux);
            }
        }else{
            aux=aux->prox;
        }
    }
    return lista_rec;
}