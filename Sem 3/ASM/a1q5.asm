.model small
.stack 100h
.data
.code

main proc
mov ax,3000h
mov ds,ax
mov si,0030h
mov di,0050h
mov bx,0000h
mov [di],bx
add di,02h
mov [di],bl
sub di, 02h

mov cx,0005h

looping:
	mov bx,[si]
	add [di],bx
	mov bl,00h
	adc bl,bl
	add di,02h
	add [di],bl
	sub di,02h
	add si,02h
loop looping
mov ah,03h
mov ah,4ch
int 21h
main endp
end
