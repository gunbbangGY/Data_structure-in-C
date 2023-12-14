#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ĳ�� Ư��
int numSets = 0;
int numBlocks = 0;
int blockSize = 0;
int writeAllocate = 0;
int writeThrough = 0;
int evictionPolicy = 0;

// �����
int totalLoads = 0;
int totalStores = 0;
int loadHits = 0;
int loadMisses = 0;
int storeHits = 0;
int storeMisses = 0;
int totalCycles = 0;

// ĳ�� ����
typedef struct {
    int valid;
    int dirty;
    int tag;
    int lastUsedCycle;
} CacheBlock;

CacheBlock** cache;

// ĳ�� ���� �Լ�
void initializeCache() {
    cache = (CacheBlock**)malloc(numSets * sizeof(CacheBlock*));
    if (cache == NULL) {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    for (int i = 0; i < numSets; i++) {
        cache[i] = (CacheBlock*)malloc(numBlocks * sizeof(CacheBlock));
        if (cache[i] == NULL) {
            printf("�޸� �Ҵ� ����\n");
            exit(1);
        }
        for (int j = 0; j < numBlocks; j++) {
            cache[i][j].valid = 0;
            cache[i][j].dirty = 0;
            cache[i][j].tag = -1;
            cache[i][j].lastUsedCycle = -1;
        }
    }
}

// ������ �׼��� �ùķ���Ʈ
void simulateCacheAccess(char accessType, int address) {
    int setIndex = (address / blockSize) % numSets;
    int tag = address / (blockSize * numSets);

    CacheBlock* set = cache[setIndex];

    for (int i = 0; i < numBlocks; i++) {
        if (set[i].valid && set[i].tag == tag) {
            if (accessType == 'l') loadHits++;
            else {
                storeHits++;
                if (writeThrough) totalCycles += 100;
                else set[i].dirty = 1;
            }
            set[i].lastUsedCycle = totalCycles;
            return;
        }
    }

    if (accessType == 'l') {
        loadMisses++;
        totalCycles += 100 * (blockSize / 4);
    }
    else {
        storeMisses++;
        if (writeAllocate) totalCycles += 100 * (blockSize / 4);
        if (writeThrough) totalCycles += 100;
        else totalCycles += 100 * (blockSize / 4);
    }

    int evictIndex = 0;
    if (evictionPolicy == 0) {  // LRU
        int minCycle = set[0].lastUsedCycle;
        for (int i = 1; i < numBlocks; i++) {
            if (set[i].lastUsedCycle < minCycle) {
                minCycle = set[i].lastUsedCycle;
                evictIndex = i;
            }
        }
    }
    else if (evictionPolicy == 1) {  // FIFO
        int minCycle = set[0].lastUsedCycle;
        evictIndex = 0;  // �ʱⰪ ����
        for (int i = 1; i < numBlocks; i++) {
            if (set[i].lastUsedCycle < minCycle) {
                minCycle = set[i].lastUsedCycle;
                evictIndex = i;
            }
            else if (set[i].lastUsedCycle == -1) {
                evictIndex = i;  // lastUsedCycle�� -1�� ����� FIFO�� ������� ����
                break;
            }
        }
    }
    else if (evictionPolicy == 2) {  // Random
        evictIndex = rand() % numBlocks;
    }

    if (set[evictIndex].dirty) {
        totalCycles += 100 * (blockSize / 4);
    }
    set[evictIndex].valid = 1;
    set[evictIndex].dirty = (accessType == 's' && !writeThrough);
    set[evictIndex].tag = tag;
    set[evictIndex].lastUsedCycle = totalCycles;
}

int main() {

    printf("ĳ�� �뷮 �Է� : (setCount, blockCount, blockSize)\n");
    int result = scanf("%d %d %d", &numSets, &numBlocks, &blockSize);
    if (result != 3) {
        printf("�Է� ����\n");
        return 1;
    }

    printf("writeAllocate �Է� : (no-write-allocate=0, write-allocate=1): ");
    scanf("%d", &writeAllocate);
    printf("writeThrough (write-back=0, write-through=1): ");
    scanf("%d", &writeThrough);

    printf("evictionPolicy (LRU=0, FIFO=1, random=2): ");
    scanf("%d", &evictionPolicy);

    initializeCache();

    FILE* file = fopen("read01.trace", "r");
    if (file == NULL) {
        printf("���� ���� ����\n");
        return 1;
    }

    char accessType;
    int address;
    while (fscanf(file, " %c %x", &accessType, &address) != EOF) {
        if (accessType == 'l') totalLoads++;
        else if (accessType == 's') totalStores++;
        else continue;
        simulateCacheAccess(accessType, address);
    }
    fclose(file);

    printf("Total loads: %d\n", totalLoads);
    printf("Total stores: %d\n", totalStores);
    printf("Load hits: %d\n", loadHits);
    printf("Load misses: %d\n", loadMisses);
    printf("Store hits: %d\n", storeHits);
    printf("Store misses: %d\n", storeMisses);
    printf("Total cycles: %d\n", totalCycles);

    for (int i = 0; i < numSets; i++) {
        free(cache[i]);
    }
    free(cache);

    return 0;
}