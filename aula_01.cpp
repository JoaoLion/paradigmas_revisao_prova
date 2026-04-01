#include <iostream>
#include <vector>
using namespace std;

// ================= CLASSE BASE =================
class Medicamento {
protected:
    string nome;
    float preco;
    int quantidade;

public:
    Medicamento(string n, float p, int q) {
        nome = n;
        preco = p;
        quantidade = q;
    }

    virtual void vender(int qtd) {
        if (qtd <= 0) {
            cout << "Erro: quantidade invalida!\n\n";
            return;
        }

        if (qtd > quantidade) {
            cout << "Erro: estoque insuficiente!\n\n";
            return;
        }

        quantidade -= qtd;
        cout << "Venda realizada! Total: R$ " << preco * qtd << "\n\n";
    }

    virtual void exibir(int indice) {
        cout << indice << " - " << nome
             << " | Preco: R$ " << preco
             << " | Estoque: " << quantidade;
    }

    virtual ~Medicamento() {}
};

// ================= CLASSE FILHA - COMUM =================
class MedicamentoComum : public Medicamento {
public:
    MedicamentoComum(string n, float p, int q)
        : Medicamento(n, p, q) {}

    void exibir(int indice) override {
        Medicamento::exibir(indice);
        cout << " | Tipo: Comum\n";
    }
};

// ================= CLASSE FILHA - GENERICO =================
class MedicamentoGenerico : public Medicamento {
public:
    MedicamentoGenerico(string n, float p, int q)
        : Medicamento(n, p, q) {}

    void vender(int qtd) override {
        if (qtd <= 0) {
            cout << "Erro: quantidade invalida!\n\n";
            return;
        }

        if (qtd > quantidade) {
            cout << "Erro: estoque insuficiente!\n\n";
            return;
        }

        quantidade -= qtd;

        float desconto = preco * 0.2; // 20% desconto
        float total = (preco - desconto) * qtd;

        cout << "Venda realizada (Generico com 20% desconto)!\n";
        cout << "Total: R$ " << total << "\n\n";
    }

    void exibir(int indice) override {
        Medicamento::exibir(indice);
        cout << " | Tipo: Generico\n";
    }
};

// ================= ESTOQUE =================
vector<Medicamento*> estoque;

// ================= FUNCOES =================
void cadastrarMedicamento() {
    string nome;
    float preco;
    int quantidade, tipo;

    cout << "Nome do medicamento: ";
    cin >> ws;
    getline(cin, nome);

    cout << "Preco: ";
    cin >> preco;

    cout << "Quantidade: ";
    cin >> quantidade;

    cout << "Tipo (1 - Comum | 2 - Generico): ";
    cin >> tipo;

    if (tipo == 1) {
        estoque.push_back(new MedicamentoComum(nome, preco, quantidade));
    } else if (tipo == 2) {
        estoque.push_back(new MedicamentoGenerico(nome, preco, quantidade));
    } else {
        cout << "Tipo invalido!\n\n";
        return;
    }

    cout << "Medicamento cadastrado com sucesso!\n\n";
}

void listarMedicamentos() {
    cout << "\n--- Lista de Medicamentos ---\n";

    if (estoque.empty()) {
        cout << "Nenhum medicamento cadastrado.\n\n";
        return;
    }

    for (int i = 0; i < estoque.size(); i++) {
        estoque[i]->exibir(i);
    }

    cout << "\n";
}

void realizarVenda() {
    int indice, qtd;

    listarMedicamentos();

    if (estoque.empty()) return;

    cout << "Escolha o indice do medicamento: ";
    cin >> indice;

    if (indice < 0 || indice >= estoque.size()) {
        cout << "Medicamento invalido!\n\n";
        return;
    }

    cout << "Quantidade a vender: ";
    cin >> qtd;

    estoque[indice]->vender(qtd);
}

// ================= MAIN =================
int main() {
    int opcao;

    do {
        cout << "=== Sistema de Farmacia (POO) ===\n";
        cout << "1 - Cadastrar medicamento\n";
        cout << "2 - Listar medicamentos\n";
        cout << "3 - Realizar venda\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

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
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n\n";
        }

    } while (opcao != 0);

    // Liberar memoria
    for (auto m : estoque) {
        delete m;
    }

    return 0;
}
