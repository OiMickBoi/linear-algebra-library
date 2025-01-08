#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  double* elements;  // Array to hold the vector elements 
  int size;          // Size of the vector
} Vector;

// Basic vector operations
Vector* vector_create(int size);              // Create a vector of given size
void vector_destroy(Vector* v);               // Clean up vector memory
void vector_print(Vector* v);                 // Print vector contents
void vector_set(Vector* v, int i, double x);  // Set element at index i
double vector_get(Vector* v, int i);          // Get element at index i

// Vector addition, 
// multiplication, 
// and dot product 
Vector* vector_add(Vector* a, Vector* b);      // Adds two vectors together
Vector* vector_scalar_multiply(Vector* v, double scalar);  
double vector_inner_product(Vector* a, Vector* b);

#endif
