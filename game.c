#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "utils.h"
#include "game.h"



void startPL(player *pl, int id){

        pl->jogador=id;
        pl->pedra=1;
        pl->addLinhaColuna=2;

}


void startgame(tabul *t){

    int tam;
    tam = intUniformRnd(3, 5);
    
    t->turno=0;
    t->linha=tam;
    t->coluna=tam;

    t->matriz = malloc(sizeof(char*)*t->linha);
    for(int i=0; i<t->linha; i++){
        t->matriz[i]= malloc(sizeof (char)*t->coluna);
    }

    for (int i=0;i < tam;i++){
        for(int j=0;j < tam;j++){

            t->matriz[i][j] = '_';

        }
    }

    printf("%dx%d\n",tam,tam);


}


void mostratabuleiro(tabul *t){
    for (int i=0;i < t->linha;i++){
        printf(" %d",i+1);
        for(int j=0;j < t->coluna;j++){
            printf("|%c|",t->matriz[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for(int j=0;j < t->coluna;j++){
        printf(" %d ",j+1);
    }
    printf("\n");

}


int updateTab(tabul *t,int l,int c){


        if(t->matriz[l][c] == 'G'){

            t->matriz[l][c] = 'Y';

        }else if(t->matriz[l][c] == 'Y'){

            t->matriz[l][c] = 'R';

        }else if (t->matriz[l][c] == 'R'){
            printf("A peca ja se encontra vermelha\n");
            return 0;
        }else if(t->matriz[l][c]=='_'){

            t->matriz[l][c] = 'G';

        }else{
            printf("A posicao ja se encontra ocupada\n");
        }

    return 1;

}


int updateTabPedra(player *p, tabul *t,int l,int c){


    if(p->pedra==0){
        printf("O jogador não dispoe de nenhuma pedra\n");
        return 2;
    }

    if(t->matriz[l][c] != '_'){
        printf("A posicao ja se encontra ocupada\n");
        return 0;
    }

    if (t->matriz[l][c] == '_'){
        t->matriz[l][c] = 'P';
        p->pedra=0;
        return 1;
    }
    return 0;
}

void addLC(tabul *t,player *p) {
    int c = 0,k=0;

    do{

        printf("_________________________________\n\n"
               "Selecione o modo de Jogo: \n    1-Linha\n    2-Coluna\n");
        printf(">");
        scanf("%d", &c);

        switch (c) {
            case 1:
            {
                k=addL(t,p);
                break;
            }
            case 2:
            {
                k=addC(t,p);
                break;
            }
            default:
                printf("Opcao indisponivel\n");
                break;

        }
    }while(k==0);

}


int addL(tabul *t,player *p){

    if(p->addLinhaColuna<=0){
        printf("Impossivel realizar operacao");
        return 2;
    }

    p->addLinhaColuna=p->addLinhaColuna-1;

    t->linha = t->linha+1;
    t->matriz = realloc(t->matriz,sizeof(char*)*t->linha);
    t->matriz[t->linha-1] = malloc(sizeof (char)*t->coluna);

    for(int i=0;i<t->coluna;i++){
        t->matriz[t->linha-1][i]='_';
    }

    return 1;
}
int addC(tabul *t,player *p){


    p->addLinhaColuna=p->addLinhaColuna-1;

    t->coluna = t->coluna+1;

    for(int i=0;i<t->linha;i++){

        t->matriz[i] = realloc(t->matriz[i],sizeof (char)*t->coluna);

        t->matriz[i][t->coluna-1]='_';
    }
    return 1;
}


void reverJogadas(tab tabl){

            while (tabl!=NULL) {
                printf("turno: %d\n",tabl->turno);
                printf("l:%d", tabl->linha);
                printf("  c:%d\n", tabl->coluna);
                mostratabuleiro(tabl);
                tabl = tabl->next;

            }

}

int verificaVitoria(tabul *t){

    int valida;

    for (int i=0;i < t->linha;i++){
        valida=1;
        for(int j=1;j < t->coluna;j++){

            if(t->matriz[i][j] == t->matriz[i][j-1] && t->matriz[i][j] != '_') {
                valida++;

                if (valida == t->coluna) {
                    return 1;
                }
            }else{
                valida =1;
            }
        }

    }

    for (int i=0;i < t->coluna;i++){
        valida=1;
        for(int j=1;j < t->linha;j++){

            if(t->matriz[j][i] == t->matriz[j-1][i] && t->matriz[j][i] != '_') {
                valida++;

                if (valida == t->linha) {
                    return 1;
                }
            }else{
                valida =1;
            }
        }

    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    if(t->coluna==t->linha) {
        valida = 0;
        for (int j = 0; j <= t->linha - 1; j++) {
            if (t->matriz[j][j] == t->matriz[0][0] && t->matriz[j][j] != '_') {
                valida++;

                if (valida == t->linha) {
                    return 1;
                }
            } else {
                valida = 0;
            }
        }

        int col = t->coluna - 1;

        for (int i = 0, j = col; j >= 0; j--, i++) {

            if (t->matriz[j][i] == t->matriz[col][0] && t->matriz[i][j] != '_') {

                valida++;
                if (valida == t->coluna) {
                    return 1;
                }
            } else {
                valida = 0;
            }
        }

    }

    return 0;
}


void turno(int turn){
    printf("_________________________________\n\n"
           "Turno: %d\n",turn);
    if(turn%2==0){
        printf("Jogador B:\n");

    }else{
        printf("Jogador A:\n");

    }
}
void pc(tab t){
    int l, c;
    l= intUniformRnd(0,t->linha-1);
    c= intUniformRnd(0,t->coluna-1);
    updateTab(t,l,c);
}


void menu(){
    int linha=0,coluna=0,k=0,tamanho = 0,valida=0,vec1=0,turn=0, c=0, modo=0;

    tab new=NULL, head=NULL;

    printf("_________________________________\n\n"
           "Bem vindo!\n");





    player pl1;
    player pl2;

    do {
        k=0;
        turn = 0;
        printf("_________________________________\n\n"
               "... \n    1-start\n    2-Load\n    4-Sair\n");
        printf(">");
        scanf("%d",&c);
        if (c==1) {
            printf("_________________________________\n"
                   "Jogo iniciado!\n");
            valida = 1;


            new = (tabul *)malloc(1*sizeof(tabul));


            startgame(new);
            insereTabuleiro( new,head);
            startPL(&pl1,1);
            startPL(&pl2,2);
            mostratabuleiro(new);

            do {
                printf("_________________________________\n\n"
                       "Selecione o modo de Jogo: \n    1-PvP\n    2-PvC\n");
                printf(">");
                scanf("%d", &c);

                switch (c) {
                    case 1: {
                        printf("Modo de Jogo Player vs Player\n");
                        modo=1;
                        break;
                    }
                    case 2: {
                        printf("Modo de Jogo Player vs Computer\n");
                        modo=2;
                        break;
                    }
                    default: {
                        printf(">Insira uma das opcoes");
                        break;
                    }
                }
            }while(modo==0);

            int end=0;
            do {

                if(turn%2!=0||modo==1) {

                    printf("_________________________________\n\n"
                           "... \n    1-Jogar\n    2-Jogar pedra\n    3-Adicionar linha/coluna\n    4-Mostrar Jogadas\n    5-Gravar\n    6-Sair\n\n");
                    printf(">");
                    scanf("%d", &c);


                    new->turno = new->turno + 1;
                    turn = new->turno;
                    turno(turn);
                    if (turn % 2 != 0) {
                        printf("ID: %d\nPedra: %d\nAddC/L: %d\n\n", pl1.jogador, pl1.pedra, pl1.addLinhaColuna);
                    } else {
                        printf("ID: %d\nPedra: %d\nAddC/L: %d\n\n", pl2.jogador, pl2.pedra, pl2.addLinhaColuna);
                    }


                    switch (c) {
                        case 1: {
                            int validaCor = 0;
                            do {
                                printf("Linha: ");
                                scanf("%d", &linha);
                                printf("coluna: ");
                                scanf("%d", &coluna);
                                validaCor = updateTab(new, linha - 1, coluna - 1);
                                head = insereTabuleiro(new, head);
                                printf("\n");
                                mostratabuleiro(new);
                            } while (validaCor == 0);
                            break;
                        }
                        case 2: {
                            int validaPedra = 0;
                            do {
                                printf("Linha: ");
                                scanf("%d", &linha);
                                printf("coluna: ");
                                scanf("%d", &coluna);
                                if (turn % 2 != 0) {
                                    validaPedra = updateTabPedra(&pl1, new, linha - 1, coluna - 1);
                                } else {
                                    validaPedra = updateTabPedra(&pl2, new, linha - 1, coluna - 1);
                                }
                                head = insereTabuleiro(new, head);

                                printf("\n");
                                mostratabuleiro(new);
                            } while (validaPedra == 0);
                            break;
                        }
                        case 3: {
                            if (turn % 2 != 0) {
                                if (pl1.addLinhaColuna > 0) {
                                    addLC(new, &pl1);
                                    head = insereTabuleiro(new, head);
                                } else { printf("Impossivel realizar operacao\n"); }
                            } else {
                                if (pl2.addLinhaColuna > 0) {
                                    addLC(new, &pl2);
                                    head = insereTabuleiro(new, head);
                                } else { printf("Impossivel realizar operacao\n"); }
                            }
                            mostratabuleiro(new);
                            break;
                        }
                        case 4: {
                            reverJogadas(head);
                            break;
                        }
                        case 5: {
                            gravar(head, pl1, pl2);
                            break;
                        }
                        case 6: {
                            end = 1;
                            break;
                        }

                    }
                }else if(modo==2 && turn%2==0){
                    new->turno = new->turno + 1;
                    turn = new->turno;
                    turno(turn);
                    pc(new);
                    head = insereTabuleiro(new, head);
                }

                vec1 = verificaVitoria(new);
                if(vec1==1){
                    printf("acabou");
                    end=1;}

            }while(end==0);
            menu();

        }else if(c==2 && valida == 1){

            printf("load");

        }else if(c==3 && valida == 1){
            //...save
        }else if(c!=5 && valida!=1){
            printf("O jogo nao se encontra iniciado");
        }else if(c==4){
            k=1;
        }else{
            printf("Comando Invalido\nTente help para mais informacoes\n");
        }



    }while(k==0);

}

tab insereTabuleiro(tab atual, tab head) {

    tab aux = NULL;


    if (head == NULL) {

        head = (tabul *) malloc(1 * sizeof(tabul));
        head ->turno = atual->turno;
        head->linha = atual->linha;
        head->coluna = atual->coluna;
        head->matriz = malloc(sizeof(char *) * head->linha);
        for (int i = 0; i < head->linha; i++) {
            head->matriz[i] = malloc(sizeof(char) * head->coluna);
        }
        for (int i = 0; i < head->linha; i++) {
            for (int j = 0; j < head->coluna; j++) {
                head->matriz[i][j] = atual->matriz[i][j];
            }
        }

    } else {
        aux = head;
        while (aux->next != NULL)
            aux = aux->next;

        aux->next = (tabul *) malloc(1 * sizeof(tabul));

        aux = aux->next;

        aux ->turno = atual->turno;
        aux->linha = atual->linha;
        aux->coluna = atual->coluna;
        aux->matriz = malloc(sizeof(char *) * aux->linha);
        for (int i = 0; i < aux->linha; i++) {
            aux->matriz[i] = malloc(sizeof(char) * aux->coluna);
        }
        for (int i = 0; i < aux->linha; i++) {
            for (int j = 0; j < aux->coluna; j++) {
                aux->matriz[i][j] = atual->matriz[i][j];
            }
        }

        aux->next = NULL;

    }
    return head;

}

void gravar(tab head,player p1, player p2){
    tab aux = head;
    FILE *f;
    f=fopen("jogo.bin","wb");

    while (aux->next!=NULL){
        fwrite(aux, sizeof(tabul),1, f);
        aux=aux->next;

    }
    fwrite(&p1,sizeof(player),1,f);
    fwrite(&p2,sizeof(player),1,f);
    fclose(f);

}
/*
void carregar(tab head,player p1, player p2){
    tab aux;
    FILE *f;
    f=fopen("jogo.bin","rb");


}*/