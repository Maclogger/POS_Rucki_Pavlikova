#include "char_buffer.h"
#include <stdlib.h>
#include <string.h>

void char_buffer_init(struct char_buffer* buf) {
    buf->capacity = 10;
    buf->size = 0;
    buf->data = calloc(buf->capacity, sizeof(char));
}

void char_buffer_init_copy(struct char_buffer* buf, const struct char_buffer* other) {
    buf->capacity = other->capacity;
    buf->size = other->size;
    buf->data = calloc(buf->capacity, sizeof(char));
    char_buffer_copy(buf, other);
}

void char_buffer_destroy(struct char_buffer* buf) {
    free(buf->data);
    buf->data = NULL;
    buf->size = 0;
    buf->capacity = 0;
}

void char_buffer_append(struct char_buffer* buf, const char* data, size_t data_size) {
    if (buf->capacity - buf->size <= data_size) {
        size_t new_capacity = buf->size + data_size + 1; // +1 pre nulový ukončovací znak
        char* new_data = realloc(buf->data, new_capacity);
        if (new_data == NULL) {
            // Spracovanie chyby pri alokácii pamäte
            return;
        }
        buf->data = new_data;
        buf->capacity = new_capacity;
    }
    memcpy(buf->data + buf->size, data, data_size);
    buf->size += data_size;
    buf->data[buf->size] = '\0';
}

void char_buffer_clear(struct char_buffer* buf) {
    buf->size = 0;
    buf->data[buf->size] = '\0';
}

void char_buffer_copy(struct char_buffer* dest, const struct char_buffer* src) {
    if (dest->capacity <= src->size) {
        dest->capacity = src->capacity;
        dest->data = realloc(dest->data, dest->capacity);
    }
    memcpy(dest->data, src->data, src->size);
    dest->size = src->size;
    dest->data[dest->size] = '\0';
}