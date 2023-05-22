#include "../include/graph.h"

//Задание графа
void inputGraph(Graph_t* graph, int count, FILE *file_txt){
    char temp[LEN];
    int *vertices = malloc(sizeof(int) * count * 2);
    int num_vertices = 0;
    graph->edges = (Edge_t**)malloc(sizeof(Edge_t*) * count);
    for (int i = 0; i < count; i++){
        int found_from = 0;
        int found_to = 0;
        graph->edges[i] = (Edge_t*)malloc(sizeof(Edge_t));
        fgets(temp, sizeof(temp), file_txt);
        sscanf(temp, "%d %d", &graph->edges[i]->vert_from, &graph->edges[i]->vert_to);
        for(int j = 0; j < num_vertices; j++){
            if (vertices[j] == graph->edges[i]->vert_from) {
                found_from = 1;
            }
            if (vertices[j] == graph->edges[i]->vert_to) {
                found_to = 1;
            }
        }
        // добавляем вершины в массив, если их нет
        if (!found_from) {
            vertices[num_vertices] = graph->edges[i]->vert_from;
            if (!graph->edges[i]->vert_from == graph->edges[i]->vert_to) num_vertices++;
        }
        if (!found_to) {
            vertices[num_vertices] = graph->edges[i]->vert_to;
            num_vertices++;
        }
        graph->num_edges = i+1;
    }
    graph->num_vertices = num_vertices;
    free(vertices);
}

//Вывод графа
void outputGraph(Graph_t* graph){
    FILE *file_graph;
    file_graph = fopen("../data/graph.dot", "w");
    fprintf(file_graph, "graph current_graph {\n");
    for (int i = 0; i < graph->num_edges; i++){
        fprintf(file_graph, " %d -- %d;\n", graph->edges[i]->vert_from, graph->edges[i]->vert_to);
    }
    fprintf(file_graph, "}");
    fclose(file_graph);
}

void dfs(Graph_t *graph, int *visited, int vertex) {
    visited[vertex] = 1; // помечаем вершину как посещенную
    for (int i = 0; i < graph->num_edges; i++) {
        Edge_t *edge = graph->edges[i];
        if (!visited[edge->vert_to] && edge->vert_from == vertex) {
            dfs(graph, visited, edge->vert_to); // рекурсивно обходим следующую вершину
        }
    }
}

//Проверка на связность
int is_connected(Graph_t *graph) {
    graph->visited = calloc(graph->num_vertices, sizeof(int)); // инициализируем массив посещенных вершин
    dfs(graph, graph->visited, 0);
    for (int i = 0; i < graph->num_vertices; i++) {
        if (!graph->visited[i]) {
            free(graph->visited);
            return 0; // если есть непосещенные вершины, то граф не связный
        }
    }
    free(graph->visited);
    return 1; // все вершины были посещены, граф связный
}

//Удаление графа и очищение памяти
void clear_memory(int count, Graph_t* graph){
    for (int i = 0; i < count; i++) {
        free(graph->edges[i]);
    }
    free(graph->edges);
}