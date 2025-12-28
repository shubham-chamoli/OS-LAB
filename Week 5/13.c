#include <stdio.h>
int main(){
    int n, m, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m];
    int resource[m], available[m];
    int finish[n];

    printf("Enter maximum requirement matrix (%d x %d):\n", n, m);
    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter allocation matrix (%d x %d):\n", n, m);
    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter resource vector (%d):\n", m);
    for(j=0;j<m;j++) {
        scanf("%d", &resource[j]);
    }
    for(j=0;j<m;j++) {
        int sum = 0;
        for(i=0;i<n;i++)
            sum += allocation[i][j];
        available[j] = resource[j] - sum;
    }
    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    for(i=0;i<n;i++)
        finish[i] = 0;

    int changed;
    do {
        changed = 0;
        for(i=0;i<n;i++) {
            if(finish[i] == 0) { 
                int can_finish = 1;
                for(j=0;j<m;j++) {
                    if(need[i][j] > available[j]) {
                        can_finish = 0;
                        break;
                    }
                }
                if(can_finish) {
                    for(j=0;j<m;j++)
                        available[j] += allocation[i][j];
                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    } while(changed);

    int deadlock_count = 0;
    printf("\nProcesses in deadlock: ");
    for(i=0;i<n;i++) {
        if(finish[i] == 0) {
            printf("P%d ", i);
            deadlock_count++;
        }
    }
    if(deadlock_count == 0)
        printf("None (No Deadlock)\n");
    else
        printf("\nDeadlock detected!\n");

    return 0;
}
