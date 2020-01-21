#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct procInfStruc{

  int processId;
  char *processContext[6];
  char processStatus;
  struct procInfStruc *next;

};
