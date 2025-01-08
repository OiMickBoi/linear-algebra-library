// #include <cerrno>
// #include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/vector.h"

// Create a vector of given size
Vector* vector_create(int size) {
  Vector* v = malloc(sizeof(Vector));
  v->elements = malloc(size * sizeof(double));
  v->size = size;
  return v;
} 

// Clean up vector memory
void vector_destroy(Vector* v) {
  free(v->elements);
  free(v);
} 

// Print vector contents
void vector_print(Vector* v) {
  printf("[");
  for (int i = 0; i < v->size; i++) {
    printf("%f", v->elements[i]);
    if (i < v->size-1) printf(", ");
  }
  printf("]\n");
} 

// Set element at index i
void vector_set(Vector* v, int i, double x) {
  v->elements[i] = x;
} 

// Get element at index i
double vector_get(Vector* v, int i) {
  return v->elements[i];
} 

// Add two vectors together
// a + b = [a₁+b₁, a₂+b₂, ...]
Vector* vector_add(Vector* a, Vector* b) {
  // Check for null inputs
  if (a == NULL || b == NULL) {
    errno = EINVAL;
    return NULL;
  } 

  // Check to vectors are same size
  if (a->size != b->size) {
    errno = EINVAL;
    return NULL;
  }


  Vector* result = vector_create(a->size);
  for (int i = 0; i < a->size; i++) {
    result->elements[i] = a->elements[i] + b->elements[i];
  }
  return result;
}
