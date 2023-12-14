#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 20
#define MAX_ROWS 20
#define MAX_COLS 20

int row = 0, col = 0;

typedef struct GraphType {
    int n;	// 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
}
// 인접 행렬 출력 함수
void print_adj_mat(GraphType* g)
{
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%2d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}
// 미로 탐색 함수
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
        printf("파일을 열 수 없음\n");
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
            fprintf(stderr, "열의 개수 초과\n");
            return 1;
        }
    }

    fclose(fp);

    printf("읽어온 데이터:\n");
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
