#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.h"

template <typename T>
class MinhaListaEncadeada :  public ListaEncadeadaAbstrata<T>
{
    ~MinhaListaEncadeada(){
        while(this->_tamanho > 0){
            removerDoFim();
        }
    };
    
    virtual std::size_t tamanho() const{
         return this->_tamanho;
     };
    
    virtual bool vazia() const{
        if(this->_primeiro == nullptr)
         return true;
         
         else
             return false;
    
     };

    virtual std::size_t posicao(T dado) const{
         if(vazia())
            throw ExcecaoListaEncadeadaVazia();
        
        Elemento<T> *aux = this->_primeiro;
        int i=0;
        
        while(i < this->_tamanho){
            if(aux->dado == dado){
                return i;
            }
            aux = aux->proximo;
            i++;
        }
        
        throw ExcecaoDadoInexistente();
     };
 
    virtual bool contem(T dado) const
    {
        Elemento<T>* Aux = this->_primeiro;

        std::size_t pos = 0;

        while(pos < this->_tamanho)
        {
            if(Aux->dado == dado)
                return true;
            Aux = Aux->proximo;
            pos++;

        }
        return false;
    };

    virtual void inserirNoInicio(T dado){
        
        Elemento<T> *aux = new Elemento<T>(dado);
        
        aux->proximo =  this->_primeiro;
        
        this->_primeiro = aux;
        this->_tamanho = this->_tamanho+1;
   
     };
   
    virtual void inserir(std::size_t posicao, T dado){
            Elemento<T> *aux = new Elemento<T>(dado);

            if (posicao < 0 || posicao > this->_tamanho)
                throw ExcecaoPosicaoInvalida();
        
              else if (posicao == 0)
                 {
                    inserirNoInicio(dado);
            }
                else if (posicao == this->_tamanho)
                 {
                    inserirNoFim(dado);
            }
              else
                {
                  Elemento<T> *aux2 = this->_primeiro;
            
                   while (--posicao > 0)
            	{
            	  aux2 = aux2->proximo;
            	}
                  aux->proximo = aux2->proximo;
                  aux2->proximo = aux;
                  this->_tamanho =  this->_tamanho+1;
                }
     };
    
    virtual void inserirNoFim(T dado){
        
      Elemento<T> *aux = new Elemento<T>(dado);
     
      if(this->_primeiro == nullptr) {
        this->_primeiro = aux;
        
      } else {
        Elemento<T> *aux2 = this->_primeiro;
        while(aux2->proximo != nullptr)
          aux2 = aux2->proximo;
        aux2->proximo = aux;
      }  
      this->_tamanho =  this->_tamanho+1;
         
     };

    virtual T removerDoInicio(){
        if(vazia())
            throw ExcecaoListaEncadeadaVazia();
            
        else{
            
        Elemento<T> *aux = this->_primeiro;
        this->_primeiro = this->_primeiro->proximo;
        
        T i = aux->dado;
        
        delete aux;
        this->_tamanho =  this->_tamanho-1;
        
        return i;
        }
         
     };
    
    virtual T removerDe(std::size_t posicao){
         
         if (posicao < 0 || posicao >= this->_tamanho)
                throw ExcecaoPosicaoInvalida();
                
            else if (posicao == 0)
                 {
                    return removerDoInicio();
            }
                else if (posicao == this->_tamanho)
                 {
                    return removerDoFim();
            }
            else{
                Elemento<T> *aux = this->_primeiro;
                size_t i = 0;
                   while (i != posicao-1)
            	{
            	  aux = aux->proximo;
            	  i++;
            	}
                  Elemento<T> *aux2 = aux->proximo;
                  aux->proximo = aux2->proximo;
                  
                  T j = aux2->dado;
                  
                  delete aux2;
                  
                  this->_tamanho =  this->_tamanho-1;
                  return j;
            }
     };
    
    virtual T removerDoFim(){
        if(vazia())
            throw ExcecaoListaEncadeadaVazia();
        Elemento<T> *aux = this->_primeiro;   
        
        if (this->_primeiro->proximo == nullptr) {
        
         T i = aux->dado;
         delete aux;
         this->_tamanho =  this->_tamanho-1;
         this->_primeiro = nullptr;
         
         return i;
        }
        
        while (aux->proximo->proximo != nullptr){
            aux = aux->proximo;
        }
        
        T i = aux->proximo->dado;
        delete aux->proximo;
      
        aux->proximo = nullptr;
        this->_tamanho =  this->_tamanho-1;
        
        return i;
     };

    virtual void remover(T dado){
        if(vazia())
            throw ExcecaoListaEncadeadaVazia();
        if(!contem(dado))
            throw ExcecaoDadoInexistente();

        Elemento<T> *aux = this->_primeiro;    

        removerDe(posicao(dado));
     };
};

#endif