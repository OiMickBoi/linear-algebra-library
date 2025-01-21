#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

Vector* vector_scalar_multiply(Vector* v, double scalar){
  // Check for null inputs
  if (v == NULL) {
    errno = EINVAL;
    return NULL;
  } 
  
  Vector* result = vector_create(v->size);
  for (int i = 0; i < v->size; i++) {
    result->elements[i] = v->elements[i] * scalar;
  }
  return result;
}  

double vector_inner_product(Vector* a, Vector* b){
  if (a == NULL || b == NULL) {
    errno = EINVAL;
    return 0.0;
  } 

  // Check to vectors are same size
  if (a->size != b->size) {
    errno = EINVAL;
    return 0.0;
  }

  double sum = 0;

  for (int i = 0; i < a->size; i++) {
    sum += a->elements[i] * b->elements[i];
  }

  return sum;
}

double vector_magnitude(Vector* a) {
  double magnitude = 0;
  for (int i = 0; i < a->size; i++) {
    magnitude += a->elements[i] * a->elements[i];
	}
  return sqrt(magnitude);
}

Vector* vector_norm(Vector* a) {
  double magnitude = vector_magnitude(a);
	Vector* normalized = vector_create(a->size);
  for (int i = 0; i < normalized->size; i++) {
    normalized->elements[i] = a->elements[i] / magnitude;
	}
	return normalized;
}
