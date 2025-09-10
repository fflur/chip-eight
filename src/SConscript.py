Import('evrm')

# Setting the decider function to use 'content' as value.
evrm.Decider('content')

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