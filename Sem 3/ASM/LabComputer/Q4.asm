.model small
.stack 100h
.data
.code

main proc
mov ax,@data
mov ds,ax
mov si,0030h
mov di,0050h
mov bx,0000h
mov [di],bx

looping:
	mov bl, [si]
	add [di], bl
	mov bl,00h
	add bl,bl
	inc di
	add [di],bl
	dec di
	inc si
loop looping
mov ah,4ch
int 21h
main endp
end main

