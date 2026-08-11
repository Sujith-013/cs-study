.PHONY: test test-cpp test-py clean

BUILD_DIR := build

test: test-cpp test-py

test-cpp:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DIR) -j
	ctest --test-dir $(BUILD_DIR) --output-on-failure

# pytest exits 5 when it collects zero tests, which happens whenever a
# module doesn't have a test file yet. Treat that as success; any other
# non-zero exit (an actual failure or error) still fails the build.
test-py:
	pytest; ec=$$?; \
	if [ $$ec -eq 5 ]; then \
		echo "no Python tests collected yet"; \
	elif [ $$ec -ne 0 ]; then \
		exit $$ec; \
	fi

clean:
	rm -rf $(BUILD_DIR) .pytest_cache
	find . -type d -name '__pycache__' -exec rm -rf {} +
