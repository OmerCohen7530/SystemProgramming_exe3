#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StrList.h"

void build_list(StrList* StrList){
    char temp[10000];
    int length_of_words;
    scanf("%d", &length_of_words);
    for (int i = 0; i < length_of_words; i++) {
        scanf("%s", temp);
        int size_word = strlen(temp);
        char *data = malloc(size_word);
        strcpy(data, temp);
        //printf("size of malloc %d ",size_word);
        //scanf("%s", data);
    //char *data = getDynamicString(stdin, 16, length_of_words);
        StrList_insertLast(StrList, data);
        // printf("done");
    }
    //free(temp);
}
// recieve a string of any size
char* getDynamicString(FILE* fp, size_t size,int length) {
    int i=0;
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n' && ch != ' ' && i<=length){
        str[len++]=ch;
        i++;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}


typedef struct _node{
    char* _data;
    struct _node * _next;
} Node;

struct _StrList {
    Node* _head;
    size_t _size;
};

Node* Node_alloc(char* data, Node* next) {
    Node* p= (Node*)malloc(sizeof(Node));
    p->_data= data;
    p->_next= next;
    return p;
}

void Node_free(Node* node) {
    free(node->_data);
    free(node);
}

StrList* StrList_alloc() {
    StrList* p= (StrList*)malloc(sizeof(StrList));
    p->_head= NULL;
    p->_size= 0;
    return p;
}

void delete_list(StrList* StrList){
    if (StrList==NULL) return;
    Node* p1= StrList->_head;
    Node* p2;
    while(p1) {
        p2= p1;
        p1= p1->_next;
        Node_free(p2);
    }
    StrList->_head =NULL;
    StrList->_size =0;
}
/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* StrList){
    if (StrList==NULL) return;
    Node* p1= StrList->_head;
    Node* p2;
    while(p1) {
        p2= p1;
        p1= p1->_next;
        Node_free(p2);
    }
    free(StrList);
}


size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}


void StrList_insertLast(StrList* StrList,const char* data){
    Node* newNode = Node_alloc((char*)data, NULL);
    
    if (StrList->_head == NULL) {
        StrList->_head = newNode;
    } else {
        
        Node* current = StrList->_head;
        while (current->_next != NULL) {
            current = current->_next;
        }
        
        current->_next = newNode;
    }

    StrList->_size++;
}


void StrList_insertFirst(StrList* StrList,const char* data) {
    Node* newNode = Node_alloc((char*)data, NULL);
    newNode->_next=StrList->_head;
    StrList->_head = newNode;
    StrList->_size++;
}

void StrList_insertAt(StrList* StrList,const char* data,int index){
    if(index > StrList->_size){
        return;
    }else if(index == StrList->_size){
        StrList_insertLast(StrList,data);
    }else if(index == 0 || StrList->_head == NULL){
        StrList_insertFirst(StrList,data);
    }else{
        Node* newNode = Node_alloc((char*)data, NULL);
        size_t count = 0;
        Node* current = StrList->_head;
        while (count < index -1){
            current = current->_next;
            count++;
        }
        newNode->_next = current->_next;
        current->_next = newNode;
        StrList->_size++;
    }
}


char* StrList_firstData(const StrList* StrList){
    return StrList->_head->_data;
}


void StrList_print(const StrList* StrList){
    if(StrList->_head ==NULL){
        printf("\n");
        return;
    }
    Node* current = StrList->_head;
    while (current->_next != NULL){
        printf("%s ",current->_data);
        current = current->_next;
    }
    printf("%s\n",current->_data);
}


void StrList_printAt(const StrList* Strlist,int index){
    if(Strlist->_head == NULL || index > Strlist->_size){
        return;
    }else if(index == 0){
        printf("%s\n",StrList_firstData(Strlist));
    }else{
        Node* current = Strlist->_head;
        size_t count = 0;
        while(count < index){
            current = current->_next;
            count++;
        }
        printf("%s\n",current->_data);
    }
}

int StrList_printLen(const StrList* Strlist){
    int count = 0;
    if(Strlist->_head == NULL){
        return count;
    }else{
        Node* current = Strlist->_head;
        count = count + strlen(current->_data);
        while (current->_next != NULL){
            current = current->_next;
            count = count + strlen(current->_data);
        }
    }
    return count;
}

//compare n'th first chars of two strings
int isEqualStringN(const char s1[], const char s2[], int n){
    for (int i=0; i<n; i++) {
        if (s1[i] != s2[i]) {
            return 0;
        }
    }
    return 1;
}

