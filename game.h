#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "list_dynamics.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

void toRead(TLista<string> &word_list) {
    // Fun��o para ler o arquivo e jogar as strings para dentro da lista encadeada
    ifstream inFile("banco.txt"); // Diz qual arquivo devo mexer
    string line; // Vari�vel para navegar entre as linhas
    if(inFile.is_open()) { // Abre o arquivo
        while(getline(inFile, line)) { // La�o para percorrer cada linha
            insere_fim(word_list, line); // Cada linha � adicionada na lista
        }
        inFile.close(); // Fecha o arquivo
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }
}

int question() {
    // Fun��o que pergunta com quantas tabelas quer jogar
    int amountOfWords;
    cout << "\nCom quantas palavras voc� deseja jogar simultaneamente? ";
    cin >> amountOfWords;
    return amountOfWords; // Retorna o valor int de tabelas
}

string getRandomElement(TLista<string> &word_list, TLista<string> &usedWords) {
    // Fun��o que gera uma string aleat�ria da lista
    srand(static_cast<unsigned int>(time(0))); // Fun��o srand para gerar n�meros aleat�rios
    int count = retorna_comprimento(word_list); // Vari�vel que cont�m o comprimento da lista

    string randomWord; // Vari�vel que armazena a string aleat�ria
    bool alreadyUsed; // Vari�vel que vai nos dizer se essa palavra j� foi usada

    do {
        int randomIndex = rand() % count; // Gera um �ndice aleat�rio
        TElemento<string> *nav = word_list.inicio; // Navega at� o elemento da lista
        for (int i = 0; i < randomIndex; ++i) {
            nav = nav->proximo;
        }
        randomWord = nav->dado; // Pega a palavra aleat�ria

        // Verificar se a palavra j� foi usada
        alreadyUsed = busca_dado(usedWords, randomWord);
    } while (alreadyUsed); // Continua at� encontrar uma palavra que ainda n�o foi usada

    insere_fim(usedWords, randomWord); // Marca a palavra como usada
    return randomWord;
}

void compareWords(const string &userWord, const string &randomWord, char **tableDataBase, int currentAttempt, int columns) {
    // Verifica cada caractere da palavra do usu�rio
    for (int i = 0; i < userWord.size(); i++) {
        // Loop para percorrer todos os caracteres da palavra do usu�rio
        if (i < columns) {
            // Certifica-se de que a posi��o i est� dentro do limite de colunas da tabela
            if (userWord[i] == randomWord[i]) {
                // Verifica se o caractere atual da palavra do usu�rio est� na mesma posi��o da palavra aleat�ria
                // Letra correta na posi��o correta (verde)
                tableDataBase[currentAttempt][i] = userWord[i];
                // Se a letra est� correta e na posi��o certa, ela � inserida na tabela
            } else if (randomWord.find(userWord[i]) != string::npos) {
                // Verifica se o caractere da palavra do usu�rio existe em qualquer outra posi��o na palavra aleat�ria
                // `string::npos` indica que o caractere n�o foi encontrado; se for diferente, foi encontrado em outra posi��o
                // Letra existe, mas na posi��o errada (amarelo)
                tableDataBase[currentAttempt][i] = userWord[i];
                // A letra est� na palavra, mas na posi��o errada; marca com um estado intermedi�rio (amarelo)
            } else {
                // Se o caractere n�o existe na palavra aleat�ria
                // Letra n�o existente (vermelho)
                tableDataBase[currentAttempt][i] = userWord[i];
                // Marca a letra como incorreta (vermelho), pois ela n�o existe na palavra aleat�ria
            }
        }
    }
}

void table(int rows, int columns, char **tableDataBase, int currentAttempt, const string &userWord, const string &randomWord) {
    // Preenche a tabela com a palavra do usu�rio na linha correspondente
    for (int j = 0; j < columns; j++) {
        if (j < userWord.size()) {
            tableDataBase[currentAttempt][j] = userWord[j];
        } else {
            tableDataBase[currentAttempt][j] = '*';  // Mant�m os espa�os n�o usados com '*'
        }
    }

    // Atualiza a tabela com o esquema de cores baseado na compara��o
    compareWords(userWord, randomWord, tableDataBase, currentAttempt, columns);

    // Imprime a tabela atualizada
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i > currentAttempt) {
                cout << "* ";  // Preenche com asteriscos as tentativas n�o realizadas
            } else {
                // Verificar o esquema de cores de acordo com a tentativa
                if (tableDataBase[i][j] == randomWord[j]) {
                    cout << "\033[1;32m" << tableDataBase[i][j] << "\033[0m "; // Verde
                } else if (randomWord.find(tableDataBase[i][j]) != string::npos && tableDataBase[i][j] != randomWord[j]) {
                    cout << "\033[1;33m" << tableDataBase[i][j] << "\033[0m "; // Amarelo
                } else {
                    cout << "\033[1;31m" << tableDataBase[i][j] << "\033[0m "; // Vermelho
                }
            }
        }
        cout << endl;
    }
}

