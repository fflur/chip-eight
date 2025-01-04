# Setting the environment construction variable.
# CXX implies C++.
evrm = Environment(
    CXX = 'g++',       # Using GNU C++ compiler.
    CXXVERSION = '20', # Using C++ 17.
    CXXFLAGS = '-std=c++20'    # Suppress warnings.
)

Export('evrm')
SConscript('src/SConscript.py', variant_dir = 'build')
