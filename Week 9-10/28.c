#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SECTORS 1000
#define MAX_FILES 100
struct file {
    char name;
    int start_block;
    int no_of_blocks;
    int flag;
};
struct block {
    int current;
    int next;
};
int main(void){
    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);
    struct file files[n];
    struct block sector[SECTORS];
    for (int i = 0; i < SECTORS; i++) {
        sector[i].current = 0;
        sector[i].next = -1;
    }
    for (int i = 0; i < n; i++) {
        printf("\nEnter file %d name: ", i + 1);
        scanf(" %c", &files[i].name);
        printf("Enter starting block of file %c: ", files[i].name);
        scanf("%d", &files[i].start_block);
        printf("Enter number of blocks for file %c: ", files[i].name);
        scanf("%d", &files[i].no_of_blocks);
        files[i].flag = 0;
    }
    for (int i = 0; i < n; i++) {
        int req = files[i].no_of_blocks, start = files[i].start_block;
        if (start < 0 || start >= SECTORS || sector[start].current != 0) {
            files[i].flag = 0;
            continue;
        }
        int allocated_count = 0, prev_index = -1, first_allocated = -1;
        for (int j = start; j < SECTORS && allocated_count < req; j++) {
            if (sector[j].current == 0) {
                sector[j].current = 1;
                sector[j].next = -1;
                if (prev_index != -1) sector[prev_index].next = j;
                else first_allocated = j;
                prev_index = j;
                allocated_count++;
            }
        }
        if (allocated_count == req) {
            files[i].flag = 1;
            files[i].start_block = first_allocated;
        } else {
            int j = first_allocated;
            while (j != -1) {
                int next = sector[j].next;
                sector[j].current = 0;
                sector[j].next = -1;
                j = next;
            }
            files[i].flag = 0;
            files[i].start_block = -1;
        }
    }
    char ch;
    printf("\nEnter the name of file to be searched: ");
    scanf(" %c", &ch);
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (files[i].flag && files[i].name == ch) {
            printf("\nFile Name : %c\n", files[i].name);
            printf("Start Block : %d\n", files[i].start_block);
            printf("No. of Blocks : %d\n", files[i].no_of_blocks);
            printf("Blocks Occupied: ");
            int j = files[i].start_block, count = 0;
            while (j != -1 && count < files[i].no_of_blocks) {
                printf("%d ", j);
                j = sector[j].next;
                count++;
            }
            printf("\n");
            found = true;
            break;
        }
    }
    if (!found) printf("File not found\n");
    return 0;
}
