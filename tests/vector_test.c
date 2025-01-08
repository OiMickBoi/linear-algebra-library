#include <stdio.h>
#include <assert.h>  // Standard C library header
#include <stdbool.h> // For boolean values
#include <math.h> // For boolean values
#include <errno.h> 
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


// Test vector addition with valid inputs
void test_vector_add_valid() {
    printf("Testing vector addition with valid inputs...\n");
    
    // Create test vectors
    Vector* a = vector_create(3);
    Vector* b = vector_create(3);
    
    // Set values for first vector
    vector_set(a, 0, 1.0);  // [1.0, 2.0, 3.0]
    vector_set(a, 1, 2.0);
    vector_set(a, 2, 3.0);
    
    // Set values for second vector
    vector_set(b, 0, 4.0);  // [4.0, 5.0, 6.0]
    vector_set(b, 1, 5.0);
    vector_set(b, 2, 6.0);
    
    // Add vectors
    Vector* sum = vector_add(a, b);
    assert(sum != NULL);
    
    // Check result [5.0, 7.0, 9.0]
    assert(approx_equal(vector_get(sum, 0), 5.0, 1e-10));
    assert(approx_equal(vector_get(sum, 1), 7.0, 1e-10));
    assert(approx_equal(vector_get(sum, 2), 9.0, 1e-10));
    
    // Clean up
    vector_destroy(a);
    vector_destroy(b);
    vector_destroy(sum);
    
    printf("✓ Valid vector addition test passed\n");
}

// Test vector addition with NULL inputs
void test_vector_add_null() {
    printf("Testing vector addition with NULL inputs...\n");
    
    Vector* a = vector_create(2);
    Vector* result;
    
    // Test first argument NULL
    result = vector_add(NULL, a);
    assert(result == NULL);
    assert(errno == EINVAL);
    
    // Test second argument NULL
    result = vector_add(a, NULL);
    assert(result == NULL);
    assert(errno == EINVAL);
    
    // Test both arguments NULL
    result = vector_add(NULL, NULL);
    assert(result == NULL);
    assert(errno == EINVAL);
    
    // Clean up
    vector_destroy(a);
    
    printf("✓ NULL input tests passed\n");
}

// Test vector addition with mismatched dimensions
void test_vector_add_mismatched_dims() {
    printf("Testing vector addition with mismatched dimensions...\n");
    
    Vector* a = vector_create(2);  // 2D vector
    Vector* b = vector_create(3);  // 3D vector
    
    Vector* result = vector_add(a, b);
    assert(result == NULL);
    assert(errno == EINVAL);
    
    // Clean up
    vector_destroy(a);
    vector_destroy(b);
    
    printf("✓ Mismatched dimensions test passed\n");
}

// Test vector addition with zero vectors
void test_vector_add_zero() {
    printf("Testing vector addition with zero vectors...\n");
    
    Vector* a = vector_create(2);
    Vector* b = vector_create(2);
    
    // Set first vector to [0, 0]
    vector_set(a, 0, 0.0);
    vector_set(a, 1, 0.0);
    
    // Set second vector to [1, 1]
    vector_set(b, 0, 1.0);
    vector_set(b, 1, 1.0);
    
    // Add vectors
    Vector* sum = vector_add(a, b);
    assert(sum != NULL);
    
    // Result should be [1, 1]
    assert(approx_equal(vector_get(sum, 0), 1.0, 1e-10));
    assert(approx_equal(vector_get(sum, 1), 1.0, 1e-10));
    
    // Clean up
    vector_destroy(a);
    vector_destroy(b);
    vector_destroy(sum);
    
    printf("✓ Zero vector addition test passed\n");
}

int main() {
  printf("\nRunning vector tests...\n");
  printf("------------------------\n");
  

  test_vector_create();
  test_vector_set_get();
  test_vector_add_valid();
  test_vector_set_get();
  test_vector_add_mismatched_dims();
  test_vector_add_zero();

  printf("------------------------\n");

  printf("All tests passed!\n\n");
  return 0;
}
