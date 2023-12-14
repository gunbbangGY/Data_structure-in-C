#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 20
#define MAX_ROWS 20
#define MAX_COLS 20

int row = 0, col = 0;

typedef struct GraphType {
    int n;	// ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    g->adj_mat[start][end] = 1;
}
// ���� ��� ��� �Լ�
void print_adj_mat(GraphType* g)
{
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}
// �̷� Ž�� �Լ�
void maze(GraphType* g, int v_col, int v_row)
{
    g->adj_mat[v_col][v_row] = 2;

    if (g->adj_mat[col+1][row+1] == 2) return;
    print_adj_mat(g);
    printf("\n");
    int w;

    if (g->adj_mat[(v_col)+1][v_row]==1) maze(g, (v_col)+1, v_row);
    if (g->adj_mat[v_col][v_row + 1]) maze(g, v_col, (v_row)+1);
    else return;
}

int main() {
    int i = 0, j = 0;
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    char ch;

    char data[MAX_VERTICES][MAX_VERTICES];
    FILE* fp = fopen("data2.txt", "r");
    if (fp == NULL) {
        printf("������ �� �� ����\n");
        return 0;
    }
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            row++;
            col = 0;
        }
        else if (col < MAX_COLS) {
            data[row][col] = ch - '0';
            col++;
        }
        else {
            fprintf(stderr, "���� ���� �ʰ�\n");
            return 1;
        }
    }

    fclose(fp);

    printf("�о�� ������:\n");
    for (int i = 0; i <= row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < row + 1; i++) insert_vertex(g, i);
    for (i = 0; i < row + 1; i++) {
        for (j = 0; j < col + 1; j++) {
            g->adj_mat[i][j] = data[i][j];
        }
    }
    maze(g, 0, 0);
    printf("\n");



    return 0;
}
