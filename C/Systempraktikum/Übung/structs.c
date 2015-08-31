// #include "structs.h"


// struct dll* mapi (struct dll* a){

//   while (a -> pred != NULL){
//     a = a -> pred;
//   }

//   a -> isFirst = 1;
//   a -> isLast  = 0;

//   int i = 0;
//   while (a -> next != NULL){
//     a -> index = i;
//     a = a -> next;
//     i++;
//   }
//   a -> index = i++;
//   a -> isLast = 1;

//   return first(a);
// }

// struct dll* last (struct dll* a){

//   while (a -> isLast != 1){
//     a = (a -> next);
//   }

//   return a;
//  }

// struct dll* first(struct dll* a){

//   while (a -> isFirst != 1){
//     a = (a -> prev);
//   }

//   return a;
// }

// struct dll* concat (struct dll* a, struct dll* b){

//     a = last  (a);
//     b = first (b);

//     a -> isLast = 0;
//     a -> next = b;
//     b -> isFirst = 0;
//     b -> prev = a;

//     a = first(a);
//     int i = 0;
//     while (a -> isLast != 1){
//       a -> index = i;
//       a = a -> next;
//       i++;
//     }
//     a -> index = i++;

//     return (first (a));
// }

// struct dll* atIndex (struct dll* a, int pos){

//   a = first(a);

//   while ((a -> isLast != 1) && (a -> index < pos)){
//     a = a -> next;
//   }
//   if (a -> index < pos){ return NULL; }

//   return a;
// }


// struct dll* createDll (char* msg){

//   struct dll* list = NULL;
//   list = malloc (DLLSZ);

//   list -> isFirst = 1;
//   list -> isLast  = 1;
//   list -> index   = 0;
//   list -> content = msg;
//   list -> prev    = NULL;
//   list -> next    = NULL;

//   return list;
// }

// struct dll* showDll (struct dll* a){

//   printf("Nr           | isFirst | isLast | content\n");
//   printf("Current node | %i       | %i      | %s\n\n", a -> isFirst, a -> isLast, a -> content);

//   a = first(a);

//   while ((a -> isLast) != 1){
//     printf("%i            | %i       | %i      | %s\n", a -> index, a -> isFirst, a -> isLast, a -> content);
//     a = a -> next;
//   }
//   printf("%i            | %i       | %i      | %s\n", a -> index , a -> isFirst, a -> isLast, a -> content);

//   return first(a);
// }


// struct dll* insert (struct dll* a, struct dll* b, int pos){}

// struct dll* delete (struct dll* a, int posFrom, int posTo){

//   struct dll* to = NULL;

//   a = first(a);
//   a = atIndex(a, posFrom-1);
//   to = atIndex(a, posTo+1);

//   a -> next = to;

// }


// int main (int argc, char** argv){
// 
    // struct dll* l1 = createDll ("Hello World!");
    // struct dll* l2 = createDll ("Hello Mars!");
    // struct dll* l3 = createDll ("msg3");
    // struct dll* l4 = createDll ("msg4");
// 
    // l1 = concat (l1, l2);
    // l1 = concat (l1, l4);
    // l1 = concat (l1, l3);
// 
    // l1 = atIndex(l1, 2);
    // showDll(l1);
   //showDll(delete(l1, 0, 3));
// 
  // return 0;
// }

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct test_struct
{
    int val;
    struct test_struct *next;
};

struct test_struct *head = NULL;
struct test_struct *curr = NULL;

struct test_struct* create_list(int val)
{
    printf("\n creating list with headnode as [%d]\n",val);
    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

struct test_struct* add_to_list(int val, bool add_to_end)
{
    if(NULL == head)
    {
        return (create_list(val));
    }

    if(add_to_end)
        printf("\n Adding node to end of list with value [%d]\n",val);
    else
        printf("\n Adding node to beginning of list with value [%d]\n",val);

    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->val = val;
    ptr->next = NULL;

    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

struct test_struct* search_in_list(int val, struct test_struct **prev)
{
    struct test_struct *ptr = head;
    struct test_struct *tmp = NULL;
    bool found = false;

    printf("\n Searching the list for value [%d] \n",val);

    while(ptr != NULL)
    {
        if(ptr->val == val)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

int delete_from_list(int val)
{
    struct test_struct *prev = NULL;
    struct test_struct *del = NULL;

    printf("\n Deleting value [%d] from list\n",val);

    del = search_in_list(val,&prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }

    free(del);
    del = NULL;

    return 0;
}

void print_list(void)
{
    struct test_struct *ptr = head;

    printf("\n -------Printing list Start------- \n");
    while(ptr != NULL)
    {
        printf("\n [%d] \n",ptr->val);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}

int main(void)
{
    int i = 0, ret = 0;
    struct test_struct *ptr = NULL;

    print_list();

    for(i = 5; i<10; i++)
        add_to_list(i,true);

    print_list();

    for(i = 4; i>0; i--)
        add_to_list(i,false);

    print_list();

    for(i = 1; i<10; i += 4)
    {
        ptr = search_in_list(i, NULL);
        if(NULL == ptr)
        {
            printf("\n Search [val = %d] failed, no such element found\n",i);
        }
        else
        {
            printf("\n Search passed [val = %d]\n",ptr->val);
        }

        print_list();

        ret = delete_from_list(i);
        if(ret != 0)
        {
            printf("\n delete [val = %d] failed, no such element found\n",i);
        }
        else
        {
            printf("\n delete [val = %d]  passed \n",i);
        }

        print_list();
    }

    return 0;
}