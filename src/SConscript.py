Import('evrm')
import os

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

# MSYS2 installation directory
msys2_inst_drct = os.path.join(
    'C:\\Users', # Necessary for Windows paths
    'pc',
    'applications',
    'MSYS2',
    'mingw64'
)

# Include paths for header files
incl_path = [
    'include',
    os.path.join(msys2_inst_drct, 'include')
]

# Library path for linking
lib_path = os.path.join(msys2_inst_drct, 'lib')

# Appending include and library paths, and libraries to link against.
evrm.Append(CPPPATH = evrm.Dir(incl_path))
evrm.Append(LIBPATH = evrm.Dir(lib_path))
evrm.Append(LIBS = ["mingw32", "SDL2main", "SDL2"])  # Link against SDL2

def CompileToObject():
    # Creating object files. `CPPPATH` is used for implicit dependencies.
    intr_ob = evrm.Object('cpp/Interpreter.cpp')
    itrc_ob = evrm.Object('cpp/InstructionSet.cpp')
    dspl_ob = evrm.Object('cpp/Display.cpp')
    cnsl_ob = evrm.Object('cpp/Console.cpp')
    mory_ob = evrm.Object('cpp/ChipExceptions.cpp')
    chp8_ob = evrm.Object('cpp/chipeight.cpp')

    # `Depends` is used for explicit dependencies.
    evrm.Depends(intr_ob, mory_ob)
    evrm.Depends(itrc_ob, intr_ob)
    evrm.Depends(dspl_ob, itrc_ob)
    evrm.Depends(cnsl_ob, itrc_ob)
    evrm.Depends(chp8_ob, [dspl_ob, cnsl_ob])

    # Linking the object files to create the final executable.
    # evrm.Program(
    #     'chip8',
    #     [
    #         intr_ob,
    #         itrc_ob,
    #         dspl_ob,
    #         cnsl_ob,
    #         mory_ob,
    #         chp8_ob
    #     ]
    # )

    return

CompileToObject()