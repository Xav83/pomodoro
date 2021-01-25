
format:
	@(clang-format -i src/command_line/*pp src/shared/*pp src/shared/color/*pp src/shared/utility/*pp tst/*pp)
	@(cmake-format -i CMakeLists.txt .cmake/*cmake)
