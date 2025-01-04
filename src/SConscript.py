Import('evrm')

incl_path = [
    'include',
    'C:/Users/pc/codes/c/libs/SDL2-2.30.9/x86_64-w64-mingw32/include'
]

lib_path = ['C:/Users/pc/codes/c/libs/SDL2-2.30.9/x86_64-w64-mingw32/lib']

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

def CompileToObject():
    # Creating object files. `CPPPATH` is used for implicit dependencies.
    intr_ob = evrm.Object('cpp/Interpreter.cpp', CPPPATH = incl_path[0])
    itrc_ob = evrm.Object('cpp/InstructionSet.cpp', CPPPATH = incl_path[0])
    dspl_ob = evrm.Object('cpp/Display.cpp', CPPPATH = incl_path)
    cnsl_ob = evrm.Object('cpp/Console.cpp', CPPPATH = incl_path)

    # `Depends` is used for explicit dependencies.
    evrm.Depends(itrc_ob, intr_ob)
    evrm.Depends(dspl_ob, itrc_ob)
    evrm.Depends(cnsl_ob, itrc_ob)
    return

CompileToObject()
