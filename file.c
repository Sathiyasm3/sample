#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100 // Total memory blocks

int memory[MAX_BLOCKS] = {0}; // 0 means free, 1 means occupied

// Function to display memory status
void displayMemory() {
    printf("Memory Blocks:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

// **Contiguous File Allocation**
void contiguousAllocation() {
    int start, length;
    printf("Enter starting block: ");
    scanf("%d", &start);
    printf("Enter file length: ");
    scanf("%d", &length);

    if (start + length > MAX_BLOCKS) {
        printf("Not enough contiguous space available!\n");
        return;
    }

    for (int i = start; i < start + length; i++) {
        if (memory[i] == 1) {
            printf("Block %d already occupied. Contiguous allocation failed.\n", i);
            return;
        }
    }

    for (int i = start; i < start + length; i++) {
        memory[i] = 1;
    }

    printf("File allocated from block %d to %d.\n", start, start + length - 1);
    displayMemory();
}

// **Indexed File Allocation**
void indexedAllocation() {
    int fileID, numBlocks;
    printf("Enter file ID: ");
    scanf("%d", &fileID);
    printf("Enter number of blocks: ");
    scanf("%d", &numBlocks);

    int blocks[numBlocks];
    printf("Enter block numbers:\n");
    for (int i = 0; i < numBlocks; i++) {
        scanf("%d", &blocks[i]);
        if (memory[blocks[i]] == 1) {
            printf("Block %d is already occupied. Indexed allocation failed.\n", blocks[i]);
            return;
        }
    }

    printf("File %d allocated at index block. Data blocks: ", fileID);
    for (int i = 0; i < numBlocks; i++) {
        memory[blocks[i]] = 1;
        printf("%d ", blocks[i]);
    }
    printf("\n");
    displayMemory();
}

// **Linked File Allocation**
void linkedAllocation() {
    int fileID, numBlocks;
    printf("Enter file ID: ");
    scanf("%d", &fileID);
    printf("Enter number of blocks: ");
    scanf("%d", &numBlocks);

    int blocks[numBlocks];
    printf("Enter block numbers:\n");
    for (int i = 0; i < numBlocks; i++) {
        scanf("%d", &blocks[i]);
        if (memory[blocks[i]] == 1) {
            printf("Block %d is already occupied. Linked allocation failed.\n", blocks[i]);
            return;
        }
    }

    printf("File %d allocated. Blocks: ", fileID);
    for (int i = 0; i < numBlocks; i++) {
        memory[blocks[i]] = 1;
        printf("%d -> ", blocks[i]);
    }
    printf("NULL\n");

    displayMemory();
}

int main() {
    int choice;
    
    while (1) {
        printf("\nFile Allocation Strategies:\n");
        printf("1. Contiguous Allocation\n2. Indexed Allocation\n3. Linked Allocation\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                contiguousAllocation();
                break;
            case 2:
                indexedAllocation();
                break;
            case 3:
                linkedAllocation();
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

