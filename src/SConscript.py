Import('evrm')

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

def compile():
    # Source files to be compiled into object files.
    chip_eght_ob = evrm.Object('cpp/chip_eight.cpp')
    xcps_ob = evrm.Object('cpp/chip_exceptions.cpp')
    rgtr_ob = evrm.Object('cpp/registers.cpp')
    mmry_ob = evrm.Object('cpp/memory.cpp')
    stck_ob = evrm.Object('cpp/stack.cpp')
    instrctn_st_ob = evrm.Object('cpp/instruction_set.cpp')
    dspy_ob = evrm.Object('cpp/display.cpp')
    cnsl_ob = evrm.Object('cpp/console.cpp')

    # Object files dependencies.
    evrm.Depends(rgtr_ob, xcps_ob)
    evrm.Depends(mmry_ob, xcps_ob)
    evrm.Depends(stck_ob, xcps_ob)
    evrm.Depends(instrctn_st_ob, [rgtr_ob, mmry_ob, stck_ob])
    evrm.Depends(dspy_ob, instrctn_st_ob)
    evrm.Depends(cnsl_ob, instrctn_st_ob)
    return

compile()