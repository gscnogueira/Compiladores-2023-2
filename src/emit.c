#include <stdio.h>
#include "globals.h"

// current code line
static int line = 0;

/*
highest line emitted
static int highestLine = 0;
*/

/* emitRO: emite uma instrucao do tipo Register-Only
    (todos os operadores sao registradores)
    op -> opcode da operacao
    reg_r -> registrador destino
    reg_s -> origem 1
    reg_t -> origem 2
*/
void emitRO(char* op, int reg_r, int reg_s, int reg_t){
    fprintf(output_file, "%3d: %5s %d,%d,%d\n", line++, op, reg_r, reg_s, reg_t);
}


/* emitRM: emite uma instrucao do tipo Register-Memory
    (todos os operadores sao registradores)
    op -> opcode da operacao
    reg_r -> registrador destino
    reg_s -> deslocamento
    reg_t -> registrador base
    comment -> comentario impresso em modo debug
*/
void emitRM(char* op, int reg_r, int reg_d, int reg_s){
    fprintf(output_file, "%3d: %5s %d,%d(%d)\n", line++, op, reg_r, reg_d, reg_s);
}

void emitComment(char* comment){
    if (TraceAnalyze) {fprintf(output_file, "*%s\n", comment);}
}