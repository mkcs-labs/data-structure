#include <stdio.h>
#include <assert.h>
#include "dynamic_array.h"

void test_dynamic_array_init();
void test_dynamic_array_insert();
void test_dynamic_array_delete();
void test_dynamic_array_peek();
void test_dynamic_array_realloc();

int main() {
    test_dynamic_array_init();
    test_dynamic_array_insert();
    test_dynamic_array_delete();
    test_dynamic_array_peek();
    test_dynamic_array_realloc();

    printf("모든 테스트를 통과했습니다!\n");
    return 0;
}

void test_dynamic_array_init() {
    DynamicArray array;
    dynamic_array_init(&array, sizeof(int));

    assert(array.size == 0);
    assert(array.capacity == DYNAMIC_ARRAY_INITIAL_CAPACITY);
    assert(array.data != NULL);

    dynamic_array_free(&array);
    printf("test_dynamic_array_init passed\n");
}

void test_dynamic_array_insert() {
    DynamicArray array;
    dynamic_array_init(&array, sizeof(int));

    const int value1 = 10;
    const int value2 = 20;
    const int value3 = 30;

    assert(dynamic_array_insert(&array, 1, &value1) == DYNAMIC_ARRAY_ERROR_OUT_OF_BOUNDS);
    assert(dynamic_array_insert(&array, 0, &value1) == DYNAMIC_ARRAY_SUCCESS);
    assert(dynamic_array_insert(&array, 1, &value2) == DYNAMIC_ARRAY_SUCCESS);
    assert(dynamic_array_insert(&array, 1, &value3) == DYNAMIC_ARRAY_SUCCESS);

    assert(array.size == 3);
    assert(*(int *)dynamic_array_peek(&array, 0) == value1);
    assert(*(int *)dynamic_array_peek(&array, 1) == value3);
    assert(*(int *)dynamic_array_peek(&array, 2) == value2);

    dynamic_array_free(&array);
    printf("test_dynamic_array_insert passed\n");
}

void test_dynamic_array_delete() {
    DynamicArray array;
    dynamic_array_init(&array, sizeof(int));

    const int value1 = 10;
    const int value2 = 20;
    const int value3 = 30;

    dynamic_array_insert(&array, 0, &value1);
    dynamic_array_insert(&array, 1, &value2);
    dynamic_array_insert(&array, 2, &value3);

    assert(dynamic_array_delete(&array, 1) == DYNAMIC_ARRAY_SUCCESS);
    assert(array.size == 2);
    
    assert(*(int *)dynamic_array_peek(&array, 0) == value1);
    assert(*(int *)dynamic_array_peek(&array, 1) == value3);

    dynamic_array_free(&array);
    printf("test_dynamic_array_delete passed\n");
}

void test_dynamic_array_peek() {
    DynamicArray array;
    dynamic_array_init(&array, sizeof(int));

    const int value1 = 10;
    const int value2 = 20;

    dynamic_array_insert(&array, 0, &value1);
    dynamic_array_insert(&array, 1, &value2);

    assert(*(int *)dynamic_array_peek(&array, 0) == value1);
    assert(*(int *)dynamic_array_peek(&array, 1) == value2);

    dynamic_array_free(&array);
    printf("test_dynamic_array_peek passed\n");
}

void test_dynamic_array_realloc() {
    DynamicArray array;
    dynamic_array_init(&array, sizeof(int));

    for (int i = 0; i < 100; i++) {
        dynamic_array_insert(&array, i, &i);
    }

    for (int i = 0; i < 100; i++) {
        assert(*(int *)dynamic_array_peek(&array, i) == i);
    }

    dynamic_array_free(&array);
    printf("test_dynamic_array_realloc passed\n");
}