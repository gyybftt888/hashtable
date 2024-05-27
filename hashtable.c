/*********************************************************
(a)	這個 hash table size 要設定為多少？ 設成input size * 1.3左右
(b)	對於這個 hash function 有何想法？為什麼會選擇這個 hash function？ 參考網路教學，發現大部分都是以字元的ASCII來運算，我覺得常見的單字長度都在10以下，用字元相加的話，容易使的hash
    出的index value都在陣列的前面，相乘應該會有較好的均勻度，又乘出來的積高機率為偶數，容易使奇數index裡為空，所以加上一個有不確定性的單字長度，再作取餘數，得出最後的hash value
(c)	這個 hash table 預計會佔用多少 memory ？
    best case:(68000 * (32 + 4 + 8 + 8)) + 22000 * 8 Byte
    worst case:(68000 * (32 + 4 + 8)) + (90000 * 8) Byte
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAIL -1
#define WORD_SIZE 32
#define TABLE_SIZE 90000
typedef struct node {
    char vocabulary[WORD_SIZE];
    int integer;
    struct node *next;
} node;

node *table[TABLE_SIZE];
void build_hash(char *);
int query_hash(char *, int *);
unsigned int hash(char *);

int main() {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
    build_hash("dict.txt");
    int value;
    if (query_hash("yn", &value) == SUCCESS) {
        printf("%d", value);
    }
    return SUCCESS;
}

// TODO: build_hash : 將所指定的檔案建構出一個 hash table
void build_hash(char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (!fptr) {
        printf("Fail to read file\n");
        return;
    }
    char vocabulary[WORD_SIZE];
    int integer;
    while (fscanf(fptr, "%s %d", vocabulary, &integer) != EOF) {
        node *temp = table[hash(vocabulary) % TABLE_SIZE];
        while (temp != NULL && strcmp(temp->vocabulary, vocabulary) != 0)
            temp = temp->next;
        if (temp != NULL) {
            temp->integer = integer;
        } else {
            unsigned int index = hash(vocabulary) % TABLE_SIZE;
            node *newnode = (node *)malloc(sizeof(node));
            if (!newnode) {
                printf("Fail to malloc1\n");
                return;
            }
            strcpy(newnode->vocabulary, vocabulary);
            newnode->integer = integer;
            newnode->next = table[index];
            table[index] = newnode;
        }
    }
    fclose(fptr);
}

// TODO: query_hash : 查詢所指定英文字的資料，回傳其相對應數值
int query_hash(char *vocabulary, int *value) {
    node *temp = table[hash(vocabulary) % TABLE_SIZE];
    while (temp != NULL && strcmp(temp->vocabulary, vocabulary) != 0)
        temp = temp->next;
    if (temp == NULL) {
        // printf("Word not found\n");
        // exit(0);
        return FAIL;
    } else {
        *value = temp->integer;
        return SUCCESS;
    }
}

unsigned int hash(char *vocabulary) {
    int length = strlen(vocabulary);
    long long value = 1;
    // TODO: define hash function
    for (int i = 0; i < length; i++) {
        value *= vocabulary[i];
        value += length;
    }
    return value;
}