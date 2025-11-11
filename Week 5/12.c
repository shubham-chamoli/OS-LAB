#include <stdio.h>
struct Process {
    int A, B, C; 
};
int main() {
    int n, A, B, C;
    printf("Enter the Number of Processes: ");
    scanf("%d", &n);
    struct Process allocated[n], require[n], need[n];
    int isExecute[n]; int ans[n];
    for (int i = 0; i < n; i++)
        isExecute[i] = 0;
    int al_a = 0, al_b = 0, al_c = 0;
    for (int i = 0; i < n; i++) {
        printf("Enter Allocated (A B C) Resources of P%d: ", i);
        scanf("%d%d%d", &allocated[i].A, &allocated[i].B, &allocated[i].C);
        printf("Enter Maximum Required (A B C) Resources of P%d: ", i);
        scanf("%d%d%d", &require[i].A, &require[i].B, &require[i].C);
        al_a += allocated[i].A;
        al_b += allocated[i].B;
        al_c += allocated[i].C;
        need[i].A = require[i].A - allocated[i].A;
        need[i].B = require[i].B - allocated[i].B;
        need[i].C = require[i].C - allocated[i].C;
    }
    printf("Enter the Total Resources (A B C): ");
    scanf("%d%d%d", &A, &B, &C);
    A -= al_a;
    B -= al_b;
    C -= al_c;
    int idx = 0;
    for (int count = 0; count < n; count++) {
        for (int j = 0; j < n; j++) {
            if (isExecute[j] == 0 &&
                need[j].A <= A && need[j].B <= B && need[j].C <= C) {
                A += allocated[j].A;
                B += allocated[j].B;
                C += allocated[j].C;
                ans[idx++] = j;
                isExecute[j] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (isExecute[i] == 0) {
            printf("No Safe Sequence is Possible\n");
            return 0;
        }
    }
    printf("Request can be fulfilled\nThe Safe Sequence is: ");
    for (int i = 0; i < n - 1; i++)     printf("P%d -> ", ans[i]);
    printf("P%d\n", ans[n - 1]);
    return 0;
}
