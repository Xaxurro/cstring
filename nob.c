#define NOB_IMPLEMENTATION
#define NOB_NO_ECHO

#include "nob.h"
#include "cstring.h"

#define BUILD_DIR "build/"
#define TESTS_DIR "tests/"
#define VSTRING "vstring/"
#define BSTRING "bstring/"

char build_tests() {
	if (!nob_mkdir_if_not_exists(TESTS_DIR)) return 1;
	if (!nob_mkdir_if_not_exists(TESTS_DIR VSTRING)) return 1;
	if (!nob_mkdir_if_not_exists(TESTS_DIR BSTRING)) return 1;
	if (!nob_mkdir_if_not_exists(BUILD_DIR)) return 1;
	if (!nob_mkdir_if_not_exists(BUILD_DIR VSTRING)) return 1;
	if (!nob_mkdir_if_not_exists(BUILD_DIR BSTRING)) return 1;

	Nob_File_Paths tests = {0};

	const char* test_directory[] = {
		TESTS_DIR VSTRING,
		TESTS_DIR BSTRING
	};

	nob_read_entire_dir(test_directory[0], &tests);

	const vstring ignored_files[] = {
		vstring_from("."),
		vstring_from("..")
	};

	Nob_Cmd cmd = {0};

	for (size_t i = 0; i < tests.count; i++) {
		if (vstring_equals(&ignored_files[0], tests.items[i]) == true) continue;
		if (vstring_equals(&ignored_files[1], tests.items[i]) == true) continue;
		vstring path = vstring_from(tests.items[i]);

		bstring full_path = bstring_from(TESTS_DIR VSTRING);
		bstring_concat(&full_path, &path);

		bstring build_path = bstring_from(BUILD_DIR VSTRING);
		vstring_remove_right(&path, 2);
		bstring_concat(&build_path, &path);

		printf("\nbuilding %s at %s", full_path.data, build_path.data);

		nob_cmd_append(&cmd, "clang", "-std=c23", "-Wall", "-Wextra", "-o", build_path.data, full_path.data);
		if (!nob_cmd_run(&cmd)) return 1;
	}
	return 0;
}

char run_tests() {
	if (!nob_mkdir_if_not_exists(BUILD_DIR VSTRING)) return 1;
	if (!nob_mkdir_if_not_exists(BUILD_DIR BSTRING)) return 1;

	Nob_File_Paths tests = {0};

	const char* test_directory[] = {
		BUILD_DIR VSTRING,
		BUILD_DIR BSTRING
	};

	nob_read_entire_dir(test_directory[0], &tests);

	const vstring ignored_files[] = {
		vstring_from("."),
		vstring_from("..")
	};

	Nob_Cmd cmd = {0};

	for (size_t i = 0; i < tests.count; i++) {
		if (vstring_equals(&ignored_files[0], tests.items[i]) == true) continue;
		if (vstring_equals(&ignored_files[1], tests.items[i]) == true) continue;

		vstring path = vstring_from(tests.items[i]);

		bstring build_path = bstring_from(BUILD_DIR VSTRING);
		bstring_concat(&build_path, &path);

		printf("\nrunning %s", build_path.data);

		nob_cmd_append(&cmd, build_path.data);
		if (!nob_cmd_run(&cmd)) return 1;
	}
	return 0;
}


char scratchpad() {
	Nob_Cmd cmd = {0};
	nob_cmd_append(&cmd, "clang", "-std=c23", "-Wall", "-Wextra", "-o", "scratchpad", "scratchpad.c");
	if (!nob_cmd_run(&cmd)) return 1;
	return 0;
}

int main(int argc, char **argv) {
	NOB_GO_REBUILD_URSELF(argc, argv);
	if (!nob_mkdir_if_not_exists(BUILD_DIR)) return 1;
	printf("\n---Building Tests---");
	build_tests();
	printf("\n");
	printf("\n---Running Tests---");
	run_tests();
	//scratchpad();
	return 0;
}
