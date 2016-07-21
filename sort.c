//Angel Morales
//3/6/2016
//CSC220
//Peter Brass

#include <stdio.h>
#include <stdlib.h>

struct listnode {
    struct listnode * next;
    long              key; } ;
//Takes a list and uses the merge sort algorithms
struct listnode *sort(struct listnode * alist) {
    //Checking for values inside the list

    if (alist== NULL || alist ->next==NULL)
    {
        return alist;
    }


    struct listnode *blist = alist;
    struct listnode *temp1 = alist->next->next;

// Findings the center of the list.
    while (temp1 && temp1->next)
    {
        blist = blist->next;
        temp1 = temp1->next->next;
    }

    struct listnode *center = blist->next;
    blist->next = NULL;
    // Recurse on the two smaller lists:
    struct listnode result[1];
    struct listnode *tale = result;

    struct listnode *alist2 = sort(alist);
    struct listnode *blist2 = sort(center);


    // Merge:
    while (alist2 != NULL && blist2 != NULL)
    {
        if (alist2->key < blist2->key)
        {
            tale->next = alist2;
            tale = alist2;
            alist2 = alist2->next;
        }
        else
        {
            tale->next = blist2;
            tale = blist2;
            blist2 = blist2->next;
        }
    }
    while (alist2 != NULL )
    {
        tale->next = alist2;
        tale = alist2;
        alist2 = alist2->next;
    }
    while (blist2 != NULL)
    {
        tale->next = blist2;
        tale = blist2;
        blist2 = blist2->next;
    }
    tale->next = NULL;
    return result->next;
}
