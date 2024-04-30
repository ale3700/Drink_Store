#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct Produto* esquerda;
    struct Produto* direita;
} Produto;

Produto* criarProduto(int codigo, char nome[], int quantidade, float preco) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->codigo = codigo;
    strcpy(novoProduto->nome, nome);
    novoProduto->quantidade = quantidade;
    novoProduto->preco = preco;
    novoProduto->esquerda = NULL;
    novoProduto->direita = NULL;
    return novoProduto;
}

Produto* inserirProduto(Produto* raiz, int codigo, char nome[], int quantidade, float preco) {
    if (raiz == NULL) {
        return criarProduto(codigo, nome, quantidade, preco);
    }

    if (codigo < raiz->codigo) {
        raiz->esquerda = inserirProduto(raiz->esquerda, codigo, nome, quantidade, preco);
    } else if (codigo > raiz->codigo) {
        raiz->direita = inserirProduto(raiz->direita, codigo, nome, quantidade, preco);
    }

    return raiz;
}

Produto* encontrarProduto(Produto* raiz, char nome[]) {
    if (raiz == NULL) {
        return raiz;
    }

    int cmp = strcmp(nome, raiz->nome);

    if (cmp == 0) {
        return raiz;
    }

    if (cmp < 0) {
        return encontrarProduto(raiz->esquerda, nome);
    }

    return encontrarProduto(raiz->direita, nome);
}

Produto* encontrarMenor(Produto* raiz) {
    Produto* atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Produto* excluirProduto(Produto* raiz, int codigo) {
    if (raiz == NULL) {
        return raiz;
    }

    if (codigo < raiz->codigo) {
        raiz->esquerda = excluirProduto(raiz->esquerda, codigo);
    } else if (codigo > raiz->codigo) {
        raiz->direita = excluirProduto(raiz->direita, codigo);
    } else {
        if (raiz->esquerda == NULL) {
            Produto* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Produto* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Produto* temp = encontrarMenor(raiz->direita);
        raiz->codigo = temp->codigo;
        raiz->direita = excluirProduto(raiz->direita, temp->codigo);
    }

    return raiz;
}

void listarProdutos(Produto* raiz) {
    if (raiz != NULL) {
        listarProdutos(raiz->esquerda);
        printf("codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", raiz->codigo, raiz->nome, raiz->quantidade, raiz->preco);
        listarProdutos(raiz->direita);
    }
}


void listarProdutosComInicial(Produto* raiz, char letra) {
    if (raiz != NULL) {
        listarProdutosComInicial(raiz->esquerda, letra);

        // Check if the product name starts with the specified letter
        if (raiz->nome[0] == letra) {
            printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", raiz->codigo, raiz->nome, raiz->quantidade, raiz->preco);
        }

        listarProdutosComInicial(raiz->direita, letra);
    }
}
void listarProdutosPorNome(Produto* raiz) {
    printf("Digite a letra inicial para listar produtos: ");
    char letra;
    scanf(" %c", &letra);  // Note the space before %c to consume any newline character

    printf("Produtos iniciando com '%c':\n", letra);
    listarProdutosComInicial(raiz, letra);
}

void alterarProduto(Produto* raiz, int codigo, char nome[], int quantidade, float preco) {
    Produto* produto = encontrarProduto(raiz, nome);
    if (produto != NULL) {
        strcpy(produto->nome, nome);
        produto->quantidade = quantidade;
        produto->preco = preco;
    } else {
        printf("Produto nao encontrado.\n");
    }
}

int main() {
    Produto* raiz = NULL;

    int opcao, codigo, quantidade;
    float preco;
    char nome[50];

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Produto\n");
        printf("2. Excluir Produto\n");
        printf("3. Consultar Produto por nome\n");
        printf("4. Listar Produtos\n");
        printf("5. Alterar Produto\n");
        printf("6. Listar Por Letra Inicial\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);
                printf("Digite o nome do produto: ");
                scanf("%s", nome);
                printf("Digite a quantidade do produto: ");
                scanf("%d", &quantidade);
                printf("Digite o preco do produto: ");
                scanf("%f", &preco);
                raiz = inserirProduto(raiz, codigo, nome, quantidade, preco);
                break;
            case 2:
                printf("Digite o codigo do produto a ser excluido: ");
                scanf("%d", &codigo);
                raiz = excluirProduto(raiz, codigo);
                break;
            case 3:
                printf("Digite o nome do produto a ser consultado: ");
                scanf("%s", nome);
                Produto* encontrado = encontrarProduto(raiz, nome);
                if (encontrado != NULL) {
                    printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", encontrado->codigo, encontrado->nome, encontrado->quantidade, encontrado->preco);
                } else {
                    printf("Produto nao encontrado.\n");
                }
                break;
            case 4:
                printf("Produtos:\n");
                listarProdutos(raiz);
                break;
            case 5:
                printf("Digite o nome do produto a ser alterado: ");
                scanf("%s", nome);
                printf("Digite a nova quantidade do produto: ");
                scanf("%d", &quantidade);
                printf("Digite o novo preco do produto: ");
                scanf("%f", &preco);
                alterarProduto(raiz, codigo, nome, quantidade, preco);
                break;
            case 6:
                printf("Produtos:\n");
                listarProdutosPorNome(raiz);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}