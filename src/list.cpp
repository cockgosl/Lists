#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double type;

struct S_LIST {
    size_t head = 0;
    size_t tail = 0;
    type* data;
    size_t* next;
    size_t* prev;
    size_t free = 1;
    size_t size = 0;
    size_t amount = 0;
};

void LIST_INIT (S_LIST* LIST, size_t size);
void LIST_DESTROY (S_LIST* LIST);
void LIST_INSERT (S_LIST* LIST, size_t anchor, type value);
void LIST_DUMP (S_LIST* LIST);
void LIST_DELETE (S_LIST* LIST, size_t anchor);
void LISTG_DUMP (S_LIST* LIST);

int main() {
    return 0;
}

void LIST_INIT (S_LIST* LIST, size_t size) {
    if (LIST) {
        LIST->data = (type*)calloc (size + 1, sizeof (type));
        LIST->next = (size_t*)calloc (size + 1, sizeof (size_t));
        LIST->prev = (size_t*)calloc (size + 1, sizeof (size_t));

        assert (LIST->data);
        assert (LIST->next);
        assert (LIST->prev);

        LIST->size = size;

        for (int i = 1; i < LIST->size; i++) {
            LIST->next[i] = i + 1;
        }
        for (int j = 0; j < LIST->size; j++) {
            LIST->prev[j] = -1;
        }

        if ( LIST && !(LIST->data && LIST->prev && LIST->next)) {
            fprintf (stderr, "List cannot be initialized\n");
            abort();
        }
    }
    else {
        printf ("something is wrong with the given list");
    }
}

void LIST_DESTROY (S_LIST* LIST) {
    if (LIST) {
        if (LIST->data && LIST->prev && LIST->next) {
            free (LIST->data);
            free (LIST->next);
            free (LIST->prev); 
        }
        else {
            printf ("List wasn't initialized - error");
        }
    }
    else {
        printf ("Something is wrong with the given list\n");
    }
}

void LIST_INSERT (S_LIST* LIST, size_t anchor, type value) {

    size_t temp = 0;

    if (LIST) {

        if (LIST->amount == 0) {
            LIST->amount++;

            LIST->head = 1;
            LIST->tail = 1;
            
            temp = LIST->free;
            LIST->free = LIST->next[LIST->free];
            LIST->data[temp] = value;

            LIST->next[LIST->tail] = 0; 
        }
        else if (anchor > LIST->amount) {
            fprintf (stderr, "There is no such anchor\n");    
        }
        else if (anchor == LIST->tail) {
            LIST->amount++;

            temp = LIST->free;
            LIST->free = LIST->next[temp];
            LIST->next[LIST->tail] = temp;
            LIST->prev[temp] = LIST->tail;
            LIST->tail = temp;
            LIST->data[temp] = value;

            LIST->next[LIST->tail] = 0;
        }
        else if (anchor == 0) {
            LIST->amount++;

            temp = LIST->free;
            LIST->free = LIST->next[temp];
            LIST->data[temp] = value;
            LIST->next[temp] = LIST->head;
            LIST->prev[temp] = 0;
            LIST->prev[LIST->head] = temp;
            LIST->head = temp;

        }
        else {
            LIST->amount++;
            temp = LIST->free;
            LIST->free = LIST->next[temp];
            LIST->data[temp] = value;
            LIST->next[temp] = LIST->next[anchor];
            LIST->prev[LIST->next[anchor]] = temp;
            LIST->next[anchor] = temp;
            LIST->prev[temp] = anchor;
        }
    }
    else {
        fprintf (stderr, "Something is wrong with the given list");
    }
}

void LIST_DELETE (S_LIST* LIST, size_t anchor) {
    size_t temp = 0;
    if (LIST) {
        if (LIST->amount == 0) {
            fprintf (stderr, "There is nothing to delete\n");
        }
        else if (anchor > LIST->amount || anchor == 0) {
            fprintf (stderr, "There is no such anchor\n");    
        }
        else if (LIST->amount == 1) {
            temp = LIST->free;
            LIST->free = anchor;
            LIST->data[anchor] = 0;
            LIST->next[LIST->head] = temp;
            LIST->tail = 0;
            LIST->head = 0;
            LIST->amount--;
        }
        else if (anchor == LIST->tail) {
            LIST->amount--;
            temp = LIST->free;
            LIST->free = anchor;
            LIST->data[anchor] = 0;
            LIST->tail = LIST->prev[LIST->tail];
            LIST->next[LIST->prev[anchor]] = 0;
            LIST->next[anchor] = LIST->tail;
            LIST->prev[anchor] = -1;
        }
        else if (anchor == LIST->head) {
            LIST->amount--;
            temp = LIST->free;
            LIST->free = anchor;
            LIST->head = LIST->next[LIST->head];
            LIST->data[anchor] = 0;
            LIST->next[anchor] = temp;
            LIST->prev[LIST->head] = 0;
            LIST->prev[anchor] = -1;
        }
        else {
            LIST->amount--;
            temp = LIST->free;
            LIST->free = anchor;
            LIST->data[anchor] = 0;
            LIST->next[LIST->prev[anchor]] = LIST->next[anchor];
            LIST->prev[LIST->next[anchor]] = LIST->prev[anchor];
            LIST->prev[anchor] = -1;
            LIST->next[anchor] = temp;
        }
    }
    else {
        printf ("something is wrong with the given list\n");
    }
}

void LIST_DUMP (S_LIST* LIST) {
    size_t temp = 0;
    if (LIST) {
        printf ("head = %ld\n", LIST->head);
        printf ("tail = %ld\n", LIST->tail);
        printf ("free = %ld\n", LIST->free);
        printf ("size = %ld\n", LIST->size);
        printf ("amount = %ld\n", LIST->amount);

        printf ("\n");

        for (size_t i = LIST->head; i != 0; i = LIST->next[i]) {
            printf ("element%ld: %f\n", i, LIST->data[i]);
        }

        printf ("\n");
        printf ("from the tail\n\n");

        for (size_t i = LIST->tail; i != 0; i = LIST->prev[i]) {
            printf ("element%ld: %f\n", i, LIST->data[i]);
        }
        printf ("\n");
        for (size_t i = 1; i <= LIST->size ; i++) {
            printf ("next[%ld]: %ld\n", i, LIST->next[i]);
        }
        for (size_t i = 1; i <= LIST->size ; i++) {
            printf ("prev[%ld]: %ld\n", i, LIST->prev[i]);
        }
    }
    else {
        printf ("Something is wrong with the given LIST\n");
    }
}

void LISTG_DUMP (S_LIST* LIST) {
    ;
}


