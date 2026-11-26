#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#define MAX_TIMES 20
#define MAX_PARTIDAS 38
#define TAM_NOME 50

typedef struct {
    int id;
    char nomedotime[TAM_NOME];
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int golsPro;
    int golsContra;
} infTime;

typedef struct {
    int idTimeCasa;
    int idTimeFora;
    int golsCasa;
    int golsFora;
} infPartida;

void cadastrarTimes(infTime APmeusTimes[], int *APtotalTimes);
void registrarPartida(infTime APmeusTimes[], int totalTimes, infPartida APpartidas[], int *APtotalPartidas);
void exibirTabela(infTime APmeusTimes[], int totalTimes);

#endif