#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100000 // ������ ������ ����
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int list[MAX_SIZE];
int n;

int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        do
            low++;
        while (list[low] < pivot);
        do
            high--;
        while (list[high] > pivot);
        if (low < high)
            SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}

void quick_sort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

int main(void) {
    int i;
    n = MAX_SIZE;
    srand(time(NULL));
    for (i = 0; i < n; i++) // ���� ���� �� ���
        list[i] = rand() % 100000;

    clock_t start_time, end_time;
    double total_time;

    start_time = clock();
    quick_sort(list, 0, n - 1); // ������ ȣ��
    end_time = clock();

    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");

    printf("���� �ð�: %.3lf ��\n", total_time);

    return 0;
}