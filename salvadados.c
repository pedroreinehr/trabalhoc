#include <stdio.h>
#include "salvadados.h"

void salvarDados(infTime meusTimes[], int totalTimes, infPartida minhasPartidas[], int totalPartidas) {
    FILE *arquivo = fopen("campeonato.txt", "wb");
    if (arquivo == NULL) {
        printf("ERRO AO SALVAR OS DADOS!\n");
        return;
    }

    fwrite(&totalTimes, sizeof(int), 1, arquivo);
    fwrite(&totalPartidas, sizeof(int), 1, arquivo);
    fwrite(meusTimes, sizeof(infTime), totalTimes, arquivo);
    fwrite(minhasPartidas, sizeof(infPartida), totalPartidas, arquivo);
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

void carregarDados(infTime meusTimes[], int *totalTimes, infPartida minhasPartidas[], int *totalPartidas) {
    FILE *arquivo = fopen("campeonato.txt", "rb");
    if (arquivo == NULL) {
        return;
    }

    fread(totalTimes, sizeof(int), 1, arquivo);
    fread(totalPartidas, sizeof(int), 1, arquivo);
    fread(meusTimes, sizeof(infTime), *totalTimes, arquivo);
    fread(minhasPartidas, sizeof(infPartida), *totalPartidas, arquivo);
    fclose(arquivo);
    printf("Dados anteriores carregados com sucesso!\n");
}