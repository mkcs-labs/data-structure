#include "dynamic_array.h"

/**
 * 동적 배열을 초기화합니다.
 *
 * @param dynamicArray 초기화할 동적 배열
 * @param element_size 요소의 크기
 */
void dynamic_array_init(DynamicArray *dynamicArray, size_t element_size) {
    dynamicArray->data = malloc(element_size * DYNAMIC_ARRAY_INITIAL_CAPACITY);
    dynamicArray->element_size = element_size;
    dynamicArray->size = 0;
    dynamicArray->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
}

/**
 * 동적 배열을 해제합니다.
 *
 * @param dynamicArray 해제할 동적 배열
 */
void dynamic_array_free(const DynamicArray *dynamicArray) {
    if (dynamicArray->data != NULL) {
        free(dynamicArray->data);
    }
}

/**
 * 동적 배열에 요소를 반환합니다.
 *
 * @param dynamicArray 동적 배열
 * @param index 인덱스
 * @return 인덱스에 해당하는 요소의 포인터
 */
void *dynamic_array_peek(const DynamicArray *dynamicArray, const size_t index) {
    if (index > dynamicArray->size) {
        return NULL;
    }
    return dynamicArray->data + index * dynamicArray->element_size;
}

/**
 * 동적 배열에 값을 삽입합니다.
 *
 * @param dynamicArray 동적 배열
 * @param index 인덱스
 * @param element 삽입할 요소
 * @return 동적 배열 오류
 */
DynamicArrayError dynamic_array_insert(DynamicArray *dynamicArray, const size_t index, const void *element) {
    const DynamicArrayError error = dynamic_array_realloc(dynamicArray);
    if (error != DYNAMIC_ARRAY_SUCCESS) {
        return error;
    }

    if (index > dynamicArray->size) {
        return DYNAMIC_ARRAY_ERROR_OUT_OF_BOUNDS;
    }

    void *destination = dynamicArray->data + (index + 1) * dynamicArray->element_size;
    const void *source = dynamicArray->data + index * dynamicArray->element_size;
    size_t bytes_to_move = (dynamicArray->size - index) * dynamicArray->element_size;
    memmove(destination, source, bytes_to_move);

    destination = dynamic_array_peek(dynamicArray, index);
    memcpy(destination, element, dynamicArray->element_size);
    dynamicArray->size++;

    return DYNAMIC_ARRAY_SUCCESS;
}

/**
 * 동적 배열에서 값을 삭제합니다.
 *
 * @param dynamicArray 동적 배열
 * @param index 인덱스
 * @return 동적 배열 오류
 */
DynamicArrayError dynamic_array_delete(DynamicArray *dynamicArray, const size_t index) {
    if (index >= dynamicArray->size) {
        return DYNAMIC_ARRAY_ERROR_OUT_OF_BOUNDS;
    }

    void *destination = dynamic_array_peek(dynamicArray, index);
    void *source = dynamic_array_peek(dynamicArray, index + 1);
    size_t bytes_to_move = (dynamicArray->size - index - 1) * dynamicArray->element_size;
    memmove(destination, source, bytes_to_move);
    dynamicArray->size--;

    return DYNAMIC_ARRAY_SUCCESS;
}

/**
 * 동적 배열의 용량을 재할당합니다.
 *
 * @param dynamicArray 동적 배열
 * @return 동적 배열 오류
 */
DynamicArrayError dynamic_array_realloc(DynamicArray *dynamicArray) {
    if (dynamicArray->size < dynamicArray->capacity) {
        return DYNAMIC_ARRAY_SUCCESS;
    }

    const size_t new_capacity = dynamicArray->capacity * DYNAMIC_ARRAY_GROWTH_FACTOR;
    void *new_data = realloc(dynamicArray->data, new_capacity * dynamicArray->element_size);
    if (new_data == NULL) {
        return DYNAMIC_ARRAY_ERROR_OUT_OF_BOUNDS;
    }

    dynamicArray->data = new_data;
    dynamicArray->capacity = new_capacity;
    return DYNAMIC_ARRAY_SUCCESS;
}
