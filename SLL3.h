//--------------------------------------------------------------
// Dr. Art Hanna
// Singly-linked list (SLL) abstract data type
// SLL3.h
//--------------------------------------------------------------
#ifndef SLL3_H
#define SLL3_H

//==============================================================
// Data model definitions
//==============================================================
typedef struct SLLNODE
{
   char *element;
   struct SLLNODE *FLink; // (F)orward Link to logically-next node
} SLLNODE;

typedef struct SLL
{
   int size;
   SLLNODE *head;         // pointer-to logically-first node
   SLLNODE *tail;         // pointer-to logically-last  node
   void (*DestructElement)(const char *element);
} SLL;

//==============================================================
// Public member function prototypes
//==============================================================
void ConstructSLL(SLL *sll,
void (*DestructElement)(const char *element));
void DestructSLL(SLL *sll);
void PushHeadSLL(SLL *sll,const char *element);
void PopHeadSLL(SLL *sll);
void PushTailSLL(SLL *sll,const char *element);
char *PeekSLL(const SLL *sll,const int offset);
bool IsEmptySLL(const SLL *sll);
int GetSizeSLL(const SLL *sll);
void PopTailSLL(SLL *sll);
bool IsInSLL(const SLL *sll,const char *element);
void InsertSLL(SLL *sll,const int offset,const char *element);
void DeleteSLL(SLL *sll,const int offset);

//==============================================================
// Private utility member function prototypes
//==============================================================
// (none)

#endif


