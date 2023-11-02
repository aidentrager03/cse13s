#include "set.h"

Set set_empty(void) {
    return 0;  // An empty set is represented as 0.
}

Set set_universal(void) {
    return 0xFF;  // The universal set contains all members (0-7).
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
    // Clear the x-th bit in the set (set it to 0).
    return s & ~(1 << x);
}

Set set_union(Set s, Set t) {
    // Compute the union using the bitwise OR operation.
    return s | t;
}

Set set_intersect(Set s, Set t) {
    // Compute the intersection using the bitwise AND operation.
    return s & t;
}

Set set_difference(Set s, Set t) {
    // Compute the difference using the bitwise AND and NOT operations.
    return s & ~t;
}

Set set_complement(Set s) {
    // Compute the complement using the bitwise NOT operation.
    return ~s;
}
