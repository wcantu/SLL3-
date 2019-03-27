#include <stdlib.h>

#include <stdbool.h>

#include <time.h>
#ifndef ADTEXCEPTIONS_H

#define ADTEXCEPTIONS_H

// ADT exception definitions

#define MALLOC_ERROR                "malloc() error"

#define DATE_ERROR                  "DATE error"

#define SLL_CAPACITY_ERROR        "STACK capacity error"

#define SLL_UNDERFLOW             "STACK underflow"

#define SLL_OVERFLOW              "STACK overflow"

#define SLL_OFFSET_ERROR          "STACK offset error"

// ADT exception-handler prototype

void RaiseADTException(char exception[]);

#endif
