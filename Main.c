#include <stdio.h>
#include "StrList.h"



int main() {
    StrList *example = StrList_alloc();
    int choice = 1;
    while(choice != 0){
        scanf("%d", &choice);
        if(choice == 1){
            build_list(example);
        } else if(choice == 2){
            int index = 0;
            char *data = malloc(DATA);
            scanf("%d", &index);
            scanf("%s", data);
            StrList_insertAt(example, data, index);
        } else if(choice == 3){
            StrList_print(example);
        } else if(choice == 4){
            int size = StrList_size(example);
            printf("%d\n", size);
        } else if(choice == 5){
            int index = 0;
            scanf("%d", &index);
            StrList_printAt(example, index);
        } else if(choice == 6){
            int len = StrList_printLen(example);
            printf("%d\n", len);
        } else if(choice == 7){
            char *data = malloc(DATA);
            scanf("%s", data);
            int count = StrList_count(example, data);
            printf("%d\n", count);
        } else if(choice == 8){
            char *data = malloc(DATA);
            scanf("%s", data);
            StrList_remove(example, data);
        } else if(choice == 9){
            int index = 0;
            scanf("%d", &index);
            StrList_removeAt(example, index);
        } else if(choice == 10){
            StrList_reverse(example);
        } else if(choice == 11){
            delete_list(example);
        } else if(choice == 12){
            StrList_sort(example);
        } else if(choice == 13){
            if(StrList_isSorted(example)){
                printf("true\n");
            }else{
                printf("false\n");
            }
        }
    }
    return 0;
}
