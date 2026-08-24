CXX = g++
CXXFLAGS = -std=c++17 -g -O0 -Wall -Wextra -Wpedantic -Iinclude

BUILD_DIR = build/bin
PROGRAM = $(BUILD_DIR)/ssccreader
TEST_PROGRAM = $(BUILD_DIR)/ssccvalidator_tests

all: $(PROGRAM)

$(BUILD_DIR):
	mkdir -p $@

$(PROGRAM): src/main.cpp src/sscc_validator.cpp Makefile | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/main.cpp src/sscc_validator.cpp -o $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(TEST_PROGRAM): tests/sscc_validator_tests.cpp src/sscc_validator.cpp Makefile | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) tests/sscc_validator_tests.cpp src/sscc_validator.cpp -lgtest_main -lgtest -pthread -o $(TEST_PROGRAM)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

clean:
	rm -rf build
