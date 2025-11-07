#include <stdio.h>
#include <limits.h>
struct Process {
    int pid,at,bt,rt,ct,tat,wt;
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
        p[i].rt = p[i].bt;
    }
    printf("Arrival time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }
    int completed = 0, time = 0, prev = -1;
    float totalWT = 0, totalTAT = 0;
    printf("Gantt Chart : ");
    while (completed < n) {
        int idx = -1, minRT = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].rt < minRT) {
                    minRT = p[i].rt;
                    idx = i;
                } else if (p[i].rt == minRT && p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        if (prev != idx) {
            printf("P%d ", p[idx].pid);
            prev = idx;
        }
        p[idx].rt--;
        time++;
        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            completed++;
        }
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage waiting time: %.2f\n", totalWT / n);
    printf("Average turnaround time : %.2f\n", totalTAT / n);
    return 0;
}
