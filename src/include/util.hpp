#ifndef LK_UTIL_H
#define LK_UTIL_H

#include <algorithm>
#include <vector>

/**
 * Contains various helper functions to
 * make life easier.
 */

template <typename T>
void moveItemToBack(std::vector<T>& v, T item);

#endif