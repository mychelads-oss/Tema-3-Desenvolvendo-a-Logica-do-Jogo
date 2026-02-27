#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_COD 10

// ================= ESTRUTURA =================

typedef struct {
    char codigo[MAX_COD];
    char nomePais[MAX_NOME];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
} Carta;


// ================= UTILITÁRIOS =================

// Remove \n do fgets
void limparEnter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Calcula atributos derivados
void calcularAtributos(Carta *c) {
    c->densidade = c->populacao / c->area;
    c->pibPerCapita = c->pib / c->populacao;
}


// ================= CADASTRO =================

void cadastrarCarta(Carta *c, int indice) {

    printf("\n=========== CARTA %d ===========\n", indice + 1);

    printf("Código: ");
    fgets(c->codigo, MAX_COD, stdin);
    limparEnter(c->codigo);

    printf("Nome do país: ");
    fgets(c->nomePais, MAX_NOME, stdin);
    limparEnter(c->nomePais);

    printf("População: ");
    scanf("%lu", &c->populacao);

    printf("Área: ");
    scanf("%f", &c->area);

    printf("PIB: ");
    scanf("%f", &c->pib);

    printf("Pontos turísticos: ");
    scanf("%d", &c->pontosTuristicos);

    getchar(); // limpar buffer

    calcularAtributos(c);
}


// ================= EXIBIÇÃO =================

void exibirCarta(const Carta *c) {

    printf("\n----------------------------------\n");
    printf("Carta: %s - %s\n", c->codigo, c->nomePais);
    printf("População: %lu\n", c->populacao);
    printf("Área: %.2f\n", c->area);
    printf("PIB: %.2f\n", c->pib);
    printf("Pontos Turísticos: %d\n", c->pontosTuristicos);
    printf("Densidade: %.2f\n", c->densidade);
    printf("PIB per Capita: %.2f\n", c->pibPerCapita);
    printf("----------------------------------\n");
}


// ================= COMPARAÇÃO =================

void compararCartas(const Carta *c1, const Carta *c2) {

    int opcao;

    printf("\n******** MENU ********\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade (menor vence)\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    printf("\nComparando %s VS %s\n", c1->nomePais, c2->nomePais);

    switch(opcao) {

        case 1:
            printf("Vencedor: %s\n",
                (c1->populacao > c2->populacao) ? c1->nomePais :
                (c1->populacao < c2->populacao) ? c2->nomePais : "Empate");
            break;

        case 2:
            printf("Vencedor: %s\n",
                (c1->area > c2->area) ? c1->nomePais :
                (c1->area < c2->area) ? c2->nomePais : "Empate");
            break;

        case 3:
            printf("Vencedor: %s\n",
                (c1->pib > c2->pib) ? c1->nomePais :
                (c1->pib < c2->pib) ? c2->nomePais : "Empate");
            break;

        case 4:
            printf("Vencedor: %s\n",
                (c1->pontosTuristicos > c2->pontosTuristicos) ? c1->nomePais :
                (c1->pontosTuristicos < c2->pontosTuristicos) ? c2->nomePais : "Empate");
            break;

        case 5:
            printf("Vencedor: %s\n",
                (c1->densidade < c2->densidade) ? c1->nomePais :
                (c1->densidade > c2->densidade) ? c2->nomePais : "Empate");
            break;

        default:
            printf("Opção inválida\n");
    }
}


// ================= ARQUIVO =================

void salvarEmArquivo(const Carta *cartas, int quantidade) {

    FILE *arquivo = fopen("cartas.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {

        fprintf(arquivo,
            "Carta: %s - %s\n"
            "População: %lu\n"
            "Área: %.2f\n"
            "PIB: %.2f\n"
            "Pontos Turísticos: %d\n"
            "Densidade: %.2f\n"
            "PIB per Capita: %.2f\n"
            "-----------------------------\n",
            cartas[i].codigo,
            cartas[i].nomePais,
            cartas[i].populacao,
            cartas[i].area,
            cartas[i].pib,
            cartas[i].pontosTuristicos,
            cartas[i].densidade,
            cartas[i].pibPerCapita
        );
    }

    fclose(arquivo);
    printf("\nDados salvos em cartas.txt com sucesso!\n");
}


// ================= MAIN =================

int main() {

    int quantidade;

    printf("Quantas cartas deseja cadastrar? ");
    scanf("%d", &quantidade);
    getchar();

    // ALOCAÇÃO DINÂMICA
    Carta *cartas = (Carta *) malloc(quantidade * sizeof(Carta));

    if (cartas == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++) {
        cadastrarCarta(&cartas[i], i);
    }

    for (int i = 0; i < quantidade; i++) {
        exibirCarta(&cartas[i]);
    }

    if (quantidade >= 2) {
        compararCartas(&cartas[0], &cartas[1]);
    }

    salvarEmArquivo(cartas, quantidade);

    // LIBERA MEMÓRIA
    free(cartas);

    printf("\nPrograma finalizado com sucesso.\n");

    return 0;
}
