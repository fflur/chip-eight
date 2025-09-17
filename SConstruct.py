import config

# Setting the environment construction variable.
# CXX implies C++.
evrm = Environment(
    # Using GNU C++ compiler.
    CXX = "g++",
    # Using C++ 20 standard.
    CXXFLAGS = ["-std=c++11", "-Wall", "-Wextra", "-Wpedantic", "-Werror"],
    # header files path
    CPPPATH = config.header_path,
    # library files path
    LIBPATH = config.library_path,
    # Libraries names without 'lib' prefix and '.a' suffix
    LIBS = ["SDL2main", "SDL2"]
)

Export('evrm')
SConscript("src/SConscript.py", variant_dir = "build")