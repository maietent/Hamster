notes for me to not forget what i wanna do exactly  

hamster.conf:  
define user defined "steps" for the build  

example config file:  
```
compiler = g++;
linker = g++;

warnings = -Wall;
compiler_args = -O2;

src_dir = src/;
include_dir = include/;
bin_dir = bin/;
output = myprogram;

step compile {
    compile src_dir into bin_dir
        with compiler_args, warnings, include_dir;
}

step link {
    link all objects in bin_dir
        into output;
}

step run_scripts {
    run scripts/script1.sh;
    run scripts/script2.sh;
}

build default {
    run compile;
    run link;
}

entry main {
    run default;

    if "run" in args {
        print("running");
        run_cmd "./myprogram";
    }
}

```  


execution flow:  
entry -> parse args -> start reading hamster.conf in working dir ->  
parse variables -> parse all steps, inline the variables and convert them to their respective commands ->  
run the commands in the order defined in entry
