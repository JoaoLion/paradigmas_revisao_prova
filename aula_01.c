#include <stdio.h>
#include <string.h>
#define MAX_MEDICAMENTOS 1000

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Medicamento;

Medicamento estoque[MAX_MEDICAMENTOS];
int totalMedicamentos = 0;

void cadastrarMedicamento();
void listarMedicamentos();
void realizarVenda();


int main() {
    int opcao;

    do {
        printf("=== Sistema de Farmacia ===\n");
        printf("1 - Cadastrar medicamento\n");
        printf("2 - Listar medicamentos\n");
        printf("3 - Realizar venda\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarMedicamento();
                break;
            case 2:
                listarMedicamentos();
                break;
            case 3:
                realizarVenda();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n\n");
        }

    } while (opcao != 0);

    return 0;
}

void cadastrarMedicamento() {
    if (totalMedicamentos >= MAX_MEDICAMENTOS) {
        printf("Estoque cheio!\n");
        return;
    }

    Medicamento m;

    printf("Nome do medicamento: ");
    scanf(" %[^\n]", m.nome);

    printf("Preco: ");
    scanf("%f", &m.preco);

    printf("Quantidade em estoque: ");
    scanf("%d", &m.quantidade);

    estoque[totalMedicamentos] = m;
    totalMedicamentos++;

    printf("Medicamento cadastrado com sucesso!\n\n");
}

// Função para listar medicamentos
void listarMedicamentos() {
    int i;
    printf("\n--- Lista de Medicamentos ---\n");
    for (i = 0; i < totalMedicamentos; i++) {
        printf("%d - %s | Preco: R$ %.2f | Estoque: %d\n",
               i, estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }
    printf("\n");
}

// Função para realizar venda
void realizarVenda() {
    int indice, qtd;

    listarMedicamentos();

    printf("Escolha o indice do medicamento: ");
    scanf("%d", &indice);

    if (indice < 0 || indice >= totalMedicamentos) {
        printf("Medicamento invalido!\n\n");
        return;
    }

    printf("Quantidade a vender: ");
    scanf("%d", &qtd);

    // Regra de ouro: não permitir estoque negativo
    if (qtd > estoque[indice].quantidade ) {
        printf("Erro: estoque insuficiente!\n\n");
        return;
    }
    if (qtd < 0 ) {
        printf("Erro: Valor negativo!\n\n");
        return;
    }

    estoque[indice].quantidade -= qtd;

    printf("Venda realizada com sucesso!\n\n");
}
