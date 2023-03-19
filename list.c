#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}
//1.
List * createList() {
  List * lista = NULL;
  lista = (List *) malloc(sizeof(List));
  return lista;
}
//2.
void * firstList(List * list) {
    if (list->current == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    if (list->current == NULL) return NULL;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    if (list->current == NULL) return NULL;
    return list->current->data;
}
//3.
void * lastList(List * list) {
    if(list->current == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    while(list->current->next != NULL) list->current = list->current->next;
    if(list-> current == NULL) return NULL;
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    if(list->current == NULL) return NULL;
    return list->current->data;
}
//4.
void pushFront(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
    if(list->head == NULL){
      list->head = nuevoNodo;
      list->tail = nuevoNodo;
    }
    else{
      nuevoNodo->next = list->head;
      list->head->prev = nuevoNodo;
      list->head = nuevoNodo;
    }
    return;
}
//5.
void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nuevoNodo = createNode(data);

    if(list->current == NULL){
      list->head = nuevoNodo;
      list->tail = nuevoNodo;
    }
    else{
      if(list->current == list->tail){
        list->tail = nuevoNodo;
      }
      else{
        nuevoNodo->next = list->current->next;
        list->current->next->prev = nuevoNodo;
      }
      nuevoNodo->prev = list->current;
      list->current->next = nuevoNodo;
    }

}
//6.
void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void * guardarDato;
    if(list->current == NULL) return NULL;
    guardarDato = list->current->data;
    if(list->current == list->tail){
      list->tail = list->current->prev;
      list->tail->next = NULL;
      list->current = NULL;
    }
    else{
      if(list->current == list->head){
      list->head = list->current->next;
      list->head->prev = NULL;
      list->current = NULL;
      }
      else{
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        list->current = NULL;
      }
    }
      
    return guardarDato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}