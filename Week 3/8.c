#include <stdio.h>
#include <limits.h>
struct Process {
    int pid,at,bt,ct,tat,wt,completed;
};
int main() {
    int n;
    printf("Number of processes : ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Burst time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
        p[i].pid = i+1;
        p[i].completed = 0;
    }
    printf("Arrival time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;
    printf("Gantt Chart : ");
    while (completed < n) {
        int idx = -1, minBT = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                } else if (p[i].bt == minBT && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        printf("P%d ", p[idx].pid);
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;
        p[idx].completed = 1;
        completed++;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time   : %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}
