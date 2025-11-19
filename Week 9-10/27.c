#include <stdio.h>
#include <stdbool.h>
#define TOTAL_BLOCKS 1000
#define MAX_BLOCKS_PER_FILE 100
typedef struct{
    char name;
    int start_block;
    int blocks[MAX_BLOCKS_PER_FILE];
    int no_of_blocks;
}FileEntry;
int main(void){
    bool blocks[TOTAL_BLOCKS];
    for(int i=0;i<TOTAL_BLOCKS;i++)blocks[i]=true;
    int n;
    printf("Enter number of files: ");
    if(scanf("%d",&n)!=1||n<=0)return 1;
    FileEntry files[n];
    for(int i=0;i<n;i++){
        printf("Enter file %d name: ",i+1);
        if(scanf(" %c",&files[i].name)!=1)return 1;
        printf("Enter starting block of file %d: ",i+1);
        if(scanf("%d",&files[i].start_block)!=1)return 1;
        if(files[i].start_block<0||files[i].start_block>=TOTAL_BLOCKS)return 1;
        printf("Enter no of blocks in file %d: ",i+1);
        if(scanf("%d",&files[i].no_of_blocks)!=1)return 1;
        if(files[i].no_of_blocks<=0||files[i].no_of_blocks>MAX_BLOCKS_PER_FILE)return 1;
        printf("Enter blocks for file %d: ",i+1);
        for(int j=0;j<files[i].no_of_blocks;j++){
            int b;
            while(1){
                if(scanf("%d",&b)!=1)return 1;
                if(b<0||b>=TOTAL_BLOCKS){printf("Block out of range, enter another: ");continue;}
                if(!blocks[b]){printf("Block %d occupied, enter another: ",b);continue;}
                files[i].blocks[j]=b;
                blocks[b]=false;
                break;
            }
        }
        if(files[i].start_block!=files[i].blocks[0])files[i].start_block=files[i].blocks[0];
    }
    char ch;
    printf("Enter the file name to be searched: ");
    if(scanf(" %c",&ch)!=1)return 1;
    bool found=false;
    for(int i=0;i<n;i++){
        if(files[i].name==ch){
            printf("File Name: %c\n",files[i].name);
            printf("Start Block: %d\n",files[i].start_block);
            printf("No. of Blocks: %d\n",files[i].no_of_blocks);
            printf("Blocks Occupied: ");
            for(int j=0;j<files[i].no_of_blocks;j++){
                printf("%d",files[i].blocks[j]);
                if(j<files[i].no_of_blocks-1)printf(" ");
            }
            printf("\n");
            found=true;
            break;
        }
    }
    if(!found)printf("\nFile not found\n");
    return 0;
}
