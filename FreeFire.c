#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10 // Capacidade máxima da mochila

// --------------------------------------------------------------
// Estrutura que representa um item da mochila do jogador.
// Contém nome, tipo e quantidade.
// --------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --------------------------------------------------------------
// Estrutura da mochila (lista sequencial).
// Armazena até MAX_ITENS itens e controla a quantidade atual.
// --------------------------------------------------------------
typedef struct {
    Item itens[MAX_ITENS];
    int quantidade;
} Mochila;

// Funções
void inicializarMochila(Mochila *mochila);
void cadastrarItem(Mochila *mochila);
void removerItem(Mochila *mochila);
void listarItens(const Mochila *mochila) ;
void buscarItem(const Mochila *mochila);
void menuMochila();

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    menuMochila();

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.


// --------------------------------------------------------------
// Inicializa a mochila, definindo quantidade como 0.
// --------------------------------------------------------------
void inicializarMochila(Mochila *mochila) {
    mochila->quantidade = 0;
    printf("Mochila inicializada!\n");
}

// --------------------------------------------------------------
// Cadastra um novo item na mochila.
// Verifica se há espaço disponível antes de inserir.
// --------------------------------------------------------------
void cadastrarItem(Mochila *mochila) {
    if (mochila->quantidade == MAX_ITENS) {
        printf("Erro: Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- Cadastro de Item ---\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpa o buffer

    mochila->itens[mochila->quantidade] = novo;
    mochila->quantidade++;

    printf("Item \"%s\" cadastrado com sucesso!\n", novo.nome);
}

// --------------------------------------------------------------
// Remove um item da mochila com base no nome informado.
// --------------------------------------------------------------
void removerItem(Mochila *mochila) {
    char nome[30];
    int pos = -1;

    printf("\n--- Remocao de Item ---\n");
    printf("Digite o nome do item para remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item \"%s\" nao encontrado na mochila.\n", nome);
        return;
    }

    for (int i = pos; i < mochila->quantidade - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }

    mochila->quantidade--;
    printf("Item \"%s\" removido com sucesso!\n", nome);
}

// --------------------------------------------------------------
// Lista todos os itens atualmente armazenados na mochila.
// --------------------------------------------------------------
void listarItens(const Mochila *mochila) {
    if (mochila->quantidade == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    printf("--------------------------------------------------------------------\n");
    printf(" Nº | Nome                 | Tipo            | Quantidade\n");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < mochila->quantidade; i++) {
        printf("%3d | %-20s | %-15s | %5d\n",
               i + 1,
               mochila->itens[i].nome,
               mochila->itens[i].tipo,
               mochila->itens[i].quantidade);
        printf("--------------------------------------------------------------------\n");
    }
}

// --------------------------------------------------------------
// NIVEL AVENTUREIRO
// Busca um item na mochila pelo nome usando busca sequencial.
// Busca sequencial por um item com base no nome informado.
// Exibe os dados do item encontrado.
// --------------------------------------------------------------
void buscarItem(const Mochila *mochila) {
    char nome[30];
    printf("\n--- Busca de Item ---\n");
    printf("Digite o nome do item para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < mochila->quantidade; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %-20s | Tipo: %-15s | Quantidade: %5d\n",
                   mochila->itens[i].nome,
                   mochila->itens[i].tipo,
                   mochila->itens[i].quantidade);
            return;
        }
    }

    printf("Item \"%s\" nao encontrado na mochila.\n", nome);
}

// --------------------------------------------------------------
// Menu principal do sistema de inventário.
// Permite ao jogador cadastrar, remover, listar e buscar itens.
// --------------------------------------------------------------
void menuMochila() {
    Mochila mochila;
    inicializarMochila(&mochila);
    int opcao;

    do {
        printf("\n=================================================================================\n");
        printf("        MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("=================================================================================\n");
        printf("Itens na Mochila: %d/%d\n\n", mochila.quantidade, MAX_ITENS);
        printf("\n=== MENU MOCHILA ===\n");
        printf("1. Cadastrar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                cadastrarItem(&mochila);
                listarItens(&mochila);
                break;
            case 2:
                removerItem(&mochila);
                listarItens(&mochila);
                break;
            case 3:
                listarItens(&mochila);
                break;
            case 4:
                buscarItem(&mochila);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}