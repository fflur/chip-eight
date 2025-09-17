Import('evrm')
import os

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

def Compile():
    # Source files to be compiled into object files.
    rgtr_ob = evrm.Object('cpp/registers.cpp')
    mmry_ob = evrm.Object('cpp/memory.cpp')
    xcps_ob = evrm.Object('cpp/chip_exceptions.cpp')
    stck_ob = evrm.Object('cpp/stack.cpp')

    # Object files dependencies.
    evrm.Depends(rgtr_ob, xcps_ob)
    evrm.Depends(mmry_ob, xcps_ob)
    evrm.Depends(stck_ob, xcps_ob)
    return

Compile()