//return how many times s2 contains s1
int CountSubstring(const char *s1, char *s2) {
    int len1 = (int)strlen(s1), len2 = (int)strlen(s2);
    int count = 0;
    for (int i = 0; i <= len2-len1; i++) {
        if (isEqualStringN(s1, s2+i, len1)) {
            count++;
        }
    }
    return count;
}

int StrList_count(StrList* StrList, const char* data){
    int count=0;
    if(StrList->_head == NULL){
        free((char*)data);
        return count;
    }else{
        Node* current = StrList->_head;
        while (current->_next != NULL){
            count = count + CountSubstring(data, (current->_data));
            current = current->_next;
        }
        free((char*)data);
        return count;
    }
}


//Given strings s1 and s2, remove all the appearences of s1 in the s2
void remove_from_string(const char *s1, char*s2){
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int count = 0;


    char *first = strstr(s2, s1);
    while (first != NULL) {
        
        count = first - s2;

        memmove(first, first + s1_len, s2_len - count - s1_len + 1);

        first = strstr(first, s1);
        s2_len =s2_len - s1_len;
    }
}


/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data){
    if(StrList->_head == NULL){
        free((char*)data);
        return;
    }else{
        int count = 0;
        Node* current = StrList->_head;
        if(strcmp(data, current->_data) == 0){
            StrList_removeAt(StrList, count);
        }else{
            remove_from_string(data, current->_data);
        }
        while (current->_next != NULL){
            count++;
            current = current->_next;
            if(strcmp(data, current->_data) == 0){
                StrList_removeAt(StrList, count);
            }else{
                remove_from_string(data, current->_data);
            }
        }
        free((char*)data);
    }
}



void StrList_removeAt(StrList* StrList, int index){
    if(index > StrList->_size){
        return;
    }else if(StrList->_head == NULL){
        return;
    }else if(index == 0){
        Node* temp = StrList->_head;
        StrList->_head = StrList->_head->_next;
        StrList->_size--;
        Node_free(temp);
    }else{
        size_t count = 0;
        Node* current = StrList->_head;
        while (count < index -1){
            current = current->_next;
            count++;
        }
        Node* temp = current->_next;
        current->_next = current->_next->_next;
        StrList->_size--;
        Node_free(temp);
    }
}


int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    Node* current1 = StrList1->_head;
    Node* current2 = StrList2->_head;
    while (current1 != NULL && current2 != NULL){
        if (strcmp(current1->_data, current2->_data) !=0){
            return 0;
        }
        current1 = current1->_next;
        current2 = current2->_next;
        if((current1 != NULL && current2 == NULL) ||
                (current1 == NULL && current2 != NULL)){
            return 0;
        }

    }
    return 1;
}

/*
 * Clones the given StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* StrList){
    // Define a new StrList as result
    struct _StrList* result = StrList_alloc();

    Node* current = StrList->_head;
    while(current != NULL){
        char* clone_data = malloc(strlen(current->_data) + 1);
        if (clone_data == NULL) {
            return NULL;
        }
        
        strcpy(clone_data, current->_data);

        StrList_insertLast(result, clone_data);
        
        current = current->_next;
    }
    return result;
}


void StrList_reverse( StrList* StrList){
    if (StrList->_head == NULL || StrList->_head->_next == NULL) {
        return;
    }
    Node* current = StrList->_head;
    Node* previous = NULL;
    Node* next = NULL;


    while (current != NULL) {
        next = current->_next;
        current->_next = previous;
        previous = current;
        current = next;
    }

    StrList->_head = previous;
}


void StrList_sort( StrList* StrList){
    if (StrList->_size <= 1) {
        return;
    }
    Node* current = NULL;
    Node* next = NULL;
    size_t size = StrList->_size;
    for (size_t i = 0; i < size - 1; ++i) {
        current = StrList->_head;
        next = current->_next;
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (strcmp(current->_data, next->_data) > 0) {
                char* temp_data = current->_data;
                current->_data = next->_data;
                next->_data = temp_data;
            }
            current = next;
            next = next->_next;
        }
    }
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList){
    if (StrList->_size <= 1) {
        return 1;
    }
    Node* current = StrList->_head;
    Node* next = current->_next;
    while (next != NULL) {
        if (strcmp(current->_data, next->_data) > 0) {
            return 0;
        }
        current = next;
        next = next->_next;
    }
    return 1;
}

