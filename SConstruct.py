# Setting the environment construction variable.
# CXX implies C++.
evrm = Environment(
    # Using GNU C++ compiler.
    CXX = 'g++',

    # Using C++ 20 standard. Doesn't work for some reason.
    CXXVERSION = '20',

    # Suppress warnings.
    # Using C++20 standard.
    CXXFLAGS = '-std=c++20 -w'
)

Export('evrm')
SConscript('src/SConscript.py', variant_dir = 'build')
