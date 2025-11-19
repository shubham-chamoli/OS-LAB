#include <stdio.h>
int main()
{
    int b, p;
    scanf("%d", &b);
    int blocks[b];
    for (int i = 0; i < b; i++)
        scanf("%d", &blocks[i]);
    scanf("%d", &p);
    int processes[p];
    for (int i = 0; i < p; i++)
        scanf("%d", &processes[i]);
    int allocated[b];
    for (int i = 0; i < b; i++)
        allocated[i] = 0;
    for (int i = 0; i < p; i++)
    {
        int assigned = -1;
        for (int j = 0; j < b; j++)
        {
            if (!allocated[j] && blocks[j] >= processes[i])
            {
                assigned = j;
                allocated[j] = 1;
                break;
            }
        }
        if (assigned != -1)
            printf("Process %d allocated to block %d\n", i + 1, assigned + 1);
        else
        {
            printf("Process %d: no free block available\n", i + 1);
        }
    }
    return 0;
}
