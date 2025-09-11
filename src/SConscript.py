Import('evrm')

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

def CompileToObject():
    # Creating object files. `CPPPATH` is used for implicit dependencies.
    intr_ob = evrm.Object('cpp/interpreter.cpp')
    itrc_ob = evrm.Object('cpp/instruction_set.cpp')
    dspl_ob = evrm.Object('cpp/display.cpp')
    cnsl_ob = evrm.Object('cpp/console.cpp')
    chip_xcptn_ob = evrm.Object('cpp/chip_exceptions.cpp')
    chip_eght_ob = evrm.Object('cpp/chip_eight.cpp')

    # `Depends` is used for explicit dependencies.
    evrm.Depends(intr_ob, chip_xcptn_ob)
    evrm.Depends(itrc_ob, intr_ob)
    evrm.Depends(dspl_ob, itrc_ob)
    evrm.Depends(cnsl_ob, itrc_ob)
    evrm.Depends(chip_eght_ob, [dspl_ob, cnsl_ob])

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