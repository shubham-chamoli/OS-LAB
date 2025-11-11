#include <stdio.h>
#include <limits.h>
struct Process {
    int id, at, bt, pr;
    int ct, tat, wt, rt, remaining;
    int start;
};
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("Enter Burst Time, Arrival Time, Priority for P%d: ", i);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].pr);
        p[i].remaining = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = p[i].rt = -1;
        p[i].start = -1;
    }
    int completed = 0, time = 0, prev = -1, total_idle = 0;
    float avg_wt = 0, avg_tat = 0;
    printf("\nGantt Chart: ");
    while (completed < n) {
        int idx = -1, minPr = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].pr < minPr) {
                    minPr = p[i].pr;
                    idx = i;
                } else if (p[i].pr == minPr) {
                    if (p[i].at < p[idx].at || 
                       (p[i].at == p[idx].at && p[i].id < p[idx].id)) {
                        idx = i;
                    }
                }
            }
        }
        if (idx == -1) {
            time++;
            total_idle++;
        } else {
            if (prev != idx) {
                printf(" P%d ", p[idx].id);
                prev = idx;
            }
            if (p[idx].start == -1) {
                p[idx].start = time;
                p[idx].rt = p[idx].start - p[idx].at;
            }
            p[idx].remaining--;
            time++;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
    }
    printf("\n\nProcess Table:\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    avg_wt /= n;
    avg_tat /= n;

    float cpu_util = ((time - total_idle) * 100.0) / time;
    float throughput = (float)n / time;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nCPU Utilization = %.2f%%", cpu_util);
    printf("\nThroughput = %.2f processes/unit time\n", throughput);

    return 0;
}

