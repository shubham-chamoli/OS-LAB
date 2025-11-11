#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

struct Process {
    int pid, at, bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
};
int max(int a, int b) {
    return a > b ? a : b;
}
int compareAT(const void *a, const void *b) {
    return ((struct Process *)a)->at - ((struct Process *)b)->at;
}
int main() {
    int n, tq;
    int current_time = 0, completed = 0;
    int total_idle_time = 0, max_completion_time;
    int queue[100], front = 0, rear = 0;
    bool in_queue[100] = {false};
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    struct Process ps[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process P%d: ", i);
        scanf("%d%d", &ps[i].at, &ps[i].bt);
        ps[i].pid = i;
        ps[i].bt_remaining = ps[i].bt;
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    qsort(ps, n, sizeof(struct Process), compareAT);
    queue[rear++] = 0;
    in_queue[0] = true;

    printf("\nGantt Chart:\n");
    while (completed < n) {
        int idx = queue[front++];
        if (ps[idx].bt_remaining == ps[idx].bt) {
            ps[idx].start_time = max(current_time, ps[idx].at);
            if (current_time < ps[idx].start_time)
                total_idle_time += ps[idx].start_time - current_time;
            current_time = ps[idx].start_time;
        }
        if (ps[idx].bt_remaining > tq) {
            ps[idx].bt_remaining -= tq;
            current_time += tq;
            printf("P%d ", ps[idx].pid);
        } else {
            current_time += ps[idx].bt_remaining;
            ps[idx].bt_remaining = 0;
            completed++;
            ps[idx].ct = current_time;
            ps[idx].tat = ps[idx].ct - ps[idx].at;
            ps[idx].wt = ps[idx].tat - ps[idx].bt;
            ps[idx].rt = ps[idx].start_time - ps[idx].at;
            sum_tat += ps[idx].tat;
            sum_wt += ps[idx].wt;
            sum_rt += ps[idx].rt;
            printf("P%d ", ps[idx].pid);
        }
        for (int i = 0; i < n; i++) {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && !in_queue[i]) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }
        if (ps[idx].bt_remaining > 0) {
            queue[rear++] = idx;
        }
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (ps[i].bt_remaining > 0) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                    break;
                }
            }
        }
    }
    max_completion_time = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (ps[i].ct > max_completion_time)
            max_completion_time = ps[i].ct;
    }
    int length_cycle = max_completion_time - ps[0].at;
    float cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;
    printf("\n\nProcess Table:\n");
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               ps[i].pid, ps[i].at, ps[i].bt, ps[i].start_time,
               ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
    printf("\nAverage Turnaround Time = %.2f", sum_tat / n);
    printf("\nAverage Waiting Time    = %.2f", sum_wt / n);
    printf("\nAverage Response Time   = %.2f", sum_rt / n);
    printf("\nThroughput              = %.2f", n / (float)length_cycle);
    printf("\nCPU Utilization         = %.2f%%\n", cpu_utilization * 100);

    return 0;
}
