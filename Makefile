
format:
	@(clang-format -i src/*)
	@(cmake-format -i CMakeLists.txt)
