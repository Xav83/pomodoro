
format:
	@(clang-format -i src/*pp src/color/*pp src/utility/*pp tst/*pp)
	@(cmake-format -i CMakeLists.txt .cmake/*cmake)
