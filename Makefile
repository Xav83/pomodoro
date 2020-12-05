
format:
	@(clang-format -i src/*pp src/color/*pp)
	@(cmake-format -i CMakeLists.txt)
