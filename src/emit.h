#ifndef _EMIT_H_
#define _EMIT_H_

/*
ARQUITETURA TARGET MACHINE

8 REGISTRADORES, REG0,...,REG7
REG7 = PROGRAM COUNTER
REG6 = MEMORY POINTER
REG5 = GLOBAL POINTER
*/

#define pc_reg 7
#define mp_reg 6
#define gp_reg 5

// Envia instrução do tipo RO
void emitRO(char* op, int reg_r, int reg_s, int reg_t, char* comment);

// Envia instrução do tipo RM
void emitRM(char* op, int reg_r, int reg_d, int reg_s, char* comment);

// Envia comentário
void emitComment(char* comment);

/*

Instruções RO
-----------------------------------------
Formato	opcode r,s,t
-----------------------------------------
Opcode		Efeito
-----------------------------------------
HALT		interrompe execução (ignora operandos)
IN		reg[r] <- valor inteiro lido da entrada padrão (s e t ignorados)
OUT		reg[r] -> saída padrão (s e t ignorados)
ADD		reg[r] = reg[s] + reg[t]
SUB		reg[r] = reg[s] - reg[t]
MUL		reg[r] = reg[s] * reg[t]
DIV		reg[r] = reg[s] / reg[t] (pode gerar ZERO_DIV)
===========================================================
Instruções RM
-----------------------------------------
Formato	opcode r,d(s)
(a=d+reg[s]; referência feita a dMem[a] gera DMEM_ERR se a<0 ou a>= DADDR_SIZE)
-----------------------------------------
Opcode		Efeito
-----------------------------------------
LD		reg[r]=dMem[a]		(carrega r com valor de memoria em a)
LDA		reg[r]=a		(carrega e endereça a diretamente em r)
LDC		reg[r]=d		(carrega constante d diretamente em r)
ST		dMem[a]=reg[r]		(armazena valor em r na posição de memória a)
JLT		if (reg[r]<0) reg[PC_REG]=a (salta para instrução a se r negativo)
JLE		if (reg[r]<=0) reg[PC_REG]=a
JGE		if (reg[r]>=0) reg[PC_REG]=a
JGT		if (reg[r]>0) reg[PC_REG]=a
JEQ		if (reg[r]==0) reg[PC_REG]=a
JNE		if (reg[r]!=0) reg[PC_REG]=a
*/

#endif