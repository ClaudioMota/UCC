md build
gcc -D_MALLOC=new -D_FREE=delete -Isource^
    source/platform/windows.c^
    source/main.c^
    source/grammar/stateMachine.c^
    source/grammar/grammar.c^
    source/grammar/lalrMachine.c^
    source/generation/generation.c^
    source/parsers/lexer.c^
    source/parsers/ucc/parser.c^
    source/parsers/ucc/conversion.c^
    source/parsers/parser.c^
    source/utils.c -o build/ucc.exe