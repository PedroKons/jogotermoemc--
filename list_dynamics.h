#ifndef LIST_DYNAMICS_H_INCLUDED
#define LIST_DYNAMICS_H_INCLUDED

template<typename T> // Aceita qualquer tipo de variavel
struct TElemento { // Bloco elemento
    T dado; // Espaço dentro do bloco para o dado
    TElemento<T> *proximo; // Espaço dentro do bloco para o apontamento para proximo bloco de elemento
};

template<typename T>
struct TLista { // Estrutura da lista
    TElemento<T> *inicio; // Marca o inicio da lista ou seja o bloco de inicio
    TElemento<T> *fim;
};

template<typename T>
bool inicializar_lista(TLista<T>& lista){ // Inicia a lista com null quer dizer vazia
    lista.inicio = NULL;
    lista.fim = NULL;
    return true;
}

//Alocação de memória
template<typename T>
TElemento<T> *novo_elemento(T dado) { // Uma funcao que retorna um ponteiro para um objeto do tipo TElemento
    TElemento<T> *novo = new TElemento<T>; // Cria um ponteiro novo que aponta para um novo bloco TElemento criado
    novo->dado = dado; // novo bloco recebe o dado passado por parametro
    novo->proximo = NULL; // E aponta para o final
    return novo; // retorna o novo bloco
}

template<typename T>
bool insere_fim(TLista<T>& lista, T dado) { // Função para inserir no final
    TElemento<T> *nav = lista.inicio; // Ponteiro de nevagação entre os blocos da lista
    TElemento<T> *novo = novo_elemento(dado); // Obtendo um novo bloco de lista
    if(lista.inicio != NULL) { // Verifica se a lista não está vazia
        while (nav->proximo != NULL){ // Loop para achar o ultimo elemento da lista
            nav = nav->proximo;
        }
        novo->proximo = nav->proximo; // Novo bloco recebe a ultima posicao
        nav->proximo = novo; // nav passa apontar para o novo
        return true; // retora verdadeira pois deu certo
    } else { // Caso a lista esteja vazia
        novo->proximo = lista.inicio; // Novo recebe o inicio que atualmente é null
        lista.inicio = novo; // lista recebe o novo
        return true; // retorna verdadeiro
    }
}

template<typename T>
bool insere(TLista<T>& lista, T dado){
    TElemento<T> *nav = lista.inicio;
    TElemento<T> *novo = novo_elemento(dado);
    TElemento<T> *ant = NULL;
    if( lista.inicio == NULL){ // Caso A 'Lista vazia'
        novo->proximo = lista.inicio;
        lista.inicio = novo;
        lista.fim = novo;
    }
    else if( dado < lista.inicio->dado) { // Caso B 'Inicio lista'
        novo->proximo = lista.inicio;
        lista.inicio = novo;
    }
    else if(dado > lista.fim->dado) { // Caso C 'Final da lista'
        lista.fim->proximo = novo;
        lista.fim = novo;
    }
    else { // Caso D 'Entre dois nós'
        while(nav != NULL && nav->dado < dado ) {
            ant = nav;
            nav = nav->proximo;
        }
        ant->proximo = novo; // O anterior aponta para o novo elemento
        novo->proximo = nav; // O novo elemento aponta para o próximo
    }

    return true;
}

template<typename T>
bool remover (TLista<T>& lista, T dado) {
    TElemento<T> *nav = lista.inicio;
    TElemento<T> *ant = NULL;
    if(lista.inicio == NULL) { //Se a lista tiver vazia nem executa
        return false;
    }
    if(lista.inicio->dado == dado && lista.fim->dado == dado) { // Unico elemento
        delete lista.inicio;
        lista.inicio = NULL;
        lista.inicio = NULL;
    }
    if(lista.inicio->dado == dado) { // Inicio lista
        TElemento<T> *temp = lista.inicio;
        lista.inicio = lista.inicio->proximo;
        delete temp;
    }
    else {
        while (nav != NULL && nav->dado != dado) {
            ant = nav;
            nav = nav->proximo;
        }

        if(nav == NULL) {
            return false;
        }

        ant->proximo =  nav->proximo;
        if(nav == lista.fim) {
            lista.fim = ant;
        }

        delete nav;
        return true;
    }
}

template<typename T>
void vizualizar_lista(TLista<T> lista) {
    TElemento<T> *nav = lista.inicio;
    while(nav != NULL){
        cout<<nav->dado<<" ";
        nav = nav->proximo;
    }
}

template<typename T>
bool busca_dado(TLista<T> lista, T dado) {
    TElemento<T> *nav = lista.inicio;
    while(nav != NULL){
        if(dado == nav->dado){
            return true;
        }
        nav = nav->proximo;
    }

    return false;
}

template<typename T>
bool liberar_memoria(TLista<T> &lista){
    TElemento<T> *nav = lista.inicio;
    cout<<"\nIniciando a liberacao de memoria";
    while(nav != NULL){
        TElemento<T> *temp = nav;
        nav = nav->proximo;
        delete temp;
        cout<<"\nElemento liberado";
    }
    lista.inicio = NULL;
    cout<<"\nMemoria liberada com sucesso";
    return true;
}

template<typename T>
int retorna_comprimento(TLista<T> lista) {
    TElemento<T> *nav = lista.inicio;
    int contador = 0;
    if (lista.inicio == NULL) return 0;
    while (nav != NULL) {
        contador++;
        nav = nav->proximo;
    }
    return contador;
}


template<typename T>
T get_element_at(TLista<T> lista, int index) {
    TElemento<T> *nav = lista.inicio;
    int contador = 0;

    while (nav != NULL) {
        if (contador == index) {
            return nav->dado;
        }
        nav = nav->proximo;
        contador++;
    }

    throw out_of_range("Índice fora do alcance");
}



#endif // LIST_DYNAMICS_H_INCLUDED
