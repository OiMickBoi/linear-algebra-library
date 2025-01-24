#include <stdio.h>
#include <stdlib.h>
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


void test_scalar_mult_basic() {
    printf("Testing basic scalar multiplication...\n");
    
    Vector* v = vector_create(3);
    // Create vector [1.0, 2.0, 3.0]
    vector_set(v, 0, 1.0);
    vector_set(v, 1, 2.0);
    vector_set(v, 2, 3.0);
    
    // Multiply by 2.0
    Vector* result = vector_scalar_multiply(v, 2.0);
    assert(result != NULL);
    
    // Check result is [2.0, 4.0, 6.0]
    assert(approx_equal(vector_get(result, 0), 2.0, 1e-10));
    assert(approx_equal(vector_get(result, 1), 4.0, 1e-10));
    assert(approx_equal(vector_get(result, 2), 6.0, 1e-10));
    
    vector_destroy(v);
    vector_destroy(result);
    
    printf("✓ Basic scalar multiplication test passed\n");
}

// Test multiplication by zero
void test_scalar_mult_zero() {
    printf("Testing multiplication by zero...\n");
    
    Vector* v = vector_create(2);
    vector_set(v, 0, 5.0);
    vector_set(v, 1, -3.0);
    
    Vector* result = vector_scalar_multiply(v, 0.0);
    assert(result != NULL);
    
    // Check result is [0.0, 0.0]
    assert(approx_equal(vector_get(result, 0), 0.0, 1e-10));
    assert(approx_equal(vector_get(result, 1), 0.0, 1e-10));
    
    vector_destroy(v);
    vector_destroy(result);
    
    printf("✓ Zero multiplication test passed\n");
}

// Test multiplication by negative scalar
void test_scalar_mult_negative() {
    printf("Testing multiplication by negative scalar...\n");
    
    Vector* v = vector_create(2);
    vector_set(v, 0, 1.0);
    vector_set(v, 1, -2.0);
    
    Vector* result = vector_scalar_multiply(v, -2.0);
    assert(result != NULL);
    
    // Check result is [-2.0, 4.0]
    assert(approx_equal(vector_get(result, 0), -2.0, 1e-10));
    assert(approx_equal(vector_get(result, 1), 4.0, 1e-10));
    
    vector_destroy(v);
    vector_destroy(result);
    
    printf("✓ Negative scalar multiplication test passed\n");
}

// Test with NULL vector
void test_scalar_mult_null() {
    printf("Testing scalar multiplication with NULL vector...\n");
    
    Vector* result = vector_scalar_multiply(NULL, 2.0);
    assert(result == NULL);
    assert(errno == EINVAL);
    
    printf("✓ NULL vector test passed\n");
}

// Test with fractional scalar
void test_scalar_mult_fraction() {
    printf("Testing multiplication by fraction...\n");
    
    Vector* v = vector_create(2);
    vector_set(v, 0, 2.0);
    vector_set(v, 1, 4.0);
    
    Vector* result = vector_scalar_multiply(v, 0.5);
    assert(result != NULL);
    
    // Check result is [1.0, 2.0]
    assert(approx_equal(vector_get(result, 0), 1.0, 1e-10));
    assert(approx_equal(vector_get(result, 1), 2.0, 1e-10));
    
    vector_destroy(v);
    vector_destroy(result);
    
    printf("✓ Fractional multiplication test passed\n");
  }

void test_scalar_mult_empty() {
    printf("Testing scalar multiplication of empty vector...\n");
    
    // Create empty vector (dimension 0)
    Vector* v = vector_create(0);
    assert(v != NULL);
    assert(v->size == 0);
    
    // Multiply by some scalar
    Vector* result = vector_scalar_multiply(v, 2.5);
    assert(result != NULL);
    assert(result->size == 0);
    
    vector_destroy(v);
    vector_destroy(result);
    
    printf("✓ Empty vector multiplication test passed\n");
}


