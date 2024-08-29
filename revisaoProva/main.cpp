#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

//github Gabriel-sardine
struct Ativo {
    string ticket;
    int quantidade;
    double preco_medio;

    Ativo(string t, int q, double p) : ticket(t), quantidade(q), preco_medio(p) {}
};


void registrarCompra(vector<Ativo>& carteira) {
    string ticket;
    int quantidade;
    double preco_compra;

    cout << "Digite o ticket da empresa (max. 6 letras): ";
    cin >> ticket;
    cout << "Digite a quantidade comprada: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da compra: ";
    cin >> preco_compra;


    auto it = find_if(carteira.begin(), carteira.end(), [&](const Ativo& a) {
        return a.ticket == ticket;
    });

    if (it != carteira.end()) {

        double preco_medio_atual = it->preco_medio;
        int quantidade_atual = it->quantidade;
        it->preco_medio = ((preco_medio_atual * quantidade_atual) + (preco_compra * quantidade)) / (quantidade_atual + quantidade);
        it->quantidade += quantidade;
    } else {
        carteira.push_back(Ativo(ticket, quantidade, preco_compra));
    }
}


void registrarVenda(vector<Ativo>& carteira) {
    string ticket;
    int quantidade;
    double preco_venda;

    cout << "Digite o ticket da empresa (max. 6 letras): ";
    cin >> ticket;
    cout << "Digite a quantidade vendida: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da venda: ";
    cin >> preco_venda;


    auto it = find_if(carteira.begin(), carteira.end(), [&](const Ativo& a) {
        return a.ticket == ticket;
    });

    if (it != carteira.end()) {
        if (it->quantidade >= quantidade) {
            it->quantidade -= quantidade;
            if (it->quantidade == 0) {
                carteira.erase(it);
            }
        } else {
            cout << "Quantidade para venda maior do que a quantidade disponivel!" << endl;
        }
    } else {
        cout << "Ativo nao encontrado na carteira!" << endl;
    }
}


Ativo* buscarAtivo(const vector<Ativo>& carteira, const string& ticket, int inicio, int fim) {
    if (inicio > fim) return nullptr;

    int meio = inicio + (fim - inicio) / 2;

    if (carteira[meio].ticket == ticket) {
        return const_cast<Ativo*>(&carteira[meio]);
    } else if (carteira[meio].ticket < ticket) {
        return buscarAtivo(carteira, ticket, meio + 1, fim);
    } else {
        return buscarAtivo(carteira, ticket, inicio, meio - 1);
    }
}


void verSaldoAtivo(const vector<Ativo>& carteira) {
    string ticket;
    cout << "Digite o ticket da empresa (max. 6 letras): ";
    cin >> ticket;


    vector<Ativo> carteiraOrdenada = carteira;
    sort(carteiraOrdenada.begin(), carteiraOrdenada.end(), [](const Ativo& a, const Ativo& b) {
        return a.ticket < b.ticket;
    });

    Ativo* ativo = buscarAtivo(carteiraOrdenada, ticket, 0, carteiraOrdenada.size() - 1);
    if (ativo) {
        cout << "Ticket: " << ativo->ticket << endl;
        cout << "Quantidade: " << ativo->quantidade << endl;
        cout << "Preço medio: " << fixed << setprecision(2) << ativo->preco_medio << endl;
    } else {
        cout << "Ativo nao encontrado na carteira!" << endl;
    }
}


void listarPatrimonio(const vector<Ativo>& carteira) {
    cout << "Patrimonio:" << endl;
    for (const auto& ativo : carteira) {
        cout << "Ticket: " << ativo.ticket << endl;
        cout << "Quantidade: " << ativo.quantidade << endl;
        cout << "Preco medio: " << fixed << setprecision(2) << ativo.preco_medio << endl;
        cout << "------------------" << endl;
    }
}


int main() {
    vector<Ativo> carteira;
    int opcao;

    do {
        cout << "Menu:" << endl;
        cout << "1. Registrar compra" << endl;
        cout << "2. Registrar venda" << endl;
        cout << "3. Ver o saldo de um ativo (Busca por Ticket)" << endl;
        cout << "4. Listar Patrimonio" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra(carteira);
                break;
            case 2:
                registrarVenda(carteira);
                break;
            case 3:
                verSaldoAtivo(carteira);
                break;
            case 4:
                listarPatrimonio(carteira);
                break;
            case 5:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
        }
    } while (opcao != 5);

    return 0;
}
