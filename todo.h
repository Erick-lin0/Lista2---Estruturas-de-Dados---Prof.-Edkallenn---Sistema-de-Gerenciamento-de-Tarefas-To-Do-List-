
/*
** Função : Sistema de Gerenciamento de Tarefas (To-Do List)
** Autor : Erick e Daysila
** Data : 16/06/2025
** Observações: Interface do sistema de tarefas com diferentes estruturas de dados
*/

#ifndef TODO_H
#define TODO_H

#define MAX_DESCRICAO 100

// TAD 
typedef struct {
    char descricao[MAX_DESCRICAO];
    int prioridade; 
    int dataVencimento; 
    int id; 
} Tarefa;


typedef struct NoLista {
    Tarefa tarefa;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
    int tamanho;
} ListaTarefas;

// FUNÇÕES
ListaTarefas* criarLista();
void adicionarTarefaInicio(ListaTarefas *lista, Tarefa tarefa);
void adicionarTarefaFim(ListaTarefas *lista, Tarefa tarefa);
int removerTarefaPorId(ListaTarefas *lista, int id, Tarefa *tarefaRemovida);
void listarTarefas(ListaTarefas *lista);
void liberarLista(ListaTarefas *lista);


typedef struct NoPilha {
    Tarefa tarefa;
    struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int tamanho;
} PilhaConcluidas;


PilhaConcluidas* criarPilha();
void empilharTarefa(PilhaConcluidas *pilha, Tarefa tarefa);
int desempilharTarefa(PilhaConcluidas *pilha, Tarefa *tarefa);
void listarTarefasConcluidas(PilhaConcluidas *pilha);
void liberarPilha(PilhaConcluidas *pilha);


typedef struct NoFila {
    Tarefa tarefa;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} FilaAgendadas;


FilaAgendadas* criarFila();
void enfileirarTarefa(FilaAgendadas *fila, Tarefa tarefa);
int desenfileirarTarefa(FilaAgendadas *fila, Tarefa *tarefa);
void processarTarefasVencidas(FilaAgendadas *fila, ListaTarefas *lista, int dataAtual);
void listarTarefasAgendadas(FilaAgendadas *fila);
void liberarFila(FilaAgendadas *fila);


typedef struct NoDeque {
    Tarefa tarefa;
    struct NoDeque *anterior;
    struct NoDeque *proximo;
} NoDeque;

typedef struct {
    NoDeque *inicio;
    NoDeque *fim;
    int tamanho;
} DequeTarefas;


DequeTarefas* criarDeque();
void adicionarFrente(DequeTarefas *deque, Tarefa tarefa);
void adicionarTras(DequeTarefas *deque, Tarefa tarefa);
int removerFrente(DequeTarefas *deque, Tarefa *tarefa);
int removerTras(DequeTarefas *deque, Tarefa *tarefa);
void listarDeque(DequeTarefas *deque);
void liberarDeque(DequeTarefas *deque);


int contarTarefasRecursivo(NoLista *no);
void listarTarefasRecursivo(NoLista *no);
NoLista* buscarTarefaPorIdRecursivo(NoLista *no, int id);


Tarefa criarTarefa(int id, char *descricao, int prioridade, int dataVencimento);
void mostrarEstatisticas(ListaTarefas *lista, PilhaConcluidas *pilha, FilaAgendadas *fila);
int validarData(int data);
char* obterTextoPrioridade(int prioridade);
void moverTarefaParaConcluida(ListaTarefas *lista, PilhaConcluidas *pilha, int id);

#endif

