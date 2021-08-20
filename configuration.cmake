set(BINARY "output_bin")    # The output binary name

# The subdirectories of "src/" to find source code
# Use ${ARCH} variable to access architecture dependent directory
# Example: "arch/${ARCH}/subdir"
set(SRCDIRS #[["sub1" "sub2" "sub3"]])

# Directories to read metric tests
set(TESTDIRS "tests/feature" "tests/unit")

# The GLOB used to match source files
set(SRCGLOB "*.c" "*.s")
