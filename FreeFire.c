#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_COMPONENETES 20 // Capacidade máxima da torre

// --------------------------------------------------------------
// Estrutura que representa um componente da torre do jogador.
// Contém nome, tipo e quantidade.
// --------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// --------------------------------------------------------------
// Estrutura da TorreFuga (lista sequencial).
// Armazena até MAX_COMPONENETES componentes e controla a quantidade atual.
// --------------------------------------------------------------
typedef struct {
    Componente lista[MAX_COMPONENETES];
    int quantidade; // Quantidade atual de componentes cadastrados
} TorreFuga;

// Funções
void inicializarTorre(TorreFuga *torre);
void cadastrarComponente(TorreFuga *torre);
void removerComponente(TorreFuga *torre);
void listarComponentes(const TorreFuga *torre);
void buscarComponentePorNome(const TorreFuga *torre);
void ordenarPorNome(TorreFuga *torre);
void ordenarPorTipo(TorreFuga *torre);
void ordenarPorPrioridade(TorreFuga *torre);
void menuTorre();

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    menuTorre();

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

// --------------------------------------------------------------
// Inicializa a torre, definindo quantidade como 0.
// --------------------------------------------------------------
void inicializarTorre(TorreFuga *torre) {
    torre->quantidade = 0;
    printf("TorreFuga inicializada!\n");
}

// --------------------------------------------------------------
// Cadastra um novo componente na torre.
// Verifica se há espaço disponível antes de inserir.
// --------------------------------------------------------------
void cadastrarComponente(TorreFuga *torre) {
    if (torre->quantidade == MAX_COMPONENETES) {
        printf("Erro: TorreFuga cheia! Nao e possivel adicionar mais componentes.\n");
        return;
    }

    Componente novo;
    printf("\n--- Cadastro de Componente ---\n");
    printf("Nome do Componente: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do Componente (controle, suporte, propulsão, etc.): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    do {
        printf("Prioridade (1 a 10): ");
        scanf("%d", &novo.prioridade);
        getchar(); // limpa o buffer
        if (novo.prioridade < 1 || novo.prioridade > 10)
            printf("Valor inválido! Digite entre 1 e 10.\n");
    } while (novo.prioridade < 1 || novo.prioridade > 10);

    torre->lista[torre->quantidade] = novo;
    torre->quantidade++;

    printf("Componente \"%s\" cadastrado com sucesso!\n", novo.nome);
}

