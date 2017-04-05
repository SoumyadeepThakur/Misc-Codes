;sort elements of an array of size [2000] starting from [2100]

START: LXI SP, 8000H
LDA 2000H ;length of array
MOV C,A ;length stored in C
LOOP: CALL MAXUPTOC ;find max element
MOV B,A ;store max element, (probably not required)
LXI H,2100H ;elements in array start from [2100]
CALL SWAPEND ;swap max with end element
DCR C
JNZ LOOP
HLT

MAXUPTOC: XRA A ;clear A
MOV B,C ;store length temporarily
LXI H,2100H
LXI D,2100H
LOOP2: CMP M
JNC NOTMAX ;if element at [DE] is not greater than max
MOV A,M ;update max
MOV E,L ;[DE]=[HL]
MOV D,H
NOTMAX: INX H
DCR B
JNZ LOOP2
RET

SWAPEND: MVI B,00H
DAD B
DCX H ;set H to address of end element
MOV B,M ;swap [HL] and [DE]
LDAX D
MOV M,A
MOV A,B
STAX D
RET
