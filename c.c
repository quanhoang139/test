#include <stdio.h>

int main() {
    int i, j, n, time_quantum, time, remain, flag = 0;
    int sum_wait = 0, sum_turnaround = 0, arrival_time[100], burst_time[100], rt[100];
    printf("Enter the number of Processes: ");
    scanf("%d", & n);
    remain = n;
    for (i = 0; i < n; i++) {
        printf("Enter arrival_time and burst_time for Process P%d: ", i + 1);
        scanf("%d", & arrival_time[i]);
        scanf("%d", & burst_time[i]);
        rt[i] = burst_time[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", & time_quantum);
    printf("\nProcess\t|Turnaround time|Waiting time\n");
    printf("--------+---------------+------------\n");
    for (time = 0, i = 0; remain != 0;) {
        if (rt[i] <= time_quantum && rt[i] > 0) {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        } else if (rt[i] > 0) {
            rt[i] -= time_quantum;
            time += time_quantum;
        }
        if (rt[i] == 0 && flag == 1) {
            remain--;
            printf("P[%d]\t|\t%d\t|\t%d\n", i + 1, time - arrival_time[i], time - arrival_time[i] - burst_time[i]);
            sum_wait += time - arrival_time[i] - burst_time[i];
            sum_turnaround += time - arrival_time[i];
            flag = 0;
        }
        if (i == n - 1)
            i = 0;
        else if (arrival_time[i + 1] <= time)
            i++;
        else
            i = 0;
    }
    printf("\nAverage Waiting Time = %f\n", sum_wait * 1.0 / n);
    printf("Average Turnaround Time = %f", sum_turnaround * 1.0 / n);
    return 0;
}
