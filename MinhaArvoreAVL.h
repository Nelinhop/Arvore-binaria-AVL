#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
     ~MinhaArvoreAVL(){
         while(this->_raiz != nullptr){
             remover(this->_raiz->chave);
         }
        
    };
///////////////////////////////////////////////////////////
     bool vazia() const {
        if (this->_raiz == nullptr)
        return true;
    else
        return false;
    };
 ///////////////////////////////////////////////////////////////////   
    
   int quantidade() const {
    return ContarChavesRecurs(this->_raiz);
    };

    int ContarChavesRecurs(const Nodo<T>* raiz) const{
    if (raiz == nullptr)
        return 0;

    int count = 1;
    count += ContarChavesRecurs(raiz->filhoEsquerda);
    count += ContarChavesRecurs(raiz->filhoDireita);

    return count;
    };
    
    //////////////////////////////////////////////////////////

     bool contem(T chave) const {
        return buscarChaveRecurs(this->_raiz, chave);
        
    };

    bool buscarChaveRecurs(Nodo<T>* nodo, T chaveBuscada){
    if (nodo == nullptr)
        return false;
    if (nodo->chave == chaveBuscada)
        return true;
    if (chaveBuscada < nodo->chave)
        return buscarChaveRecurs(nodo->filhoEsquerda, chaveBuscada);
    else
        return buscarChaveRecurs(nodo->filhoDireita, chaveBuscada);
};
 
 /////////////////////////////////////////////////////

    std::optional<int> altura(T chave) const {
    return alturaRecurs(this->_raiz, chave);
}

    std::optional<int> alturaRecurs(Nodo<T>* raiz, T chave) const {
    if (raiz == nullptr)
        return std::nullopt;
    
    if (chave < raiz->chave)
        return alturaRecurs(raiz->filhoEsquerda, chave);
    else if (chave > raiz->chave)
        return alturaRecurs(raiz->filhoDireita, chave);
    else
        return raiz->altura;
};


int alturaRecurs(Nodo<T>* raiz){
  if(raiz == nullptr)
  {
      return -1;
  }
  
  return std::max(alturaRecurs(raiz->filhoEsquerda), alturaRecurs(raiz->filhoDireita)) + 1;
    
};

//////////////////////////////////////////////////////////     
    

    
   void inserirRecurs(Nodo<T>* raiz, T chave)
{
    if (chave >= raiz->chave)
    {
        if (raiz->filhoDireita == nullptr)
        {
            Nodo<T>* novo = new Nodo<T>{chave};
            raiz->filhoDireita = novo;
        }
        else
        {
            inserirRecurs(raiz->filhoDireita, chave);
        }
    }
    else
    {
        if (raiz->filhoEsquerda == nullptr)
        {
            Nodo<T>* novo = new Nodo<T>{chave};
            raiz->filhoEsquerda = novo;
        }
        else
        {
            inserirRecurs(raiz->filhoEsquerda, chave);
        }
    }
    
    raiz->altura = this->alturaRecurs(raiz);
        
    balancear(raiz);
};


     void inserir(T chave) {
        if(this->_raiz == nullptr){
            Nodo<T>* novo = new Nodo<T>{chave};
            this->_raiz = novo;
        }
        else 
            inserirRecurs(this->_raiz,chave);
    };

//////////////////////////////////////////////////////////
    int fatorBalanceamento(Nodo<T>* raiz){
        int direita,esquerda;

        if(raiz->filhoDireita == nullptr)
            direita = -1;
        else 
            direita = raiz->filhoDireita->altura; 

        if(raiz->filhoEsquerda == nullptr)
            esquerda = -1;
        else 
            esquerda = raiz->filhoEsquerda->altura; 

        return esquerda - direita;
    };

    void balancear(Nodo<T>* raiz){
        if(raiz->altura == 0)
            return;
        int fator = fatorBalanceamento(raiz);
        if(fator > 1){
            int fatoresquerda = fatorBalanceamento(raiz->filhoEsquerda);
            if(fatoresquerda >= 0)
                rotacaoDireita(raiz);
            else if(fatoresquerda < 0)
                rotacaoEsquerdaDireita(raiz);
        }
        else if(fator < -1){
            int fatordireita     = fatorBalanceamento(raiz->filhoDireita);
            if(fatordireita >= 0)
                rotacaoEsquerda(raiz);
            else if(fatordireita < 0)
                rotacaoDireitaEsquerda(raiz);
        }
        else 
            return;
    };
    
    //////////////////////////////////////////////////////
 
   void rotacaoEsquerda(Nodo<T>*& nodo) {
        Nodo<T>* novaRaiz = nodo->filhoDireita;
        nodo->filhoDireita = novaRaiz->filhoEsquerda;
        novaRaiz->filhoEsquerda = nodo;
        
        nodo = novaRaiz;
    }

    void rotacaoDireita(Nodo<T>*& nodo) {
        Nodo<T>* novaRaiz = nodo->filhoEsquerda;
        nodo->filhoEsquerda = novaRaiz->filhoDireita;
        novaRaiz->filhoDireita = nodo;

        nodo = novaRaiz;
    }
    
    void rotacaoEsquerdaDireita(Nodo<T>*& nodo) {
        rotacaoEsquerda(nodo->filhoEsquerda);
        rotacaoDireita(nodo);
    }

 
    void rotacaoDireitaEsquerda(Nodo<T>*& nodo) {
        rotacaoDireita(nodo->filhoDireita);
        rotacaoEsquerda(nodo);
    }
