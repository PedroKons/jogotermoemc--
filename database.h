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
            // Se a linha não for a palavra a ser removida, escreve no arquivo temporário
            tempFile << line << endl;
        } else {
            found = true; // Palavra encontrada
        }
    }

    inFile.close();
    tempFile.close();

    // Se a palavra foi encontrada, substituímos o arquivo original pelo temporário
    if (found) {
        remove("banco.txt");            // Remove o arquivo original
        rename("temp.txt", "banco.txt"); // Renomeia o arquivo temporário
    } else {
        remove("temp.txt"); // Se a palavra não foi encontrada, remove o arquivo temporário
    }

    return found;
}

#endif // DATABASE_H_INCLUDED
