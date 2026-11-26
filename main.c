#include <stdio.h>
#include "campeonato.h"
#include "salvadados.h"

int main() {
    int totalTimes = 0;
    int totalPartidas = 0;
    infTime meusTimes[MAX_TIMES];
    infPartida minhasPartidas[MAX_PARTIDAS];
    int opcao;

    carregarDados(meusTimes, &totalTimes, minhasPartidas, &totalPartidas);

    do {
        printf("\nTABELA DE PONTOS CORRIDOS\n");
        printf("1 - Cadastrar novo time\n");
        printf("2 - Registrar partida\n");
        printf("3 - Exibir tabela\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTimes(meusTimes, &totalTimes);
                break;

            case 2:
                registrarPartida(meusTimes, totalTimes, minhasPartidas, &totalPartidas);
                break;

            case 3:
                exibirTabela(meusTimes, totalTimes);
                break;

            case 4:
                salvarDados(meusTimes, totalTimes, minhasPartidas, totalPartidas);
                printf("Saindo...\n");
                break;

            default:
                printf("NÃO EXISTE ESSA OPÇÃO!!\n");
        }
    } while (opcao != 4);

    return 0;
}