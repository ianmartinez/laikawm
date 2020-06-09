#ifndef LK_UTIL_H
#define LK_UTIL_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/**
 * Contains various helper functions to
 * make life easier.
 */

/**
 * Concat an arbitrary # of strings.
 * 
 * char *str = concat(2, "a", "b");
 * (* do something with it *)
 * free(str);
 * 
 * From: https://stackoverflow.com/a/11394336
 */
char *str_concat(int count, ...);

#endif