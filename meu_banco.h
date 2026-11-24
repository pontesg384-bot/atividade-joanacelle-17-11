#ifndef MEU_BANCO_H
#define MEU_BANCO_H

typedef struct {
    int numero;
    int tipo;
    float saldo;
    char historico[10][100];
    int qtdHistorico;
} Conta;

typedef struct {
    char nome[50];
    Conta contas[3];
    int qtdContas;
    int emprestimo;
} Cliente;

int abrirBanco();
void consultarHistorico();
void efetuarSorteio();
void solicitarEmprestimo();

#endif