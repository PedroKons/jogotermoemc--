#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

bool writing(string word){
    ofstream outFile("banco.txt", ios::app);
    if (outFile.is_open()) {
        outFile << word << endl;
        outFile.close();
        return true;
    }
    return false;
}

void toReadDataBase() {
    ifstream inFile("banco.txt");
    string line;
    if(inFile.is_open()){
        while(getline(inFile, line)){
            cout<<"\n"<<line<<endl;
        }
        inFile.close();
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }
}

bool removeWordFromFile(const string& wordToRemove) {
    ifstream inFile("banco.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    // Verifica se ambos os arquivos foram abertos corretamente
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }

    // Ler cada linha do arquivo original
    while (getline(inFile, line)) {
        if (line != wordToRemove) {
            // Se a linha n�o for a palavra a ser removida, escreve no arquivo tempor�rio
            tempFile << line << endl;
        } else {
            found = true; // Palavra encontrada
        }
    }

    inFile.close();
    tempFile.close();

    // Se a palavra foi encontrada, substitu�mos o arquivo original pelo tempor�rio
    if (found) {
        remove("banco.txt");            // Remove o arquivo original
        rename("temp.txt", "banco.txt"); // Renomeia o arquivo tempor�rio
    } else {
        remove("temp.txt"); // Se a palavra n�o foi encontrada, remove o arquivo tempor�rio
    }

    return found;
}

#endif // DATABASE_H_INCLUDED