// --------------------------------------------------------------
// Remove um Componente da torre com base no nome informado.
// --------------------------------------------------------------
void removerComponente(TorreFuga *torre) {
    char nome[30];
    int pos = -1;

    printf("\n--- Remocao de Componente ---\n");
    printf("Digite o nome do Componente para remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < torre->quantidade; i++) {
        if (strcmp(torre->lista[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Componente \"%s\" nao encontrado na torre.\n", nome);
        return;
    }

    for (int i = pos; i < torre->quantidade - 1; i++) {
        torre->lista[i] = torre->lista[i + 1];
    }

    torre->quantidade--;
    printf("Componente \"%s\" removido com sucesso!\n", nome);
}

// --------------------------------------------------------------
// Lista todos os componentes atualmente armazenados na torre.
// --------------------------------------------------------------
void listarComponentes(const TorreFuga *torre) {
    if (torre->quantidade == 0) {
        printf("\nA torre esta vazia.\n");
        return;
    }

    printf("\n--- Componentes na TorreFuga ---\n");
    printf("--------------------------------------------------------------------\n");
    printf(" Nº | Nome                 | Tipo            | Quantidade\n");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < torre->quantidade; i++) {
        printf("%3d | %-20s | %-15s | %5d\n",
               i + 1,
               torre->lista[i].nome,
               torre->lista[i].tipo,
               torre->lista[i].prioridade);
        printf("--------------------------------------------------------------------\n");
    }
}

// --------------------------------------------------------------
// Busca binária por nome — só funciona após ordenação por nome.
// --------------------------------------------------------------
void buscarComponentePorNome(const TorreFuga *torre) {
    if (torre->quantidade == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }

    char chave[30];
    printf("\n--- Busca Binária ---\n");
    printf("Digite o nome do componente-chave: ");
    fgets(chave, sizeof(chave), stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int inicio = 0, fim = torre->quantidade - 1, meio;
    int comparacoes = 0;
    int encontrado = -1;

    clock_t inicio_tempo = clock();

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoes++;

        int resultado = strcmp(chave, torre->lista[meio].nome);

        if (resultado == 0) {
            encontrado = meio;
            break;
        } else if (resultado < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    clock_t fim_tempo = clock();
    double tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;

    printf("\n--- Resultado da Busca Binária ---\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);

    if (encontrado != -1) {
        printf("Componente encontrado!\n");
        printf("Nome: %-20s | Tipo: %-15s | Prioridade: %2d\n",
               torre->lista[encontrado].nome,
               torre->lista[encontrado].tipo,
               torre->lista[encontrado].prioridade);
        printf("\nComponente‑chave localizado! Torre pronta para ativação.\n");
    } else {
        printf("Componente \"%s\" não encontrado na lista.\n", chave);
    }
}

// --------------------------------------------------------------
// Bubble Sort — Ordena por nome (string)
// --------------------------------------------------------------
void ordenarPorNome(TorreFuga *torre) {
    if(torre->quantidade == 0) {
        printf("\nNenhum componente cadastrado para ordenar.\n");
        return;
    }
    int comparacoes = 0, trocas = 0;
    clock_t inicio = clock();

    for (int i = 0; i < torre->quantidade - 1; i++) {
        for (int j = 0; j < torre->quantidade - i - 1; j++) {
            comparacoes++;
            if (strcmp(torre->lista[j].nome, torre->lista[j + 1].nome) > 0) {
                Componente temp = torre->lista[j];
                torre->lista[j] = torre->lista[j + 1];
                torre->lista[j + 1] = temp;
                trocas++;
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n--- Ordenação por Nome (Bubble Sort) ---\n");
    printf("Comparações: %d | Trocas: %d | Tempo: %.6f segundos\n", comparacoes, trocas, tempo);
}

// --------------------------------------------------------------
// Insertion Sort — Ordena por tipo (string)
// --------------------------------------------------------------
void ordenarPorTipo(TorreFuga *torre) {
    int comparacoes = 0, trocas = 0;
    clock_t inicio = clock();

    for (int i = 1; i < torre->quantidade; i++) {
        Componente chave = torre->lista[i];
        int j = i - 1;

        while (j >= 0 && strcmp(torre->lista[j].tipo, chave.tipo) > 0) {
            torre->lista[j + 1] = torre->lista[j];
            j--;
            comparacoes++;
            trocas++;
        }
        torre->lista[j + 1] = chave;
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n--- Ordenação por Tipo (Insertion Sort) ---\n");
    printf("Comparações: %d | Trocas: %d | Tempo: %.6f segundos\n", comparacoes, trocas, tempo);
}

// --------------------------------------------------------------
// Selection Sort — Ordena por prioridade (int)
// --------------------------------------------------------------
void ordenarPorPrioridade(TorreFuga *torre) {
    int comparacoes = 0, trocas = 0;
    clock_t inicio = clock();

    for (int i = 0; i < torre->quantidade - 1; i++) {
        int indice_min = i;
        for (int j = i + 1; j < torre->quantidade; j++) {
            comparacoes++;
            if (torre->lista[j].prioridade < torre->lista[indice_min].prioridade)
                indice_min = j;
        }
        if (indice_min != i) {
            Componente temp = torre->lista[i];
            torre->lista[i] = torre->lista[indice_min];
            torre->lista[indice_min] = temp;
            trocas++;
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n--- Ordenação por Prioridade (Selection Sort) ---\n");
    printf("Comparações: %d | Trocas: %d | Tempo: %.6f segundos\n", comparacoes, trocas, tempo);
}


// --------------------------------------------------------------
// Menu principal do sistema de inventário.
// Permite ao jogador cadastrar, remover, listar e buscar componentes.
// --------------------------------------------------------------
void menuTorre() {
    TorreFuga torre;
    inicializarTorre(&torre);
    int opcao;
    int ordenado = 0; // 0 = não ordenado, 1 = ordenado por nome


    do {
        printf("\n=================================================================================\n");
        printf("        PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("=================================================================================\n");
        printf("Componentes na TorreFuga: %d/%d\n\n", torre.quantidade, MAX_COMPONENETES);

        // Exibe o status de ordenação
        if (ordenado) {
            printf("Status da ordenação por nome: Ordenado\n");
        } else {
            printf("Status da ordenação por nome: Não ordenado\n");
        }

        printf("\n=== MENU TORRE ===\n");
        printf("1. Cadastrar Componente (Loot)\n");
        printf("2. Remover Componente\n");
        printf("3. Listar Componentes na TorreFuga\n");
        printf("4. Buscar Componente por Nome (Busca Binária)\n");
        printf("5. Ordenar por Nome (Bubble Sort)\n");
        printf("6. Ordenar por Tipo (Insertion Sort)\n");
        printf("7. Ordenar por Prioridade (Selection Sort)\n");

        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                cadastrarComponente(&torre);
                ordenado = 0; // nova inserção pode desordenar a lista
                break;
            case 2:
                removerComponente(&torre);
                ordenado = 0; // remoção pode desordenar a lista
                break;
            case 3:
                listarComponentes(&torre);
                break;
            case 4:
                if (!ordenado) {
                    printf("Atenção: A busca binária só funciona após ordenar por nome.\n");
                    printf("Use a opção 5 (Bubble Sort) para ordenar por nome antes de buscar.\n");
                    break;
                } else {
                buscarComponentePorNome(&torre);
                }
                break;
            case 5:
                ordenarPorNome(&torre);
                ordenado = 1; // marca que agora está ordenado por nome
                printf("lista ordenada por nome! Busca binária habilitada.\n");
                break;
            case 6:
                ordenarPorTipo(&torre);
                ordenado = 0;
                printf("Lista ordenada por tipo!\n");
                break;
            case 7:
                ordenarPorPrioridade(&torre);
                printf("Lista ordenada por prioridade!\n");
                ordenado = 0;
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}