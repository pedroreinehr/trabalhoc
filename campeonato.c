#include <stdio.h>
#include <string.h>
#include "campeonato.h"

void cadastrarTimes(infTime APmeusTimes[], int *APtotalTimes) {
    if (*APtotalTimes >= MAX_TIMES) {
        printf("Numero máximo de times criados!\n");
        return;
    }
    printf("\nCadastre o seu Time\n");
    printf("Informe o ID escolhido: ");
    scanf("%d", &APmeusTimes[*APtotalTimes].id);

    while (getchar() != '\n');

    printf("Informe o nome escolhido: ");
    fgets(APmeusTimes[*APtotalTimes].nomedotime, TAM_NOME, stdin);

    APmeusTimes[*APtotalTimes].nomedotime[strcspn(APmeusTimes[*APtotalTimes].nomedotime, "\n")] = '\0';

    APmeusTimes[*APtotalTimes].pontos = 0;
    APmeusTimes[*APtotalTimes].vitorias = 0;
    APmeusTimes[*APtotalTimes].empates = 0;
    APmeusTimes[*APtotalTimes].derrotas = 0;
    APmeusTimes[*APtotalTimes].golsPro = 0;
    APmeusTimes[*APtotalTimes].golsContra = 0;

    (*APtotalTimes)++;
    printf("Time cadastrado com sucesso!!\n");
}

void registrarPartida(infTime APmeusTimes[], int totalTimes, infPartida APpartidas[], int *APtotalPartidas) {
    if (totalTimes < 2) {
        printf("Você precisa de pelo menos dois times cadastrados para registrar uma partida!!\n");
        return;
    }
    if (*APtotalPartidas >= MAX_PARTIDAS) {
        printf("Número máximo de partidas atingido!\n");
        return;
    }

    int idCasa, idFora;
    int numCasa = -1, numFora = -1;

    printf("\nRegistre sua partida\n");
    printf("Informe o ID do time da casa: ");
    scanf("%d", &idCasa);

    printf("Informe o ID do time de fora: ");
    scanf("%d", &idFora);

    if (idCasa == idFora) {
        printf("Um time não pode jogar contra si mesmo!!\n");
        return;
    }

    for (int i = 0; i < totalTimes; i++) {
        if (APmeusTimes[i].id == idCasa) {
            numCasa = i;
        }
        if (APmeusTimes[i].id == idFora) {
            numFora = i;
        }
    }

    if (numCasa == -1 || numFora == -1) {
        printf("ERRO!!\n");
        printf("Um ou ambos os IDs não foram encontrados!!\n");
        printf("Cadastre-os primeiro.\n");
        return;
    }

    printf("Gols do(a) %s: ", APmeusTimes[numCasa].nomedotime);
    scanf("%d", &APpartidas[*APtotalPartidas].golsCasa);

    printf("Gols do(a) %s: ", APmeusTimes[numFora].nomedotime);
    scanf("%d", &APpartidas[*APtotalPartidas].golsFora);

    APpartidas[*APtotalPartidas].idTimeCasa = idCasa;
    APpartidas[*APtotalPartidas].idTimeFora = idFora;

    int gCasa = APpartidas[*APtotalPartidas].golsCasa;
    int gFora = APpartidas[*APtotalPartidas].golsFora;

    APmeusTimes[numCasa].golsPro += gCasa;
    APmeusTimes[numCasa].golsContra += gFora;
    APmeusTimes[numFora].golsPro += gFora;
    APmeusTimes[numFora].golsContra += gCasa;

    if (gCasa > gFora) {
        APmeusTimes[numCasa].vitorias++;
        APmeusTimes[numCasa].pontos += 3;
        APmeusTimes[numFora].derrotas++;
    } else if (gCasa < gFora) {
        APmeusTimes[numFora].vitorias++;
        APmeusTimes[numFora].pontos += 3;
        APmeusTimes[numCasa].derrotas++;
    } else {
        APmeusTimes[numCasa].empates++;
        APmeusTimes[numCasa].pontos += 1;
        APmeusTimes[numFora].empates++;
        APmeusTimes[numFora].pontos += 1;
    }

    (*APtotalPartidas)++;
    printf("Partida registrada com sucesso!\n");
}

void exibirTabela(infTime APmeusTimes[], int totalTimes) {
    if (totalTimes == 0) {
        printf("\nNenhum time cadastrado ainda!\n");
        return;
    }

    for (int i = 0; i < totalTimes - 1; i++) {
        for (int j = 0; j < totalTimes - i - 1; j++) {
            int sgJ = APmeusTimes[j].golsPro - APmeusTimes[j].golsContra;
            int sgNext = APmeusTimes[j + 1].golsPro - APmeusTimes[j + 1].golsContra;

            int trocar = 0;
            if (APmeusTimes[j].pontos < APmeusTimes[j + 1].pontos) {
                trocar = 1;
            } else if (APmeusTimes[j].pontos == APmeusTimes[j + 1].pontos) {
                if (sgJ < sgNext) {
                    trocar = 1;
                } else if (sgJ == sgNext) {
                    if (APmeusTimes[j].golsPro < APmeusTimes[j + 1].golsPro) {
                        trocar = 1;
                    }
                }
            }

            if (trocar) {
                infTime temp = APmeusTimes[j];
                APmeusTimes[j] = APmeusTimes[j + 1];
                APmeusTimes[j + 1] = temp;
            }
        }
    }

    printf("\n--- TABELA DE CLASSIFICACAO ---\n");
    printf("ID | Nome                | Pts | V | E | D | GP | GC | SG\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < totalTimes; i++) {
        int sg = APmeusTimes[i].golsPro - APmeusTimes[i].golsContra;
        printf("%2d | %-19s | %3d | %d | %d | %d | %2d | %2d | %2d\n",
            APmeusTimes[i].id,
            APmeusTimes[i].nomedotime,
            APmeusTimes[i].pontos,
            APmeusTimes[i].vitorias,
            APmeusTimes[i].empates,
            APmeusTimes[i].derrotas,
            APmeusTimes[i].golsPro,
            APmeusTimes[i].golsContra,
            sg);
    }
}