void test_inner_product_basic() {
    printf("Testing basic inner product...\n");
    
    // Create two 2D vectors: [1,2] and [3,4]
    Vector* a = vector_create(2);
    Vector* b = vector_create(2);
    
    vector_set(a, 0, 1.0);
    vector_set(a, 1, 2.0);
    vector_set(b, 0, 3.0);
    vector_set(b, 1, 4.0);
    
    // [1,2]·[3,4] = 1*3 + 2*4 = 11
    double result = vector_inner_product(a, b);
    double expected = 11.0;
    
    if (!approx_equal(result, expected, 1e-10)) {
        printf("❌ Test failed!\n");
        printf("Expected: %f\n", expected);
        printf("Actual: %f\n", result);
        printf("Vectors:\n");
        printf("a = ");
        vector_print(a);
        printf("b = ");
        vector_print(b);
        exit(1);
    }
    
    vector_destroy(a);
    vector_destroy(b);
    printf("✓ Basic inner product test passed\n");
}
void test_inner_product_zero_vector() {
    printf("Testing inner product with zero vector...\n");
    
    // Create [0,0] and [1,2]
    Vector* zero = vector_create(2);
    Vector* v = vector_create(2);
    
    vector_set(v, 0, 1.0);
    vector_set(v, 1, 2.0);
    
    double result = vector_inner_product(zero, v);
    assert(approx_equal(result, 0.0, 1e-10));
    
    vector_destroy(zero);
    vector_destroy(v);
    printf("✓ Zero vector inner product test passed\n");
}

void test_inner_product_different_dimensions() {
    printf("Testing inner product with different dimensions...\n");
    
    Vector* a = vector_create(2);  // 2D vector
    Vector* b = vector_create(3);  // 3D vector
    
    vector_set(a, 0, 1.0);
    vector_set(a, 1, 2.0);
    vector_set(b, 0, 1.0);
    vector_set(b, 1, 2.0);
    vector_set(b, 2, 3.0);
    
    double result = vector_inner_product(a, b);
    // Should return 0.0 and set errno
    assert(approx_equal(result, 0.0, 1e-10));
    
    vector_destroy(a);
    vector_destroy(b);
    printf("✓ Different dimensions test passed\n");
}

void test_inner_product_null() {
    printf("Testing inner product with NULL vectors...\n");
    
    Vector* v = vector_create(2);
    vector_set(v, 0, 1.0);
    vector_set(v, 1, 2.0);
    
    double result = vector_inner_product(NULL, v);
    assert(approx_equal(result, 0.0, 1e-10));
    
    result = vector_inner_product(v, NULL);
    assert(approx_equal(result, 0.0, 1e-10));
    
    vector_destroy(v);
    printf("✓ NULL vector test passed\n");
}

void test_inner_product_identical() {
    printf("Testing inner product of vector with itself...\n");
    
    // Create [1,2]
    Vector* v = vector_create(2);
    vector_set(v, 0, 1.0);
    vector_set(v, 1, 2.0);
    
    // [1,2]·[1,2] = 1*1 + 2*2 = 5
    double result = vector_inner_product(v, v);
    assert(approx_equal(result, 5.0, 1e-10));
    
    vector_destroy(v);
    printf("✓ Self inner product test passed\n");
}

void test_vector_magnitude() {
  printf("Testing vector magnitude...\n");
  
  // Create [1,2]
  Vector* v = vector_create(2);
  vector_set(v, 0, 3.0);
  vector_set(v, 1, 4.0);
  
  // sqrt(3^2 + 4^2) = 5
  double result = vector_magnitude(v);
  printf("The answer is ");
  printf("%lf\n", result);

  assert(approx_equal(result, 5.0, 1e-10));
  
  vector_destroy(v);
  printf("✓ Vector Magnitude test passed\n");
}

void test_vector_norm() {
  printf("Testing vector normalization...\n");

  // Create [3,4]
  Vector* v = vector_create(2);
  vector_set(v, 0, 3.0);
  vector_set(v, 1, 4.0);

  // v^=(3/5, 4/5)=(0.6,0.8)

  Vector* result = vector_norm(v);
  assert(approx_equal(result->elements[0], 0.6, 1e-10));
  assert(approx_equal(result->elements[1], 0.8, 1e-10));
  vector_destroy(v);
  vector_destroy(result);
  printf("✓ Vector normalization test passed\n");

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

  test_scalar_mult_basic();
  test_scalar_mult_zero();
  test_scalar_mult_negative();
  test_scalar_mult_null();
  test_scalar_mult_fraction();
  test_scalar_mult_empty();
  
  test_inner_product_basic();
  test_inner_product_zero_vector();
  test_inner_product_different_dimensions();
  test_inner_product_null();
  test_inner_product_identical();
  test_vector_magnitude();
  test_vector_norm();

  printf("------------------------\n");

  printf("All tests passed!\n\n");
  return 0;
}
