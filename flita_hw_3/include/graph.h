#ifndef FLITA_HW_2_GRAPH_H
#define FLITA_HW_2_GRAPH_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LEN 100

typedef struct {
    int vert_from;
    int vert_to;
} Edge_t;

typedef struct {
    int num_vertices;
    int num_edges;
    Edge_t **edges;
    int *visited;
} Graph_t;

void inputGraph(Graph_t* graph, int count, FILE *file_txt); // Задание графа
void outputGraph(Graph_t* graph); // Вывод графа
void clear_memory(int count, Graph_t* graph); // Удаление графа и очищение памяти

#endif //FLITA_HW_2_GRAPH_H
