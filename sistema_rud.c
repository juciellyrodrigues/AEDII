// Jucielly Gonçalves Rodrigues
//AEDII - Engenharia de Computação

/*enunciado: Você foi contratado para implementar um sistema rudimentar de proteção de dados (ofuscação) 
que precisa embaralhar a ordem dos elementos durante sua inserção em uma lista linear. Para isso, foi criada 
uma regra simples: cada novo valor inserido deve ocupar a posição central da lista atual. Com essa técnica, a ordem 
de entrada não reflete a ordem final dos elementos armazenados, dificultando que um intruso descubra os dados originais
apenas olhando a estrutura. Esta função de inserção, criada através de uma lista encadeada, armazenará unicamente elementos
contendo cada um, um número inteiro. O que é a posição central: -> É dada por ⌊n/2⌋, onde n é o tamanho atual da lista antes
da inserção. -> A numeração das posições começa em 0 (zero). Exemplo: Lista com 4 elementos: índice do meio = 2 → insere na
posição 2. Lista com 0 ou 1 elementos: novo elemento entra na posição 0. Sua função receberá como parâmetros o ponteiro para
a cabeça da lista, um valor inteiro que pertencerá ao novo elemento e outro valor inteiro contendo o tamanho da lista atual.
-------------------------------------------------------- 
Além da função de inserção, foi solicitado também que você desenvolva uma função simples que apresente TODOS os elementos presentes
na lista, porém estes devem ser impressos em ordem inversa (do último elemento da lista para o primeiro). Esta função deve ser implementada 
através da técnica de recursão. */

#include <stdio.h>
#include <stdlib.h>

/* definição da estrutura do nó da lista encadeada*/
typedef struct No
{
    int valor; //campo de armazena o tipo in di nó
    struct  No* prox; //poneito para o próximo nó da lista
} No; //'No' é nome para 'struct No'

//cria um novo nó com valor passado e retorna o poneiro p/ ele
No* criarNo(int valor){ 
    No* novo = (No*) malloc(sizeof(No)); //aloca memória para o novo nó
    if(novo == NULL){ //ferificação do malloc
        fprintf(stderr, "Erro; malloc falhou\n"); //imprime erro
        exit(EXIT_FAILURE); //encerra o programa
    }

    novo->valor = valor; //valor recebido ao campo 'valor' do nó
    novo->prox = NULL; // inicialmente o prox nó é NULL
    return novo;
}

// insere um novo nó na posição central da lista 
/* cabeca é ponteiro p/ ponteiro de cabeça porque 
podemos alterar a cabeça */
void inserirMeio(No** cabeca, int valor, int tamanho){
    No* novo = criarNo(valor); // criar o novo nó com o valor informado

/* se a lista estiver vazia (*cabeca == NULL) ou tamanho <= 1.
inserimos o novo nó no inicio (posição 0)*/

if(*cabeca == NULL || tamanho <= 1){
    novo->prox = *cabeca; //novo aponta para antiga cabeca
    *cabeca = novo; //atualiza para o novo nó
    return; 
}

int pos = tamanho/2; //calcula a posição do meio
No* atual = *cabeca; // ponteiro aux p/ percorrer a lista

/* percorre até o nó anterior á posição de inserção
querems para em (pos - 1)*/

for(int i = 0; i < pos - 1 && atual->prox != NULL; i++){
    atual = atual->prox; // avança p/ o prox nó
}

// 'atual está no nó após o qual queremos inserir o novo nó
novo->prox = atual->prox; //novo aponta p/ o que antes vinha depois de 'atual'
atual->prox = novo; // 'atual' passa a apontar p/ novo nó

}

//imprime a lista em ordem inversa usando recursão (do ultimo p/ primeiro)

void imprimirRev (No* cabeca){
    if (cabeca == NULL) return; //caso base: lista vazia ou fim da lista
    imprimirRev(cabeca->prox); //chamada recursiva p/ prox nó
    printf("%d ", cabeca->valor); //ao voltar da recursão, imprime o valor
}

// função aux p/ liberar toda lista (necessária?)

void liberarLista(No* cabeca){
    while (cabeca != NULL) //percorre enquanto houver nó's
    {
        No* temp = cabeca; //guarda o nó atual
        cabeca = cabeca->prox; //avança a cabeça para o prox nó
        free(temp); //libera a memória do nó anterior
    }
    
}

int main(){
    No* lista = NULL; //inicializa a cabeça da lista como NULL
    int tamanho = 0; //variável que mantém o tamanho atual da lista

    /*'tamanho++' p/ passar o tamanho atual 
    e depois incrementá-lo para a próxima inserção*/

    inserirMeio(&lista, 10, tamanho++); // insere 10 com tam antes = 0
    inserirMeio(&lista, 20, tamanho++); // insere 20 com tam antes = 1
    inserirMeio(&lista, 30, tamanho++); // insere 30 com tam antes = 2
    inserirMeio(&lista, 40, tamanho++); // insere 40 com tam antes = 3
    inserirMeio(&lista, 50, tamanho++); // insere 50 com tam antes = 4

    printf("Lista invertida: "); //imprime im título antes da lista invertida
    imprimirRev(lista); //chama a função recursiva que imprime ao contrário
    printf("\n"); 

    liberarLista(lista); //libera a memória alocada p/ os nó's
    return 0;
}

//resp esperada: 10 30 50 40 20 