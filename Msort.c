#include <stdio.h>
#include <time.h>

#define MAX_SIZE 10000 // 변경할 데이터 개수

int sorted[MAX_SIZE]; // 추가 공간이 필요

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;

    while (i <= mid && j <= right) {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid)
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    else
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];

    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main(void) {
    int list[MAX_SIZE];
    int n = MAX_SIZE;
    int i;

    // 난수 생성 및 출력
    for (i = 0; i < n; i++)
        list[i] = rand() % 10000;

    clock_t start_time, end_time;
    double total_time;

    start_time = clock();
    merge_sort(list, 0, n - 1); // 병합 정렬 호출
    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++)
        printf("%d ", list[i]);

    printf("\n실행 시간: %.3lf 초\n", total_time);

    return 0;
}