///////////////////////////////////////////////////////////////////////////
     void remover(T chave)
{
    this->_raiz = removerRecurs(this->_raiz, chave);
}

Nodo<T>* removerRecurs(Nodo<T>* raiz, T chave)
{
    if (raiz == nullptr)
        return nullptr;
    
    if (chave < raiz->chave)
        raiz->filhoEsquerda = removerRecurs(raiz->filhoEsquerda, chave);
    else if (chave > raiz->chave)
        raiz->filhoDireita = removerRecurs(raiz->filhoDireita, chave);
    else
    {
        if (raiz->filhoEsquerda == nullptr)
        {
            Nodo<T>* temp = raiz->filhoDireita;
            delete raiz;
            return temp;
        }
        else if (raiz->filhoDireita == nullptr)
        {
            Nodo<T>* temp = raiz->filhoEsquerda;
            delete raiz;
            return temp;
        }
        
        Nodo<T>* minDireita = encontrarMinimo(raiz->filhoDireita);
        raiz->chave = minDireita->chave;
        raiz->filhoDireita = removerRecurs(raiz->filhoDireita, minDireita->chave);
    }
    
    raiz->altura = this->alturaRecurs(raiz);
    
    balancear(raiz);
    return raiz;
}

Nodo<T>* encontrarMinimo(Nodo<T>* raiz)
{
    if (raiz == nullptr)
        return nullptr;

    Nodo<T>* atual = raiz;
    while (atual->filhoEsquerda != nullptr)
        atual = atual->filhoEsquerda;

    return atual;
}

//////////////////////////////////////////////////////////////////
std::optional<T> filhoEsquerdaDe(T chave) const {
    Nodo<T>* nodo = buscarChaveRecurs(this->_raiz, chave);
    if (nodo && nodo->filhoEsquerda) {
        return nodo->filhoEsquerda->chave;
    }
    return std::nullopt;
}

std::optional<T> filhoDireitaDe(T chave) const {
    Nodo<T>* nodo = buscarChaveRecurs(this->_raiz, chave);
    if (nodo && nodo->filhoDireita) {
        return nodo->filhoDireita->chave;
    }
    return std::nullopt;
}

bool buscar(T chave) const {
    return buscarChaveRecurs(this->_raiz, chave) != nullptr;
}

Nodo<T>* buscarChaveRecurs(Nodo<T>* nodo, T chaveBuscada) const {
    if (nodo == nullptr || nodo->chave == chaveBuscada)
        return nodo;
    if (chaveBuscada < nodo->chave)
        return buscarChaveRecurs(nodo->filhoEsquerda, chaveBuscada);
    else
        return buscarChaveRecurs(nodo->filhoDireita, chaveBuscada);
}


////////////////////////////////////////////////////////////////////////
     ListaEncadeadaAbstrata<T>* emOrdem() const {
        ListaEncadeadaAbstrata<T>* Lista = new MinhaListaEncadeada<T>;
        emOrdemRecurs(Lista,this->_raiz);
        return Lista;
    };

     ListaEncadeadaAbstrata<T>* preOrdem() const {
        ListaEncadeadaAbstrata<T>* Lista = new MinhaListaEncadeada<T>;
        preOrdemRecurs(Lista,this->_raiz);
        return Lista;  
    };

    ListaEncadeadaAbstrata<T>* posOrdem() const {
    ListaEncadeadaAbstrata<T>* lista = new MinhaListaEncadeada<T>;
    posOrdemRecurs(this->_raiz, lista);
    return lista;
}
    
    void emOrdemRecurs(ListaEncadeadaAbstrata<T>* lista, Nodo<T>* nodo) const {
    if (nodo == nullptr)
        return;
    emOrdemRecurs(lista, nodo->filhoEsquerda);
    lista->inserirNoFim(nodo->chave);
    emOrdemRecurs(lista, nodo->filhoDireita);
}

    void preOrdemRecurs(ListaEncadeadaAbstrata<T>* lista, Nodo<T>* nodo) const {
    if (nodo == nullptr)
        return;
    lista->inserirNoFim(nodo->chave);
    preOrdemRecurs(lista, nodo->filhoEsquerda);
    preOrdemRecurs(lista, nodo->filhoDireita);
};
   void posOrdemRecurs(Nodo<T>* nodo, ListaEncadeadaAbstrata<T>* lista) const {
    if (nodo == nullptr)
        return;
    posOrdemRecurs(nodo->filhoEsquerda, lista);
    posOrdemRecurs(nodo->filhoDireita, lista);
    lista->inserirNoFim(nodo->chave);
}

};

#endif