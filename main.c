
/*
** Função : Sistema de Gerenciamento de Tarefas (To-Do List)
** Autor : Erick e Daysila
** Data : 16/06/2025
** Observações: Interface principal do sistema de tarefas
*/

#include "todo.h"
#include <stdio.h>
#include <string.h>

static int proximoId = 1;

void mostrarMenu() {
    printf("\n=== SISTEMA DE GERENCIAMENTO DE TAREFAS ===\n");
    printf("1.  Adicionar tarefa (início da lista)\n");
    printf("2.  Adicionar tarefa (final da lista)\n");
    printf("3.  Agendar tarefa para data futura\n");
    printf("4.  Marcar tarefa como concluída\n");
    printf("5.  Listar TO-DO List\n");
    printf("6.  Listar tarefas concluídas\n");
    printf("7.  Listar tarefas agendadas\n");
    printf("8.  Processar tarefas vencidas\n");
    printf("9.  Desfazer última conclusão\n");
    printf("10. Buscar tarefa por ID (recursivo)\n");
    printf("11. Listar tarefas (recursivo)\n");
    printf("12. Operações com Deque\n");
    printf("13. Mostrar estatísticas\n");
    printf("0.  Sair\n");
    printf("Escolha uma opção: ");
}

void menuDeque(DequeTarefas *deque) {
    int opcao;
    char descricao[MAX_DESCRICAO];
    int prioridade;
    Tarefa tarefa;
    
    do {
        printf("\n--- OPERAÇÕES COM DEQUE ---\n");
        printf("1. Adicionar na frente\n");
        printf("2. Adicionar atrás\n");
        printf("3. Remover da frente\n");
        printf("4. Remover de trás\n");
        printf("5. Listar deque\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                printf("Descrição: ");
                fgets(descricao, MAX_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                
                printf("Prioridade (1-Baixa, 2-Média, 3-Alta): ");
                scanf("%d", &prioridade);
                getchar();
                
                tarefa = criarTarefa(proximoId++, descricao, prioridade, 0);
                adicionarFrente(deque, tarefa);
                printf("? Tarefa adicionada na frente do deque!\n");
                break;
            case 2:
                printf("Descrição: ");
                fgets(descricao, MAX_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                
                printf("Prioridade (1-Baixa, 2-Média, 3-Alta): ");
                scanf("%d", &prioridade);
                getchar();
                
                tarefa = criarTarefa(proximoId++, descricao, prioridade, 0);
                adicionarTras(deque, tarefa);
                printf("? Tarefa adicionada atrás do deque!\n");
                break;
            case 3:
                if (removerFrente(deque, &tarefa)) {
                    printf("? Tarefa removida da frente: %s\n", tarefa.descricao);
                } else {
                    printf("Deque vazio!\n");
                }
                break;
            case 4:
                if (removerTras(deque, &tarefa)) {
                    printf("? Tarefa removida de trás: %s\n", tarefa.descricao);
                } else {
                    printf("Deque vazio!\n");
                }
                break;
            case 5:
                listarDeque(deque);
                break;
        }
    } while(opcao != 0);
}

int main() {
    ListaTarefas *lista = criarLista();
    PilhaConcluidas *pilha = criarPilha();
    FilaAgendadas *fila = criarFila();
    DequeTarefas *deque = criarDeque();
    
    int opcao;
    char descricao[MAX_DESCRICAO];
    int prioridade, dataVencimento, id, dataAtual;
    Tarefa tarefa;
    NoLista *resultado;
    
    printf("=== GERENCIAMENTO DE TAREFAS ===\n");
    
    do {
        mostrarMenu();
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                printf("\n--- ADICIONAR TAREFA (INÍCIO) ---\n");
                printf("Descrição: ");
                fgets(descricao, MAX_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                
                printf("Prioridade (1-Baixa, 2-Média, 3-Alta): ");
                scanf("%d", &prioridade);
                
                printf("Data de vencimento (DDMMYYYY): ");
                scanf("%d", &dataVencimento);
                getchar();
                
                if (!validarData(dataVencimento)) {
                    printf("Data inválida! Use formato DDMMYYYY.\n");
                    break;
                }
                
                tarefa = criarTarefa(proximoId++, descricao, prioridade, dataVencimento);
                adicionarTarefaInicio(lista, tarefa);
                break;
            case 2:
                printf("\n--- ADICIONAR TAREFA (FINAL) ---\n");
                printf("Descrição: ");
                fgets(descricao, MAX_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                
                printf("Prioridade (1-Baixa, 2-Média, 3-Alta): ");
                scanf("%d", &prioridade);
                
                printf("Data de vencimento (DDMMYYYY): ");
                scanf("%d", &dataVencimento);
                getchar();
                
                if (!validarData(dataVencimento)) {
                    printf("Data inválida! Use formato DDMMYYYY.\n");
                    break;
                }
                
                tarefa = criarTarefa(proximoId++, descricao, prioridade, dataVencimento);
                adicionarTarefaFim(lista, tarefa);
                break;
            case 3:
                printf("\n--- AGENDAR TAREFA ---\n");
                printf("Descrição: ");
                fgets(descricao, MAX_DESCRICAO, stdin);
                descricao[strcspn(descricao, "\n")] = 0;
                
                printf("Prioridade (1-Baixa, 2-Média, 3-Alta): ");
                scanf("%d", &prioridade);
                
                printf("Data de vencimento (DDMMYYYY): ");
                scanf("%d", &dataVencimento);
                getchar();
                
                if (!validarData(dataVencimento)) {
                    printf("Data inválida! Use formato DDMMYYYY.\n");
                    break;
                }
                
                tarefa = criarTarefa(proximoId++, descricao, prioridade, dataVencimento);
                enfileirarTarefa(fila, tarefa);
                break;
            case 4:
                printf("\n--- MARCAR COMO CONCLUÍDA ---\n");
                listarTarefas(lista);
                printf("Digite o ID da tarefa a concluir: ");
                scanf("%d", &id);
                getchar();
                
                moverTarefaParaConcluida(lista, pilha, id);
                break;
            case 5:
                listarTarefas(lista);
                break;
            case 6:
                listarTarefasConcluidas(pilha);
                break;
            case 7:
                listarTarefasAgendadas(fila);
                break;
            case 8:
                printf("\n--- PROCESSAR TAREFAS VENCIDAS ---\n");
                printf("Digite a data atual (DDMMYYYY): ");
                scanf("%d", &dataAtual);
                getchar();
                
                if (!validarData(dataAtual)) {
                    printf("Data inválida! Use formato DDMMYYYY.\n");
                    break;
                }
                processarTarefasVencidas(fila, lista, dataAtual);
                break;
            case 9:
                printf("\n--- DESFAZER CONCLUSÃO ---\n");
                if (desempilharTarefa(pilha, &tarefa)) {
                    adicionarTarefaInicio(lista, tarefa);
                    printf("? Tarefa '%s' retornada para TO-DO List!\n", tarefa.descricao);
                }
                break;
            case 10:
                printf("\n--- BUSCAR TAREFA (RECURSIVO) ---\n");
                printf("Digite o ID da tarefa: ");
                scanf("%d", &id);
                getchar();
                
                resultado = buscarTarefaPorIdRecursivo(lista->inicio, id);
                if (resultado != NULL) {
                    printf("? Tarefa encontrada:\n");
                    printf("ID: %d\n", resultado->tarefa.id);
                    printf("Descrição: %s\n", resultado->tarefa.descricao);
                    printf("Prioridade: %s\n", obterTextoPrioridade(resultado->tarefa.prioridade));
                } else {
                    printf("Tarefa com ID %d não encontrada.\n", id);
                }
                break;
            case 11:
                printf("\n--- LISTAGEM RECURSIVA ---\n");
                printf("TO-DO List (usando recursão):\n");
                listarTarefasRecursivo(lista->inicio);
                break;
            case 12:
                menuDeque(deque);
                break;
            case 13:
                mostrarEstatisticas(lista, pilha, fila);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;  
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while(opcao != 0);

    liberarLista(lista);
    liberarPilha(pilha);
    liberarFila(fila);
    liberarDeque(deque);
    
    printf("Sistema encerrado.\n");
    return 0;
}

