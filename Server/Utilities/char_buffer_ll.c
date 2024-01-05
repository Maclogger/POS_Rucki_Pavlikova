#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} NODE;

typedef struct buffer_char_ll {
    NODE* start;
    NODE* end;
    int capacity;
    int size;
} CHAR_BUFFER_LL;

void buffer_ll_init(CHAR_BUFFER_LL* buffer, int capacity) {
    buffer->start = NULL;
    buffer->end = NULL;
    buffer->capacity = capacity;
    buffer->size = 0;
}

void buffer_ll_destroy(CHAR_BUFFER_LL* buffer) {
    while (buffer->start != NULL) {
        NODE* temp = buffer->start;
        buffer->start = buffer->start->next;
        free(temp);
    }
    buffer->start = NULL;
    buffer->end = NULL;
    buffer->capacity = 0;
    buffer->size = 0;
}

_Bool buffer_ll_try_add(CHAR_BUFFER_LL* buffer, char item) {
    if (buffer->size == buffer->capacity) {
        return 0;
    }
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if (newNode == NULL) {
        return 0;
    }
    newNode->data = item;
    newNode->next = NULL;
    if (buffer->end == NULL) {
        buffer->start = newNode;
        buffer->end = newNode;
    } else {
        buffer->end->next = newNode;
        buffer->end = newNode;
    }
    buffer->size++;
    return 1; // Success
}

_Bool buffer_ll_try_remove_first(CHAR_BUFFER_LL* buffer, char* item) {
    if (buffer->start == NULL || buffer->size == 0) {
        return 0; // Buffer is empty
    }
    NODE* firstNode = buffer->start;
    *item = firstNode->data;
    buffer->start = firstNode->next;
    if (buffer->start == NULL) {
        buffer->end = NULL;
    }
    free(firstNode);
    buffer->size--;
    return 1; // Return the removed item
}

/*
int main() {
    Buffer buffer;
    buffer_ll_init(&buffer);

    // Try to add and remove items
    if (buffer_add(&buffer, 'a') == 0) {
        printf("Item added successfully.\n");
    }
    char item;
    if (buffer_remove_first(&buffer, &item) == 0) {
        printf("Item removed: %c\n", item);
    }

    return 0;
}*/


/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