void startGame() { // funcao principal
    TLista<string> word_list; // lista que vai conter os dados do arquivo
    inicializar_lista(word_list); // inicia lista
    toRead(word_list); // L� a lista de palavras do arquivo

    int amountOfWords = question(); // Pergunta quantas tabelas o jogador deseja jogar

    // Define o n�mero de tentativas com base no n�mero de tabelas
    int maxAttempts = 6 + (amountOfWords - 1) * 2; // 6 tentativas para 1 tabela, 8 para 2, etc.
    int rows = maxAttempts;
    int columns = 5;

    // Aloca mem�ria para v�rias tabelas
    char ***tableDataBases = new char**[amountOfWords]; // Cria um array de tabelas
    for (int t = 0; t < amountOfWords; t++) {
        tableDataBases[t] = new char*[rows]; // Cada tabela tem v�rias linhas
        for (int i = 0; i < rows; i++) {
            tableDataBases[t][i] = new char[columns]; // Cada linha tem 5 colunas
            for (int j = 0; j < columns; j++) {
                tableDataBases[t][i][j] = '*'; // Inicializa a tabela com '*'
            }
        }
    }

    TLista<string> usedWords; // Lista para armazenar palavras j� usadas
    inicializar_lista(usedWords);

    // Gera palavras aleat�rias para cada tabela
    string *randomWords = new string[amountOfWords];
    for (int t = 0; t < amountOfWords; t++) {
        randomWords[t] = getRandomElement(word_list, usedWords);
    }

    int attempts = 0;
    bool allSolved = false;
    bool *solved = new bool[amountOfWords]{false}; // Array para marcar se uma tabela foi resolvida

    do {
        // Exibe o n�mero de tentativas restantes
        int attemptsLeft = maxAttempts - attempts;
        cout << "\nTentativas restantes: " << attemptsLeft << endl;

        // Entrada do usu�rio
        string userWord;
        while (userWord.size() != 5) {
            cout << "Digite uma palavra: ";
            cin >> userWord;

            if (userWord.size() != 5)
                cout << "\nA palavra deve conter 5 caracteres\n";
        }
        system("cls");
        // Atualiza e exibe todas as tabelas
        for (int t = 0; t < amountOfWords; t++) {
            if (!solved[t]) {  // S� atualiza se a tabela ainda n�o foi resolvida
                cout<<"Palavra Respostas: "<<randomWords[t];
                cout << "\nTabela " << (t + 1) << ":" << endl;
                table(rows, columns, tableDataBases[t], attempts, userWord, randomWords[t]);

                if (userWord == randomWords[t]) { // Verifica se o usu�rio acertou a palavra
                    solved[t] = true; // Marca a tabela como resolvida
                    cout << "Voc� acertou a tabela " << (t + 1) << "!" << endl;
                }
            }
        }

        // Verifica se todas as tabelas foram resolvidas
        allSolved = true;
        for (int t = 0; t < amountOfWords; t++) {
            if (!solved[t]) {
                allSolved = false;
                break;
            }
        }

        attempts++;

    } while (!allSolved && attempts < maxAttempts); // Continua at� resolver todas ou atingir o limite de tentativas

    // Exibe a mensagem final
    if (allSolved) {
        cout << "Parab�ns! Voc� acertou todas as tabelas!" << endl;
    } else {
        for (int t = 0; t < amountOfWords; t++) {
            if (!solved[t]) {
                cout << "Voc� perdeu! A palavra da tabela " << (t + 1) << " era: " << randomWords[t] << endl;
            }
        }
    }

    // Libera a mem�ria
    for (int t = 0; t < amountOfWords; t++) {
        for (int i = 0; i < rows; i++) {
            delete[] tableDataBases[t][i];
        }
        delete[] tableDataBases[t];
    }
    delete[] tableDataBases;
    delete[] randomWords;
    delete[] solved;
}

#endif // GAME_H_INCLUDED
