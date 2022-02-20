//
// Created by miner on 19/04/2021.
//

#ifndef TRABALHO_P_GAME_H
#define TRABALHO_P_GAME_H




typedef struct players{
    int jogador;
    int pedra;
    int addLinhaColuna;
} player;




typedef struct tabuleiro tabul,*tab;

struct tabuleiro
{
    int turno;
    int linha;
    int coluna;
    char **matriz;
    tabul* next;
};







void menu();


void startPL(player *pl, int id);
void startgame(tabul *t);
void mostratabuleiro(tabul *t);
int updateTab(tabul *t,int l,int c);
int updateTabPedra(player *p,tabul *t,int l,int c);
void addLC(tabul *t,player *p);
int addL(tabul *t,player *p);
int addC(tabul *t,player *p);
void reverJogadas(tabul *tab);
int verificaVitoria(tabul *t);
void turno(int turn);

void gravar(tab head,player p1, player p2);



tab insereTabuleiro(tab atual,tab head);

#endif //TRABALHO_P_GAME_H