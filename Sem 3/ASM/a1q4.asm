dosseg
.model small
.stack 100h
.data
.code

main proc
mov ax,@data
mov ds,ax
mov si,0030h
mov di,0050h
mov cx,0007h
mov ax,0000h
mov bx,0000h

l1:     mov bl,[si]
	add ax,bx
	inc si	
	loop l1

mov [di],ax
int 03h
mov ah,4ch
int 21h
main endp
end main

