#include <stdio.h>
#include <assert.h>  // Standard C library header
#include <stdbool.h> // For boolean values
#include <math.h> // For boolean values
#include "../include/vector.h"

// Test helper function
bool approx_equal(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}

void test_vector_create() {
  printf("Testing vector creation...\n");
  
  Vector* v = vector_create(3);
  if (v == NULL) {
    fprintf(stderr, "ERROR: Failed to create vector\n");
    return;
  }
  
  assert(v->size == 3);
  assert(v->elements != NULL);
  
  vector_destroy(v);
  printf("✓ Vector creation test passed\n");
}

void test_vector_set_get() {
  printf("Testing vector set/get operations...\n");
  
  Vector* v = vector_create(3);
  if (v == NULL) {
    fprintf(stderr, "ERROR: Failed to create vector\n");
    return;
  }
  
  // Test setting and getting values
  vector_set(v, 0, 1.0);
  vector_set(v, 1, 2.0);
  vector_set(v, 2, 3.0);
  
  assert(approx_equal(vector_get(v, 0), 1.0, 1e-10));
  assert(approx_equal(vector_get(v, 1), 2.0, 1e-10));
  assert(approx_equal(vector_get(v, 2), 3.0, 1e-10));
  
  vector_destroy(v);
  printf("✓ Vector set/get test passed\n");
}

int main() {
  printf("\nRunning vector tests...\n");
  printf("------------------------\n");
  
  test_vector_create();
  test_vector_set_get();
  
  printf("------------------------\n");
  printf("All tests passed!\n\n");
  return 0;
}
