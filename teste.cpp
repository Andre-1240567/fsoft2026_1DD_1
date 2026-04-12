#include <iostream>
#include <string>
using namespace std;

// Classe Enfermeira
class Enfermeira {
public:
    string nome;

    Enfermeira(string n) {
        nome = n;
    }

    void aplicarVacina() {
        cout << "Enfermeira " << nome << " aplicou a vacina.\n";
    }
};

// Classe Utente
class Utente {
public:
    string nome;
    int idade;

    Utente(string n, int i) {
        nome = n;
        idade = i;
    }

    void mostrarInfo() {
        cout << "Utente: " << nome << ", Idade: " << idade << endl;
    }
};

// Classe Vacina
class Vacina {
public:
    string tipo;

    Vacina(string t) {
        tipo = t;
    }

    void mostrarVacina() {
        cout << "Vacina do tipo: " << tipo << endl;
    }
};

int main() {
    // Criar objetos
    Enfermeira enf("Ana");
    Utente ut("Joao", 25);
    Vacina vac("COVID-19");

    // Usar objetos
    ut.mostrarInfo();
    vac.mostrarVacina();
    enf.aplicarVacina();

    return 0;
}
