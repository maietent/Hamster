notes for me to not forget what i wanna do exactly  

hamster.conf:  
define user defined "steps" for the build  

example config file:  
```
Compiler = g++;
Linker = g++;

Warnings = -Wall;

Include = include/;
SRC = src/;

Bin = bin/;
Output = myprogram;

CompilerArgs = -O2;

Step: compile
{
    compile SRC into bin/ with CompilerArgs, Warnings, Include;
}

Step: link
{
    link all objects in bin/ into Output with LinkerArgs;
}

Step: run_scripts
{
    run scripts/script1.sh;
    run scripts/script2.sh;
}

Build
{
    run-step compile();
    run-step link();
}

Entry
{
    run-build;

    if "run" in Args: # args is gonna be builtin var with the arguments passed into hamster
        print("running");
        run-cmd "./my_program";
}

```  


execution flow:  
entry -> parse args -> start reading hamster.conf in working dir ->  
parse variables -> parse all steps, inline the variables and convert them to their respective commands ->  
run the commands in the order defined in entry
