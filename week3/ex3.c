#include <stdio.h>
#include <stdlib.h>

struct LinkedListNode {
    int value;
    struct LinkedListNode *next;
};

struct LinkedList {
    size_t size;
    struct LinkedListNode *head;
};

void init_LinkedList(struct LinkedList *const ll);
void print_list(const struct LinkedList *const ll);
void insert_node(struct LinkedList *const ll, size_t index, int value);
void delete_node(struct LinkedList *const ll, size_t index);
void free_LinkedList();

int main(void){
    struct LinkedList ll;
    init_LinkedList(&ll);
    insert_node(&ll, 0, 3);
    insert_node(&ll, 0, 1);
    insert_node(&ll, 10, 10);
    insert_node(&ll, 1, 124);
    print_list(&ll);
    delete_node(&ll, 0);
    delete_node(&ll, 1);
    delete_node(&ll, 0);
    print_list(&ll);
    free_LinkedList(&ll);
    return 0;
}

void init_LinkedList(struct LinkedList *const ll) {
    ll->size = 0;
    ll->head = NULL;
}

void print_list(const struct LinkedList *const ll) {
    if (ll->head == NULL) {
        printf("Given linked list is empty\n");
    } else {
        const struct LinkedListNode *current = ll->head;
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}

void insert_node(struct LinkedList *const ll, size_t index, int value) {
    if (ll->head == NULL && index == 0) {
        ll->head = malloc(sizeof(struct LinkedListNode));
        ll->head->value = value;
        ll->head->next = NULL;
        ++ll->size;
    } else if (index < ll->size) {
        struct LinkedListNode *cur;
        cur = ll->head;
        size_t cur_index = 0;
        while (cur_index < index) {
            cur = cur->next;
            ++cur_index;
        }
        struct LinkedListNode *new = malloc(sizeof(struct LinkedListNode));
        new->next = cur->next;
        new->value = value;
        cur->next = new;
        ++ll->size;
    } else {
        fprintf(stderr, "ERROR: Index is out of range\n");
    }
}

void delete_node(struct LinkedList *const ll, size_t index) {
    if (index >= ll->size || ll->head == NULL) {
        return;
    }
    struct LinkedListNode *prev, *cur;
    prev = NULL;
    cur = ll->head;
    size_t cur_index = 0;
    while (cur_index < index) {
        prev = cur;
        cur = cur->next;
        ++cur_index;
    }
    if (prev != NULL) {
        prev->next = cur->next;
    }
    if (index == 0) {
        ll->head = cur->next;
    }
    free(cur);
}

void free_LinkedList_recursively(struct LinkedListNode *lln) {
    if (lln == NULL) {
        return;
    }
    if (lln->next != NULL) {
        free_LinkedList_recursively(lln->next);
    }
    free(lln);
}

void free_LinkedList(struct LinkedList *ll) { free_LinkedList_recursively(ll->head); }
