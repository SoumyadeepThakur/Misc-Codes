;seperate out odd and even no from a given sequence of numbers

START: LDA 204FH ;length of sequence
STA 204EH ;store no of elements in temprary location
LXI H,2500H ;numbers in sequence
LXI B,2100H ;even numbers
LXI D,2200H ;odd numbers
LOOP: MOV A,M
RAR
JC ODD ;check for odd
RAL ;restore number
STAX B ;store even number in [BC]
LDA 2300H
INR A
STA 2300H ;increment count of even numbers
INX B
JMP NEXT
ODD: RAL ;restore the number
STAX D ;store odd number in [DE] location
LDA 2301H
INR A
STA 2301H ;increment count of odd number
INX D
NEXT: INX H
LDA 204EH
DCR A
STA 204EH
JNZ LOOP
HLT

 
