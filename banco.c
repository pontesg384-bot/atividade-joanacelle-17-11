#include <stdio.h>
#include <stdlib.h>
#include "meu_banco.h"

Cliente clientes[100];
int qtdClientes = 0;
int numeroConta = 1000;

int abrirBanco() {
    int n, tipo, qtd;

    printf("Quantidade de clientes: ");
    scanf("%d", &n);

    if (n < 1 || n > 100)
        return 0;

    qtdClientes = n;

    for (int i = 0; i < n; i++) {

        printf("Nome do cliente: ");
        scanf("%49s", clientes[i].nome);

        clientes[i].qtdContas = 0;
        clientes[i].emprestimo = 0;

        printf("Quantidade de contas: ");
        scanf("%d", &qtd);

        if (qtd < 1 || qtd > 3)
            qtd = 1;

        for (int j = 0; j < qtd; j++) {

            printf("\n1 - Corrente\n");
            printf("2 - Salario\n");
            printf("3 - Poupanca\n");
            printf("Escolha: ");
            scanf("%d", &tipo);

            if (tipo < 1 || tipo > 3) {
                printf("Tipo invalido!\n");
                j--;
                continue;
            }

            int permitido = 1;

            for (int k = 0; k < clientes[i].qtdContas; k++) {

                if (clientes[i].contas[k].tipo == tipo ||
                    (clientes[i].contas[k].tipo == 1 && tipo == 2) ||
                    (clientes[i].contas[k].tipo == 2 && tipo == 1)) {
                    permitido = 0;
                }
            }

            if (!permitido) {
                printf("Conta nao permitida!\n");
                j--;
                continue;
            }

            Conta *c = &clientes[i].contas[clientes[i].qtdContas];

            (*c).numero = numeroConta++;
            (*c).tipo = tipo;
            (*c).qtdHistorico = 0;

            printf("Saldo inicial: ");
            scanf("%f", &(*c).saldo);

            sprintf((*c).historico[0], "Conta aberta. Saldo: %.2f", (*c).saldo);
            (*c).qtdHistorico = 1;

            clientes[i].qtdContas++;

            printf("Numero da conta: %04d-%02d\n", (*c).numero, tipo);
        }
    }

    return 1;
}

void consultarHistorico() {
    int numero, tipo, achou = 0;

    printf("Numero da conta: ");
    scanf("%d", &numero);

    printf("Tipo da conta: ");
    scanf("%d", &tipo);

    for (int i = 0; i < qtdClientes; i++) {
        for (int j = 0; j < clientes[i].qtdContas; j++) {

            Conta *c = &clientes[i].contas[j];

            if ((*c).numero == numero && (*c).tipo == tipo) {

                achou = 1;

                printf("\nCliente: %s\n", clientes[i].nome);
                printf("Saldo: R$ %.2f\n", (*c).saldo);

                for (int k = 0; k < (*c).qtdHistorico; k++)
                    printf("%s\n", (*c).historico[k]);
            }
        }
    }

    if (!achou)
        printf("Conta nao encontrada!\n");
}

void efetuarSorteio() {

    if (qtdClientes == 0) {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }

    int sorteado = rand() % qtdClientes;

    printf("Cliente sorteado: %s\n", clientes[sorteado].nome);
}

void solicitarEmprestimo() {
    int n, corrente = -1, poupanca = 0;
    float total = 0, limite, valor;

    for (int i = 0; i < qtdClientes; i++)
        printf("%d - %s\n", i + 1, clientes[i].nome);

    printf("Escolha o cliente: ");
    scanf("%d", &n);

    if (n < 1 || n > qtdClientes)
        return;

    Cliente *c = &clientes[n - 1];

    if ((*c).emprestimo == 1) {
        printf("Cliente ja possui emprestimo!\n");
        return;
    }

    for (int i = 0; i < (*c).qtdContas; i++) {

        total += (*c).contas[i].saldo;

        if ((*c).contas[i].tipo == 1)
            corrente = i;

        if ((*c).contas[i].tipo == 3)
            poupanca = 1;
    }

    if (corrente == -1 || poupanca == 0) {
        printf("Cliente precisa de conta corrente e poupanca!\n");
        return;
    }

    limite = total * 2.5;

    printf("Limite: R$ %.2f\n", limite);
    printf("Valor do emprestimo: ");
    scanf("%f", &valor);

    if (valor <= 0 || valor > limite) {
        printf("Valor invalido!\n");
        return;
    }

    (*c).contas[corrente].saldo += valor;
    (*c).emprestimo = 1;

    if ((*c).contas[corrente].qtdHistorico < 10) {

        sprintf((*c).contas[corrente].historico[
            (*c).contas[corrente].qtdHistorico],
            "Emprestimo: %.2f", valor);

        (*c).contas[corrente].qtdHistorico++;
    }

    printf("Emprestimo aprovado!\n");
}