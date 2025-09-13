Import('evrm')
import os

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

def CompileToObject():
    # registers.hpp object file
    rgtr_ob = evrm.Object('cpp/registers.cpp')
    # memory.hpp object file
    mmry_ob = evrm.Object('cpp/memory.cpp')
    # chip_exceptions.hpp object file
    xcps_ob = evrm.Object('cpp/chip_exceptions.cpp')

    # Memory depends on the chip exceptions
    evrm.Depends(mmry_ob, xcps_ob)
    return

CompileToObject()