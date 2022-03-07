#ifndef DTS_FL_H
#define DTS_FL_H

#include <stdio.h>
#include <string.h>

#include "err.h"

int file_write(char *file_name, char *data);

int file_search(char *file_name, char *data, int *n);

#endif 
