#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *f1 = fopen("a.txt", "w");
    fprintf(f1, "Helloooo\nJATIN\n");
    fclose(f1);
    FILE *f2 = fopen("b.txt", "w");
    fprintf(f2, "Byeee\nJATIN\n");
    fclose(f2);
    f1 = fopen("a.txt", "r");
    f2 = fopen("b.txt", "r");
    char line1[256], line2[256];
    while (fgets(line1, sizeof(line1), f1)) {
        rewind(f2);
        while (fgets(line2, sizeof(line2), f2)) {
            if (strcmp(line1, line2) == 0) {
                printf("%s", line1);
            }
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
