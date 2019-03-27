#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include "ADTExceptions.h"

//--------------------------------------------------------------

void RaiseADTException(char exception[])

//--------------------------------------------------------------

{

   fprintf(stderr,"\a\nException \"%s\"\n\n",exception);

   system("PAUSE");

   exit( 1 );

}
