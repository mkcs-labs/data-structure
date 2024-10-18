CC = gcc
CFLAGS = -I./include -g
BUILD_DIR = ./build

# src와 test 디렉토리 내의 모든 .c 파일을 찾아서 SRCS에 저장
SRC_SRCS = $(wildcard ./src/*.c)
TEST_SRCS = $(wildcard ./test/*.c)

# .c 파일을 build 디렉토리로 .o 파일로 변환 (src와 test의 각각)
SRC_OBJS = $(patsubst ./src/%.c,$(BUILD_DIR)/src_%.o,$(SRC_SRCS))
TEST_OBJS = $(patsubst ./test/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SRCS))

# test 디렉토리 내의 .c 파일에 맞는 실행 파일 이름 결정
TEST_TARGETS = $(patsubst ./test/%.c,$(BUILD_DIR)/%,$(TEST_SRCS))

# 빌드 디렉토리 생성
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 기본 빌드 타겟: test 디렉토리의 각각의 .c 파일에 대한 실행 파일 생성
all: $(BUILD_DIR) $(TEST_TARGETS)

# 개별 테스트 타겟을 빌드하는 규칙 (각각의 test 소스 파일에 대해 실행 파일 생성)
$(BUILD_DIR)/%: $(BUILD_DIR)/test_%.o $(SRC_OBJS)
	$(CC) -o $@ $(BUILD_DIR)/test_$*.o $(SRC_OBJS) $(CFLAGS)

# src와 test 디렉토리의 각 소스 파일을 build 디렉토리로 컴파일하는 규칙
$(BUILD_DIR)/src_%.o: ./src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/test_%.o: ./test/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# 빌드 파일을 모두 제거
clean:
	rm -rf $(BUILD_DIR)