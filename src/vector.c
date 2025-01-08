#include <stdio.h>
#include <stdlib.h>
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
    printf("%f, ", v->elements[i]);
  }
  printf("[");
} 

// Set element at index i
void vector_set(Vector* v, int i, double x) {
  v->elements[i] = x;
} 

// Get element at index i
double vector_get(Vector* v, int i) {
  return v->elements[i];
} 
