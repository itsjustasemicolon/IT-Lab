dosseg
.model small
.stack 100h
.data
.code

main proc
mov ax,@data
mov es,ax
mov di,0030h
mov cx,0008h
mov al,55h
mov ah,00h

cld

l2: 
	scasb
	jnz l1
	inc ah

l1:loop l2
mov di,0040h
mov [di],ah

int 03h
mov ah,4ch
int 21h
main endp
end main
