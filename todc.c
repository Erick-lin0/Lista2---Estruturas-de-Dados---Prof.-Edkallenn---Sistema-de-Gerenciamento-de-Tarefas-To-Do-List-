
/*
** Função : Sistema de Gerenciamento de Tarefas (To-Do List)
** Autor : Erick e Daysila
** Data : 16/06/2025
** Observações: Implementação completa do sistema de tarefas
*/

#include "todo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int proximoId = 1; // id unico

// LISTA ENCADEADA 

ListaTarefas* criarLista() {
    ListaTarefas *lista = (ListaTarefas*)malloc(sizeof(ListaTarefas));
    if (lista == NULL) {
        printf("Error\n");
        return NULL;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

void adicionarTarefaInicio(ListaTarefas *lista, Tarefa tarefa) {
    NoLista *novoNo = (NoLista*)malloc(sizeof(NoLista));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->tarefa = tarefa;
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
    lista->tamanho++;
    
    printf("? Tarefa adicionada no início da lista!\n");
}

void adicionarTarefaFim(ListaTarefas *lista, Tarefa tarefa) {
    NoLista *novoNo = (NoLista*)malloc(sizeof(NoLista));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->tarefa = tarefa;
    novoNo->proximo = NULL;
    
    if (lista->inicio == NULL) {
        lista->inicio = novoNo;
    } else {
        NoLista *atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    
    lista->tamanho++;
    printf("? Tarefa adicionada no final da lista!\n");
}

int removerTarefaPorId(ListaTarefas *lista, int id, Tarefa *tarefaRemovida) {
    if (lista->inicio == NULL) {
        printf("A lista vazia!\n");
        return 0;
    }
    
    NoLista *atual = lista->inicio;
    NoLista *anterior = NULL;
    
    while (atual != NULL && atual->tarefa.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("Tarefa com ID %d não encontrada!\n", id);
        return 0;
    }
    
    *tarefaRemovida = atual->tarefa;
    
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    free(atual);
    lista->tamanho--;
    return 1;
}

void listarTarefas(ListaTarefas *lista) {
    printf("\n=== TO-DO LIST ===\n");
    if (lista->inicio == NULL) {
        printf("Nenhuma tarefa na lista.\n");
        return;
    }
    
    printf("Total de tarefas: %d\n", lista->tamanho);
    printf("----------------------------------------\n");
    
    NoLista *atual = lista->inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%d. [ID:%d] %s\n", contador, atual->tarefa.id, atual->tarefa.descricao);
        printf("   Prioridade: %s | Vencimento: %08d\n", 
            obterTextoPrioridade(atual->tarefa.prioridade), 
            atual->tarefa.dataVencimento);
        atual = atual->proximo;
        contador++;
    }
    printf("----------------------------------------\n");
}

void liberarLista(ListaTarefas *lista) {
    if (lista == NULL) return;
    
    NoLista *atual = lista->inicio;
    while (atual != NULL) {
        NoLista *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}
//--------------------------------------------------------------------------------------------------------------------

//PILHA

PilhaConcluidas* criarPilha() {
    PilhaConcluidas *pilha = (PilhaConcluidas*)malloc(sizeof(PilhaConcluidas));
    if (pilha == NULL) {
        printf("Erro: Não foi possível alocar memória para pilha.\n");
        return NULL;
    }
    pilha->topo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

void empilharTarefa(PilhaConcluidas *pilha, Tarefa tarefa) {
    NoPilha *novoNo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novoNo == NULL) {
        printf("Erro: Não foi possível alocar memória.\n");
        return;
    }
    
    novoNo->tarefa = tarefa;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
    pilha->tamanho++;
    
    printf("? Tarefa marcada como concluída!\n");
}

int desempilharTarefa(PilhaConcluidas *pilha, Tarefa *tarefa) {
    if (pilha->topo == NULL) {
        printf("Nenhuma tarefa concluída para desfazer!\n");
        return 0;
    }
    
    NoPilha *topo = pilha->topo;
    *tarefa = topo->tarefa;
    pilha->topo = topo->proximo;
    free(topo);
    pilha->tamanho--;
    
    return 1;
}

void listarTarefasConcluidas(PilhaConcluidas *pilha) {
    printf("\n=== TAREFAS CONCLUÍDAS ===\n");
    if (pilha->topo == NULL) {
        printf("Nenhuma tarefa concluída.\n");
        return;
    }
    
    printf("Total de tarefas concluídas: %d\n", pilha->tamanho);
    printf("(Última concluída primeiro)\n");
    printf("----------------------------------------\n");
    
    NoPilha *atual = pilha->topo;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%d. [ID:%d] %s\n", contador, atual->tarefa.id, atual->tarefa.descricao);
        printf("   Prioridade: %s\n", obterTextoPrioridade(atual->tarefa.prioridade));
        atual = atual->proximo;
        contador++;
    }
    printf("----------------------------------------\n");
}

void liberarPilha(PilhaConcluidas *pilha) {
    if (pilha == NULL) return;
    
    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(pilha);
}

//-------------------------------------------------------------------------------------------------------

// FILA

FilaAgendadas* criarFila() {
    FilaAgendadas *fila = (FilaAgendadas*)malloc(sizeof(FilaAgendadas));
    if (fila == NULL) {
        printf("Erro: Não foi possível alocar memória para fila.\n");
        return NULL;
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    return fila;
}

void enfileirarTarefa(FilaAgendadas *fila, Tarefa tarefa) {
    NoFila *novoNo = (NoFila*)malloc(sizeof(NoFila));
    if (novoNo == NULL) {
        printf("Erro.\n");
        return;
    }
    
    novoNo->tarefa = tarefa;
    novoNo->proximo = NULL;
    
    if (fila->fim == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
    
    fila->tamanho++;
    printf("? Tarefa agendada para %08d!\n", tarefa.dataVencimento);
}

int desenfileirarTarefa(FilaAgendadas *fila, Tarefa *tarefa) {
    if (fila->inicio == NULL) {
        return 0;
    }
    
    NoFila *primeiro = fila->inicio;
    *tarefa = primeiro->tarefa;
    fila->inicio = primeiro->proximo;
    
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(primeiro);
    fila->tamanho--;
    return 1;
}

void processarTarefasVencidas(FilaAgendadas *fila, ListaTarefas *lista, int dataAtual) {
    printf("\n>>> Processando tarefas vencidas...\n");
    int processadas = 0;
    
    while (fila->inicio != NULL && fila->inicio->tarefa.dataVencimento <= dataAtual) {
        Tarefa tarefa;
        if (desenfileirarTarefa(fila, &tarefa)) {
            adicionarTarefaFim(lista, tarefa);
            printf("Tarefa movida para TO-DO: %s\n", tarefa.descricao);
            processadas++;
        }
    }
    
    if (processadas == 0) {
        printf("Nenhuma tarefa vencida para processar.\n");
    } else {
        printf("? %d tarefa(s) movida(s) para a TO-DO List!\n", processadas);
    }
}

void listarTarefasAgendadas(FilaAgendadas *fila) {
    printf("\n=== TAREFAS AGENDADAS ===\n");
    if (fila->inicio == NULL) {
        printf("Nenhuma tarefa agendada.\n");
        return;
    }
    
    printf("Total de tarefas agendadas: %d\n", fila->tamanho);
    printf("----------------------------------------\n");
    
    NoFila *atual = fila->inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%d. [ID:%d] %s\n", contador, atual->tarefa.id, atual->tarefa.descricao);
        printf("   Prioridade: %s | Agendada para: %08d\n", 
            obterTextoPrioridade(atual->tarefa.prioridade), 
            atual->tarefa.dataVencimento);
        atual = atual->proximo;
        contador++;
    }
    printf("----------------------------------------\n");
}

void liberarFila(FilaAgendadas *fila) {
    if (fila == NULL) return;
    
    NoFila *atual = fila->inicio;
    while (atual != NULL) {
        NoFila *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(fila);
}

//------------------------------------------------------------------------------------------

// DEQUE

DequeTarefas* criarDeque() {
    DequeTarefas *deque = (DequeTarefas*)malloc(sizeof(DequeTarefas));
    if (deque == NULL) {
        printf("Error\n");
        return NULL;
    }
    deque->inicio = NULL;
    deque->fim = NULL;
    deque->tamanho = 0;
    return deque;
}

void adicionarFrente(DequeTarefas *deque, Tarefa tarefa) {
    NoDeque *novoNo = (NoDeque*)malloc(sizeof(NoDeque));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->tarefa = tarefa;
    novoNo->anterior = NULL;
    novoNo->proximo = deque->inicio;
    
    if (deque->inicio == NULL) {
        deque->fim = novoNo;
    } else {
        deque->inicio->anterior = novoNo;
    }
    
    deque->inicio = novoNo;
    deque->tamanho++;
}

void adicionarTras(DequeTarefas *deque, Tarefa tarefa) {
    NoDeque *novoNo = (NoDeque*)malloc(sizeof(NoDeque));
    if (novoNo == NULL) {
        printf("Error\n");
        return;
    }
    
    novoNo->tarefa = tarefa;
    novoNo->proximo = NULL;
    novoNo->anterior = deque->fim;
    
    if (deque->fim == NULL) {
        deque->inicio = novoNo;
    } else {
        deque->fim->proximo = novoNo;
    }
    
    deque->fim = novoNo;
    deque->tamanho++;
}

int removerFrente(DequeTarefas *deque, Tarefa *tarefa) {
    if (deque->inicio == NULL) {
        return 0;
    }
    
    NoDeque *primeiro = deque->inicio;
    *tarefa = primeiro->tarefa;
    
    deque->inicio = primeiro->proximo;
    if (deque->inicio == NULL) {
        deque->fim = NULL;
    } else {
        deque->inicio->anterior = NULL;
    }
    
    free(primeiro);
    deque->tamanho--;
    return 1;
}

int removerTras(DequeTarefas *deque, Tarefa *tarefa) {
    if (deque->fim == NULL) {
        return 0;
    }
    
    NoDeque *ultimo = deque->fim;
    *tarefa = ultimo->tarefa;
    
    deque->fim = ultimo->anterior;
    if (deque->fim == NULL) {
        deque->inicio = NULL;
    } else {
        deque->fim->proximo = NULL;
    }
    
    free(ultimo);
    deque->tamanho--;
    return 1;
}

void listarDeque(DequeTarefas *deque) {
    printf("\n=== DEQUE DE TAREFAS ===\n");
    if (deque->inicio == NULL) {
        printf("Deque vazio.\n");
        return;
    }
    
    printf("Total no deque: %d\n", deque->tamanho);
    printf("----------------------------------------\n");
    
    NoDeque *atual = deque->inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%d. [ID:%d] %s\n", contador, atual->tarefa.id, atual->tarefa.descricao);
        printf("   Prioridade: %s\n", obterTextoPrioridade(atual->tarefa.prioridade));
        atual = atual->proximo;
        contador++;
    }
    printf("----------------------------------------\n");
}

void liberarDeque(DequeTarefas *deque) {
    if (deque == NULL) return;
    
    NoDeque *atual = deque->inicio;
    while (atual != NULL) {
        NoDeque *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(deque);
}

// inicio das funcoes

int contarTarefasRecursivo(NoLista *no) {
    if (no == NULL) {
        return 0;
    }
    return 1 + contarTarefasRecursivo(no->proximo);
}

void listarTarefasRecursivo(NoLista *no) {
    if (no == NULL) {
        return;
    }
    
    printf("- [ID:%d] %s (Prioridade: %s)\n", 
        no->tarefa.id, 
        no->tarefa.descricao, 
        obterTextoPrioridade(no->tarefa.prioridade));
    
    listarTarefasRecursivo(no->proximo);
}

NoLista* buscarTarefaPorIdRecursivo(NoLista *no, int id) {
    if (no == NULL) {
        return NULL;
    }
    
    if (no->tarefa.id == id) {
        return no;
    }
    
    return buscarTarefaPorIdRecursivo(no->proximo, id);
}


Tarefa criarTarefa(int id, char *descricao, int prioridade, int dataVencimento) {
    Tarefa tarefa;
    tarefa.id = id;
    strncpy(tarefa.descricao, descricao, MAX_DESCRICAO - 1);
    tarefa.descricao[MAX_DESCRICAO - 1] = '\0';
    tarefa.prioridade = prioridade;
    tarefa.dataVencimento = dataVencimento;
    return tarefa;
}

void mostrarEstatisticas(ListaTarefas *lista, PilhaConcluidas *pilha, FilaAgendadas *fila) {
    printf("\n=== ESTATÍSTICAS DO SISTEMA ===\n");
    printf("TO-DO List: %d tarefa(s)\n", lista->tamanho);
    printf("Tarefas Concluídas: %d\n", pilha->tamanho);
    printf("Tarefas Agendadas: %d\n", fila->tamanho);
    

    int totalRecursivo = contarTarefasRecursivo(lista->inicio);
    printf("Total (contagem recursiva): %d tarefa(s)\n", totalRecursivo);
    
    printf("================================\n");
}


char* obterTextoPrioridade(int prioridade) {
    switch (prioridade) {
        case 1: return "Baixa";
        case 2: return "Média";
        case 3: return "Alta";
        default: return "";
    }
}

void moverTarefaParaConcluida(ListaTarefas *lista, PilhaConcluidas *pilha, int id) {
    Tarefa tarefa;
    if (removerTarefaPorId(lista, id, &tarefa)) {
        empilharTarefa(pilha, tarefa);
        printf("Tarefa '%s' concluída com sucesso!\n", tarefa.descricao);
    }
}

