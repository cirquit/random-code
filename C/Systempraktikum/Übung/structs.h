#ifndef structs_h
#define structs_h

#include <stdlib.h>
#include <stdio.h>

#define DLLSZ (sizeof(struct dll))


/*
 * Double linked lists
 *
 */
struct dll{
  int isFirst;
  int isLast;
  int index;
  char* content;
  struct dll* prev;
  struct dll* next;
};



struct dll* mapi(struct dll* a);

/*
 * returns the last node of the dll
 */
struct dll* last (struct dll* a);

/*
 * returns the first node of the dll
 */
struct dll* first(struct dll* a);

/*
 * concats 2 lists
 * goes to the end of the first list and the start of the second list
 * returns the first node of the list
 */
struct dll* concat (struct dll* a, struct dll* b);


// goto index node
struct dll* atIndex (struct dll* a, int pos);

/*
 * creates a single node with
 * isFirst = 1
 * isLast  = 1
 * indext = 0
 * content = msg
 * next = NULL
 * prev = NULL
 */
struct dll* createDll (char* msg);

/*
 * pretty prints current node
 * prints all enumerated nodes with the contents
 * returns the first node of the dll
 */
struct dll* showDll (struct dll* a);


// 1: list
// 2: to insert in list
// index where to insert
struct dll* insert (struct dll* a, struct dll* b, int pos);


// 1: list
// 2 & 3: delete at index from to (inclusive)
// delete (a, 2, 3) where a = [a, b, c, d] => [a, b]
struct dll* delete (struct dll* a, int posFrom, int posTo);

#endif
