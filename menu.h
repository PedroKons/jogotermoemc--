#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include "database.h"
#include <string.h>

void SetColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode = (bgColor << 4) | textColor;
    SetConsoleTextAttribute(hConsole, colorCode);
}

void PrintCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    cout << string(padding, ' ') << text << endl;
}

void ClearScreen() {
    system("cls");
}

string questionDataBase(){
    string word;
    while(word.size() != 5 && word.size() < 5){
        cout<<"\nDigite a palavra que deseja adionar no banco de palavras: ";
        cin>>word;

        if (word.size() != 5 && word.size() < 5) {
            cout << "A palavra deve ter 5 caracteres. Tente novamente." << endl;
        }
    }
    return word;
}

void removeWord() {
    string word;
    cout << "Digite a palavra que deseja remover: ";
    cin >> word;

    if (removeWordFromFile(word)) {
        cout << "Palavra removida com sucesso." << endl;
    } else {
        cout << "Palavra não encontrada." << endl;
    }
}

void ShowMenu() {
    // Obtém o console e calcula sua largura
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.dwSize.X;

    SetColor(14, 0);  // Amarelo claro no fundo preto
    cout << string(consoleWidth, '=') << endl;
    PrintCentered("MENU PRINCIPAL", consoleWidth);
    cout << string(consoleWidth, '=') << endl;
    PrintCentered("1. Jogar", consoleWidth);
    PrintCentered("2. Adicionar Palavras", consoleWidth);
    PrintCentered("3. Remover Palavras", consoleWidth);
    PrintCentered("4. Exibir Banco de Palavras", consoleWidth);
    PrintCentered("5. Sair", consoleWidth);
    SetColor(7, 0);  // Cor padrão
}

void DynamicsMenu(){
    int option;

    do {
        ShowMenu();
        cout<<"Escolha uma opção (1-5): ";
        cin>>option;

        switch (option) {
            case 1:
                //Jogar
                ClearScreen();
                startGame();
                break;
            case 2:
                //Adicionar Palavras
                ClearScreen();
                    if(writing(questionDataBase()) == true) {
                        cout<<"\nAdicionado com sucesso!\n";
                    } else {
                        cout<<"\nOcorreu algum erro\n";                   }
                break;
            case 3:
                //Remover Palavras
                ClearScreen();
                removeWord();
                break;
            case 4:
                //Exibir Palavras
                ClearScreen();
                toReadDataBase();
                break;
            case 5:
                //Sair
                ClearScreen();
                SetColor(4, 0);
                cout<<"Saindo...";
                break;
            default:
                ClearScreen();
                SetColor(4, 0);
                cout<<endl<<"Escolha inválida. Tente novamente."<<endl;
        }
    } while(option != 5);
}
#endif // MENU_H_INCLUDED
