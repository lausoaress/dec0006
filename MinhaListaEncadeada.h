#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada()
    {
        // escreva o algoritmo esperado
        
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };

    virtual bool vazia() const
    {
        if (this->_primeiro == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const
    {
        if (this->_tamanho == 0)
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T> *atual = this->_primeiro;
        std::size_t posicao = 0;

        while (atual != 0)
        {
            if (dado == atual->dado)
            {
                return posicao;
            }
            atual = atual->proximo;
            posicao++;
        }

        throw ExcecaoDadoInexistente();
    };

    /**
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        Elemento<T> *atual = this->_primeiro;

        while (atual != nullptr)
        {
            if (dado == atual->dado)
            {
                return true;
            }
            atual = atual->proximo;
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {
        if (this->_tamanho == 0)
        {
            this->_primeiro = new Elemento<T>(dado, nullptr);
            this->_tamanho++;
            return;
        }
        else
        {
            Elemento<T> *novo = new Elemento<T>(dado, this->_primeiro);
            this->_primeiro = novo;
        }
        this->_tamanho++;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        if (posicao > this->_tamanho || posicao < 0)
        {
            throw ExcecaoPosicaoInvalida();
        }
        if (posicao == 0)
        {
            inserirNoInicio(dado);
        }
        else
        {
            Elemento<T> *atual = this->_primeiro;

            for (size_t i = 0; i < posicao - 1; i++)
            {
                atual = atual->proximo;
            }
            atual->proximo = new Elemento<T>(dado, atual->proximo);
            this->_tamanho++;
        }
    };
    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {

        this->inserir(this->_tamanho, dado);
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {

        if (this->_tamanho > 0)
        {
            Elemento<T> *atual = this->_primeiro;
            this->_primeiro = atual->proximo;
            T atualdado = atual->dado;
            delete atual;
            this->_tamanho--;
            return atualdado;
        }

        else
        {
            throw ExcecaoListaEncadeadaVazia();
        }
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        

        if (posicao >= this->_tamanho  || posicao < 0)
        {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0 && !this->vazia())
        {
            return removerDoInicio();
        }
        else
        {
            Elemento<T> *atual = this->_primeiro;

            for (std::size_t i = 0; i < posicao - 1; i++)
            {
                atual = atual->proximo;
            }

            Elemento<T> *remover = atual->proximo;
            atual->proximo = remover->proximo;
            T dadoremovido = remover->dado;
            delete remover;

            this->_tamanho--;
            return dadoremovido;
        }
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        if (this->vazia())
            throw ExcecaoListaEncadeadaVazia();

        return this->removerDe(this->_tamanho - 1);
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {

        if (this->_tamanho == 0)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if (!contem(dado))
        {
            throw ExcecaoDadoInexistente();
        }

        Elemento<T> *anterior = this->_primeiro;
        Elemento<T> *atual = anterior->proximo;

        if (anterior->dado == dado)
        {
            this->removerDoInicio();
            return;
        }


        while (atual->dado != dado)
        {
            anterior = anterior->proximo;
            atual = atual->proximo;
        if(atual->proximo == nullptr)
            break;
       
        }
        if (atual->dado == dado)
        {
            anterior->proximo = atual->proximo;
            delete atual;
        this->_tamanho--;
        }

    };
};

#endif