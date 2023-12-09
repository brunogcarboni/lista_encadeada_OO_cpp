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
    // Implemente aqui as funcões marcadas com virtual na ListaEncadeadaAbstrata
    // Lembre-se de implementar o construtor e destrutor da classe

    virtual ~MinhaListaEncadeada()
    {
        while (!vazia())
        {
            removerDoInicio();
        }
    };

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };
    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const
    {
        return (this->_primeiro == nullptr) ? true : false;
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
        if (vazia())
            throw ExcecaoListaEncadeadaVazia();

        /**
         * itera toda a lista com o ponteiro 'procura_dado' e retorna o valor de 'i'
         * quando encontrar o dado passado para a função
         */
        // ponteiro iterador
        Elemento<T> *procura_dado = this->_primeiro;
        // posicao do ponteiro iterador
        int i = 0;

        while (dado != procura_dado->dado)
        {
            if (procura_dado->proximo == nullptr) // ponteiro iterador aponta para o ultimo elemento, logo dado inexistente.
                throw ExcecaoDadoInexistente();

            procura_dado = procura_dado->proximo;
            i++;
        }

        return i;
    };
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        if (tamanho() != 0) // condicao quando a lista esta vazia
        {
            // ponteiro iterador
            Elemento<T> *procura_dado = this->_primeiro;
            // controle de posicao para nao acessar posições inválidas.
            int i = 0;

            /**
             * itera toda a lista com o ponteiro 'procura_dado' e retorna booleana
             * quando encontrar o dado passado para a função
             */

            while (procura_dado->dado != dado && i <= tamanho() && procura_dado->proximo != nullptr)
            {
                procura_dado = procura_dado->proximo;
                i++;
            }

            return (procura_dado->dado == dado) ? true : false;
        }
        else
        {
            return false;
        }
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {
        Elemento<T> *novo_elemento = new Elemento(dado);

        if (!vazia()) // lista nao esta vazia
        {
            /**
             * aponta o novo elemento para o atual primeiro elemento da lista
             * novo elemento é o novo primeiro elemento
             */
            novo_elemento->proximo = this->_primeiro;
            this->_primeiro = novo_elemento;
        }
        else // lista esta vazia
        {
            /**
             * novo elemento é o primeiro e ultimo elemento da lista
             * (novo elemento ja foi inicializado apontando para 'nullptr').
             */
            this->_primeiro = novo_elemento;
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
        if (posicao < tamanho() && posicao > 0)
        {

            // ponteiro iterador | novo elemento
            Elemento<T> *procura_posicao = new Elemento(dado, this->_primeiro);

            /**
             * itera a lista a procura da posicao correta e entao insere
             * o elemento seguindo os seguintes passos
             *
             * 1 - iterador para dois elementos antes da posicao correta
             * 2 - iterador aponta para o segundo elemento seguinte (sucessor a posicao correta)
             * 3 - elemento seguinte (antecessor a posicao correta) aponta para iterador/novo elemento
             * 4 - incrementa tamanho da lista
             */

            for (size_t i = 0; i < posicao - 1; i++)
            {
                procura_posicao->proximo = procura_posicao->proximo->proximo;
            }

            // elemento antecessor
            Elemento<T> *temp = procura_posicao->proximo;

            procura_posicao->proximo = procura_posicao->proximo->proximo;
            temp->proximo = procura_posicao;
            this->_tamanho++;
        }
        else if (posicao < 0 || posicao > tamanho()) // valor de posicao desrespeita o intervalo válido
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao == tamanho())
        {
            inserirNoFim(dado);
        }
        else // (posicao == 0)
        {
            inserirNoInicio(dado);
        }
    };
    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        // ponteiro iterador | novo elemento
        Elemento<T> *novo_elemento = new Elemento(dado);

        if (!vazia())
        {

            /**
             * iterador procura ultimo elemento da lista a partir do
             * endereco apontado pelo segundo elemento seguinte a ele
             * (que sera 'nullptr' quando alcançar o último elemento)
             */

            novo_elemento->proximo = this->_primeiro;

            for (size_t i = 0; i < tamanho() - 1; i++)
            {
                novo_elemento->proximo = novo_elemento->proximo->proximo;
            }

            novo_elemento->proximo->proximo = novo_elemento;
            novo_elemento->proximo = nullptr;
        }
        else // lista vazia
        {
            //(elemento ja incializado apontando para nulo)
            this->_primeiro = novo_elemento;
        }

        this->_tamanho++;
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if (!vazia())
        {

            /**
             * segundo elemento é o novo primeiro elemento da lista
             */

            Elemento<T> *temp = this->_primeiro;
            T dado = this->_primeiro->dado;

            this->_primeiro = this->_primeiro->proximo;
            delete temp;
            this->_tamanho--;

            return dado;
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
        if (posicao > 0 && posicao < tamanho() - 1 && !vazia())
        {
            // ponteiro iterador
            Elemento<T> *procura_posicao = this->_primeiro;

            /**
             * ponteiro iterador procura posicao correta para
             * remover elemento
             */

            for (size_t i = 1; i <= posicao - 1; i++)
            {
                procura_posicao = procura_posicao->proximo;
            }

            T dado = procura_posicao->proximo->dado;
            // elemento seguinte ao que sera removido, para nao perder endereço na memória
            Elemento<T> *temp = procura_posicao->proximo->proximo;

            delete procura_posicao->proximo;
            procura_posicao->proximo = temp;
            this->_tamanho--;
            return dado;
        }
        else if (posicao < 0 || posicao >= tamanho())// fora do intevalo de posições válidas
        { 
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao == tamanho() - 1)
        {
            return removerDoFim();
        }
        else if (posicao == 0)
        {
            return removerDoInicio();
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

        if (!vazia() && tamanho() != 1)
        {
            //ponteiro iterador
            Elemento<T> *procura_final = this->_primeiro;

            /**
             * ponteiro iterador procura final da lista e remove ultimo elemento
             * (ponteiro para apontando para o ultimo elemento)
            */

            while (procura_final->proximo->proximo != nullptr)
            {
                procura_final = procura_final->proximo;
            }

            T dado = procura_final->proximo->dado;

            delete procura_final->proximo;
            procura_final->proximo = nullptr; //penúltimo elemento é o novo ultimo elemento
            this->_tamanho--;
            return dado;
        }
        else if (tamanho() == 1)
        {
            return removerDoInicio();
        }
        else //(vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
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
        if (!vazia() && contem(dado))
        {
            removerDe(posicao(dado));
        }
        else if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else //(!contem(dado))
        {
            throw ExcecaoDadoInexistente();
        }
    };
};

#endif