#include <stdio.h>
#include <stdlib.h>
#define LOW 0
#define HIGH 199
#define MAXQ 100
int absval(int x){ return x < 0 ? -x : x; }
int main() {
    int queue[MAXQ], q_size, head;
    printf("Input no of disk locations: ");
    if(scanf("%d", &q_size) != 1 || q_size <= 0 || q_size >= MAXQ-5){
        printf("Invalid queue size\n");
        return 1;
    }
    printf("Enter head position: ");
    if(scanf("%d", &head) != 1 || head < LOW || head > HIGH){
        printf("Invalid head position\n");
        return 1;
    }
    printf("Input elements into disk queue:\n");
    for(int i = 0; i < q_size; i++){
        if(scanf("%d", &queue[i]) != 1){
            printf("Invalid input\n");
            return 1;
        }
        if(queue[i] < LOW || queue[i] > HIGH){
            printf("Queue element out of range [%d..%d]\n", LOW, HIGH);
            return 1;
        }
    }
    queue[q_size] = head;
    q_size++;
    for(int i = 0; i < q_size - 1; i++){
        for(int j = i + 1; j < q_size; j++){
            if(queue[i] > queue[j]){
                int t = queue[i]; queue[i] = queue[j]; queue[j] = t;
            }
        }
    }
    int dloc = -1;
    for(int i = 0; i < q_size; i++){
        if(queue[i] == head){ dloc = i; break; }
    }
    if(dloc == -1){
        printf("Head not found\n");
        return 1;
    }
    int move_right = (absval(head - HIGH) <= absval(head - LOW));
    int order[MAXQ + 10], o = 0;
    order[o++] = head;
    if(move_right){
        for(int i = dloc + 1; i < q_size; i++) order[o++] = queue[i];
        if(order[o-1] != HIGH) order[o++] = HIGH;
        order[o++] = LOW;
        for(int i = 0; i < dloc; i++) order[o++] = queue[i];
    } else {
        for(int i = dloc - 1; i >= 0; i--) order[o++] = queue[i];
        if(order[o-1] != LOW) order[o++] = LOW;
        order[o++] = HIGH;
        for(int i = q_size - 1; i > dloc; i--) order[o++] = queue[i];
    }
    printf("\nC-SCAN service order:\n");
    for(int i = 0; i < o; i++){
        if(i == o - 1) printf("%d\n", order[i]);
        else printf("%d --> ", order[i]);
    }
    long total_movement = 0;
    for(int i = 1; i < o; i++) total_movement += absval(order[i] - order[i-1]);
    printf("Total head movement (including jump): %ld\n", total_movement);
    return 0;
}
