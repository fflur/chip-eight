# Setting the environment construction variable.
# CXX implies C++.
evrm = Environment(
    # Using GNU C++ compiler.
    CXX = 'g++',

    # Using C++ 11 standard. Doesn't work for some reason.
    # CXXVERSION = '11',

    # Suppress warnings.
    # Using C++20 standard.
    CXXFLAGS = '-std=c++11 -w'
)

Export('evrm')
SConscript('src/SConscript.py', variant_dir = 'build')