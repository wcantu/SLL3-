
//--------------------------------------------------------------
// Dr. Art Hanna
// SLL ADT Problem #3
// Problem3.c
//--------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

#include "Random.h"
#include "SLL3.h"

//--------------------------------------------------------------
int main()
//--------------------------------------------------------------
{
   void DestructElement(const char *element);
   char *NewElement();
   void DisplayElement(char *element);
   bool SwapAscending(const char *LHS,const char *RHS);

   int pushN;

   SetRandomSeed();
   printf("pushN? ");
   while ( scanf("%d",&pushN) != EOF )
   {
      SLL sll;
      int n;

      ConstructSLL(&sll,DestructElement);

      for (n = 1; n <= pushN; n++)
      {
         int offset = RandomInt(0,GetSizeSLL(&sll));
         
         InsertSLL(&sll,offset,NewElement());
         printf("offset = %2d: ",offset); TraverseSLL(&sll,DisplayElement); printf("\n");
      }
      printf("\n");

      SortSLL(&sll,SwapAscending);

      printf("sorted: "); TraverseSLL(&sll,DisplayElement); printf("\n\n");

      do
      {
         int offset = RandomInt(0,GetSizeSLL(&sll)-1);
         char buffer[256+1];
         
         DeleteSLL(&sll,offset);
         sprintf(buffer,"offset = %2d: ",offset);
         if ( IsEmptySLL(&sll) )
            strcat(buffer,"(empty)");
         else
         {
            for (offset = 0; offset <= GetSizeSLL(&sll)-1; offset++)
            {
               strcat(buffer,PeekSLL(&sll,offset));
               strcat(buffer,(offset != GetSizeSLL(&sll)-1) ? " " : "\n");
            }
         }
         printf("%s",buffer);
      } while ( !IsEmptySLL(&sll) );
      printf("\n");

      DestructSLL(&sll);
      printf("\npushN? ");
   }

   system("PAUSE");
   return( 0 );
}

//--------------------------------------------------------------
char *NewElement()
//--------------------------------------------------------------
{
   const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

   int i;
   int len = RandomInt(3,7);
   char *element = (char *) malloc(sizeof(char)*(len+1));

   for (i = 0; i <= len-1; i++)
      element[i] = RandomChar((char *) ALPHABET,26);
   element[len] = '\0';
   return( element );
}

//--------------------------------------------------------------
void DisplayElement(char *element)
//--------------------------------------------------------------
{
   printf("%s ",element);
}

//--------------------------------------------------------------
void DestructElement(const char *element)
//--------------------------------------------------------------
{
   free((char *) element);
}

//--------------------------------------------------------------
bool SwapAscending(const char *LHS,const char *RHS)
//--------------------------------------------------------------
{
   return( strcmp(LHS,RHS) > 0 );
}


