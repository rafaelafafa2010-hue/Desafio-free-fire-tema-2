#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[30];
    char tipo[20]; // alimento, arma, ferramenta
    int prioridade; 
} Item;

typedef struct {
    Item itens[MAX];
    int qtd;
} Inventario;

// ---------------------------
// Funções de Inventário
// ---------------------------

void adicionarItem(Inventario *inv, Item item) {
    if (inv->qtd >= MAX) {
        printf("Inventario cheio!\n");
        return;
    }
    inv->itens[inv->qtd] = item;
    inv->qtd++;
}

void removerItem(Inventario *inv, char nome[]) {
    int i, found = -1;

    for (i = 0; i < inv->qtd; i++) {
        if (strcmp(inv->itens[i].nome, nome) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (i = found; i < inv->qtd - 1; i++) {
        inv->itens[i] = inv->itens[i + 1];
    }
    inv->qtd--;

    printf("Item removido com sucesso!\n");
}

void listarItens(Inventario *inv) {
    if (inv->qtd == 0) {
        printf("Inventario vazio.\n");
        return;
    }

    printf("\n--- Itens do Inventario ---\n");
    for (int i = 0; i < inv->qtd; i++) {
        printf("%s (%s) - prioridade %d\n", 
            inv->itens[i].nome, 
            inv->itens[i].tipo,
            inv->itens[i].prioridade);
    }
}

// ---------------------------
// Selection Sort por prioridade
// ---------------------------

void ordenarPorPrioridade(Inventario *inv) {
    int i, j, min;
    Item temp;

    for (i = 0; i < inv->qtd - 1; i++) {
        min = i;
        for (j = i + 1; j < inv->qtd; j++) {
            if (inv->itens[j].prioridade < inv->itens[min].prioridade) {
                min = j;
            }
        }
        temp = inv->itens[i];
        inv->itens[i] = inv->itens[min];
        inv->itens[min] = temp;
    }
}

// ---------------------------
// Busca Binária (por prioridade)
// ---------------------------

int buscaBinaria(Inventario *inv, int prioridade) {
    int inicio = 0, fim = inv->qtd - 1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if (inv->itens[meio].prioridade == prioridade)
            return meio;

        if (inv->itens[meio].prioridade < prioridade)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ---------------------------
// Menu principal
// ---------------------------

int main() {
    Inventario inv;
    inv.qtd = 0;

    int opc;
    Item item;
    char nomeBusca[30];
    int prioBusca;

    do {
        printf("\n===== FREE FIRE INVENTARIO =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar por prioridade\n");
        printf("5 - Buscar item por prioridade\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                printf("Nome do item: ");
                fgets(item.nome, 30, stdin);
                item.nome[strcspn(item.nome, "\n")] = 0;

                printf("Tipo (alimento/arma/ferramenta): ");
                fgets(item.tipo, 20, stdin);
                item.tipo[strcspn(item.tipo, "\n")] = 0;

                printf("Prioridade (1 a 100): ");
                scanf("%d", &item.prioridade);
                getchar();

                adicionarItem(&inv, item);
                break;

            case 2:
                printf("Nome do item para remover: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                removerItem(&inv, nomeBusca);
                break;

            case 3:
                listarItens(&inv);
                break;

            case 4:
                ordenarPorPrioridade(&inv);
                printf("Itens ordenados.\n");
                break;

            case 5:
                printf("Prioridade para buscar: ");
                scanf("%d", &prioBusca);

                ordenarPorPrioridade(&inv);
                int pos = buscaBinaria(&inv, prioBusca);

                if (pos == -1) {
                    printf("Item nao encontrado.\n");
                } else {
                    printf("Item encontrado: %s (%s)\n",
                           inv.itens[pos].nome,
                           inv.itens[pos].tipo);
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opc != 0);

    return 0;
}
