;AUTHOR: SOUMYADEEP THAKUR
;DATE: 21 OCT 2017

.model small
.stack 300h
.data
msg1 db 0AH,0DH,'Enter number: $'
msg2 db 0AH,0DH,'Number is palindrome $'
msg3 db 0AH,0DH,'Number is not palindrome $'
msg4 db 0AH,0DH,'Reverse: $'
endl db 0AH,0DH,'$'
val dw ?

.code
print macro msg
	push ax
	push dx
	mov ah, 09h
	lea dx, msg
	int 21h
	pop dx
	pop ax
endm

main proc
	mov ax,@data
	mov ds,ax
	
	start:
	
	print msg1
	
	call readnum
	
	
	mov val, ax
	
	call revword
	print msg4
	call writenum
	print endl
	cmp ax,val
	jnz notpal
	print msg2
	jmp exit
	notpal:
	print msg3
	exit:
    mov ah, 4ch
    int 21h
main endp
revword proc near
	; this procedure will take a number as input from user and store in AX
	; input : AX
	
	; output : AX
	
	push bx
	push cx
	push dx
	
	mov bx, 0ah 
	mov dx, 00h
	mov cx, 00h ; rev no stored here
	loop1:
		mov dx, 00h
		div bx ; stores rem of ax/bx in dx
		push ax
		push dx
		mov ax, cx
		mul bx
		pop dx
		add ax,dx
		mov cx,ax
		pop ax
		cmp ax, 00h
	jnz loop1
	
	mov ax, cx
	
	pop dx
	pop cx
	pop bx
	
	ret
revword endp

readnum proc near
	; this procedure will take a number as input from user and store in AX
	; input : none
	
	; output : AX

	
	push bx
	push cx
	mov cx,0ah
	mov bx,00h
	loopnum: 
		mov ah,01h
		int 21h
		cmp al,'0'
		jb skip
		cmp al,'9'
		ja skip
		sub al,'0'
		push ax
		mov ax,bx
		mul cx
		mov bx,ax
		pop ax
		mov ah,00h
		add bx,ax
	jmp loopnum
	
	skip:
	mov ax,bx
	pop cx
	pop bx
	ret
readnum endp

writenum proc near
	; this procedure will display a decimal number
	; input : AX
	; output : none

	push ax
	push bx                        
	push cx                        
	push dx                        

	xor cx, cx
	mov bx, 0ah                     

	@output:                       
		xor dx, dx                   
		div bx                       ; divide AX by BX
		push dx                      ; push remainder onto the STACK
		inc cx                       
		or ax, ax                    
	jne @output                    

	mov ah, 02h                      ; set output function

	@display:                      
		pop dx                       ; pop a value(remainder) from STACK to DX
		or dl, 30h                   ; convert decimal to ascii code
		int 21h                      
	loop @display                  

	pop dx                         
	pop cx                         
	pop bx 
	pop ax

	ret                            
writenum endp

end main
