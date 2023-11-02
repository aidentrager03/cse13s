#include "set.h"

Set set_empty(void) {
    return (Set) 0;
}

bool set_member(Set s, int x) {
    // Check if the x-th bit is set in the set.
    return (s & (1 << x)) != 0;
}

Set set_insert(Set s, int x) {
    // Set the x-th bit in the set to 1.
    return s | (1 << x);
}

Set set_remove(Set s, int x) {
    // Clear the x-th bit in the set to 0.
    return s & ~(1 << x);
}

Set set_union(Set s, Set t) {
    // Perform a bitwise OR operation to get the union of two sets.
    return s | t;
}

Set set_intersect(Set s, Set t) {
    // Perform a bitwise AND operation to get the intersection of two sets.
    return s & t;
}

Set set_difference(Set s, Set t) {
    // Perform a bitwise AND NOT operation to get the difference of two sets.
    return s & ~t;
}

Set set_complement(Set s) {
    // Perform a bitwise NOT operation to get the complement of the set.
    return ~s;
}
