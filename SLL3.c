//--------------------------------------------------------------
// Dr. Art Hanna
// Singly-linked list (SLL) abstract data type
// SLL.c
//--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SLL3.h"
#include "ADTExceptions.h"
//--------------------------------------------------------------
void DeleteSLL(SLL *sll,const int offset)
//--------------------------------------------------------------
{
   SLLNODE *p;

   if ( GetSizeSLL(sll) == 0 ) RaiseADTException(SLL_UNDERFLOW);

   if ( !((0 <= offset) && (offset <= GetSizeSLL(sll)-1)) ) RaiseADTException(SLL_OFFSET_ERROR);

   if ( GetSizeSLL(sll) == 1 )                   // *sll contains only 1 node
   {
      p = sll->head;
      sll->head = NULL;
      sll->tail = NULL;
   }
   else                                          // *sll contains 2 or more nodes
   {
      if ( offset == 0 )                         // delete head node
      {
         p = sll->head;
         sll->head = p->FLink;
      }
      else
      {
         SLLNODE *L = NULL;                      // set L to point-to node to (L)eft of deleted node
         int i;

         p = sll->head;                          // set p to point-to node to be deleted
         for (i = 1; i <= offset; i++)
         {
            L = p;
            p = p->FLink;
         }
         if ( p == sll->tail )                   // delete tail node
         {
            sll->tail = L;
            L->FLink = NULL;
         }
         else                                    // delete "middle node"
         {
            L->FLink = p->FLink;
         }
      }
   }
   if ( sll->DestructElement != NULL ) sll->DestructElement(p->element);
   free(p);
   sll->size--;
}
void PopTailSLL(SLL *sll)
{
    SLLNODE *p = sll->head, *last = sll->tail;
    if ( GetSizeSLL(sll) == 0 ) RaiseADTException(SLL_UNDERFLOW);
    if ( GetSizeSLL(sll) == 1 )
    {
        sll->head = NULL;
        sll->tail = NULL;
    }
    else
    {
        while(p->FLink != last) //goto last but one node
            p = p->FLink;
    }
    if ( sll->DestructElement != NULL ) sll->DestructElement(last->element);
    free(last);
    p->FLink = NULL;
    sll->tail = p;
    sll->size--;
}
bool IsInSLL(const SLL *sll,const char *element)
{
    SLLNODE *p = sll->head;
    while(p != NULL)
    {
        if(strcmp(p->element, element) == 0)
            return true;
        p = p->FLink;
    }
    return false;
}
void TraverseSLL(const SLL *sll,void (*ProcessElement)(char *element))
{
    SLLNODE *p = sll->head;
    while(p != NULL)
    {
        ProcessElement(p->element);
        p = p->FLink;
    }
}
//--------------------------------------------------------------
void InsertSLL(SLL *sll,const int offset,const char *element)
//--------------------------------------------------------------
{
   SLLNODE *n = (SLLNODE *) malloc(sizeof(SLLNODE));

   if ( n == NULL ) RaiseADTException(MALLOC_ERROR);

   n->element = (char *) element;

   if ( !((0 <= offset) && (offset <= GetSizeSLL(sll))) ) RaiseADTException(SLL_OFFSET_ERROR);

// Insert new node *BEFORE* offset node except insert *AFTER* tail node when offset = size-of-list
   if ( IsEmptySLL(sll) )                        // *sll is empty
   {
      sll->head = n;
      sll->tail = n;
      n->FLink = NULL;
   }
   else                                          // *sll contains at least 1 node
   {
      if ( offset == 0 )                         // insert new head node
      {
         n->FLink = sll->head;
         sll->head = n;
      }
      else if ( offset == GetSizeSLL(sll) )      // insert new tail node                    
      {
         sll->tail->FLink = n;
         sll->tail = n;
         n->FLink = NULL;
      }
      else                                       // insert "middle node"
      {
         SLLNODE *L = sll->head;                 // set L to point-to node to (L)eft of inserted node
         int i;

         for (i = 1; i <= offset-1; i++)
         {
            L = L->FLink;
         }
         n->FLink = L->FLink;
         L->FLink = n;
      }
   }
   sll->size++;
}

//--------------------------------------------------------------
void ConstructSLL(SLL *sll,
                  void (*DestructElement)(const char *element))
//--------------------------------------------------------------
{
   sll->size = 0;
   sll->head = NULL;
   sll->tail = NULL;
   sll->DestructElement = DestructElement;
}

//--------------------------------------------------------------
void DestructSLL(SLL *sll)
//--------------------------------------------------------------
{
   while ( !IsEmptySLL(sll) )
   {
      PopHeadSLL(sll);
   }
}

//--------------------------------------------------------------
void PushHeadSLL(SLL *sll,const char *element)
//--------------------------------------------------------------
{
   SLLNODE *p = (SLLNODE *) malloc(sizeof(SLLNODE));

   if ( p == NULL ) RaiseADTException(MALLOC_ERROR);

   p->element = (char *) element;
   if ( IsEmptySLL(sll) )
   {
      p->FLink = NULL;
      sll->head = p;
      sll->tail = p;
   }
   else
   {
      p->FLink = sll->head;
      sll->head = p;
   }
   sll->size++;
}

//--------------------------------------------------------------
void PopHeadSLL(SLL *sll)
//--------------------------------------------------------------
{
   SLLNODE *p = sll->head;

   if ( GetSizeSLL(sll) == 0 ) RaiseADTException(SLL_UNDERFLOW);

   if ( GetSizeSLL(sll) == 1 )
   {
      sll->head = NULL;
      sll->tail = NULL;
   }
   else
   {
      sll->head = p->FLink;
   }
   if ( sll->DestructElement != NULL ) sll->DestructElement(p->element);
   free(p);
   sll->size--;
}

//--------------------------------------------------------------
void PushTailSLL(SLL *sll,const char *element)
//--------------------------------------------------------------
{
   SLLNODE *p = (SLLNODE *) malloc(sizeof(SLLNODE));

   if ( p == NULL ) RaiseADTException(MALLOC_ERROR);

   p->element = (char *) element;
   p->FLink = NULL;
   if ( IsEmptySLL(sll) )
   {
      sll->head = p;
      sll->tail = p;
   }
   else
   {
      sll->tail->FLink = p;
      sll->tail = p;
   }
   sll->size++;
}

//--------------------------------------------------------------
char *PeekSLL(const SLL *sll,const int offset)
//--------------------------------------------------------------
{
   SLLNODE *p = sll->head;
   int i;

   if ( !((0 <= offset) && (offset <= GetSizeSLL(sll)-1)) ) RaiseADTException(SLL_OFFSET_ERROR);

   for (i = 0; i <= offset-1; i++)
      p = p->FLink;
   return( p->element );
}

//--------------------------------------------------------------
bool IsEmptySLL(const SLL *sll)
//--------------------------------------------------------------
{
   return( sll->size == 0 );
}

//--------------------------------------------------------------
int GetSizeSLL(const SLL *sll)
//--------------------------------------------------------------
{
   return( sll->size );
}

