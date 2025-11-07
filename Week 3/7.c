#include <stdio.h>
struct Process {
    int pid,at,bt,ct,tat,wt;
};
int main() {
    int n;
    printf("Number of processes : ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Burst time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
        p[i].pid = i;
    }
    printf("Arrival time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }
    int time = 0;
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    } 

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time   : %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
