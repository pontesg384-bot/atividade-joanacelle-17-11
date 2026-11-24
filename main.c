#include <stdio.h>
#include <stdlib.h>
#include "meu_banco.h"

int main() {

    int opcao;
    int bancoAberto = 0;

    do {

        printf("\n===== Carteira digital =====\n");
        printf("1 - Abrir banco\n");
        printf("2 - Consultar historico\n");
        printf("3 - Efetuar sorteio\n");
        printf("4 - Solicitar emprestimo\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                if (!bancoAberto)
                    bancoAberto = abrirBanco();
                else
                    printf("O banco ja esta aberto!\n");
                break;

            case 2:
                if (bancoAberto)
                    consultarHistorico();
                else
                    printf("Abra o banco primeiro!\n");
                break;

            case 3:
                if (bancoAberto)
                    efetuarSorteio();
                else
                    printf("Abra o banco primeiro!\n");
                break;

            case 4:
                if (bancoAberto)
                    solicitarEmprestimo();
                else
                    printf("Abra o banco primeiro!\n");
                break;

            case 5:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}