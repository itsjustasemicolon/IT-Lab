dosseg
.model small
.stack 100h
.data
.code

main proc
mov ax,@data
mov ds,ax
mov es,ax
mov si,0030h
mov di,0040h
mov cL,[si]
mov ch,00h ; cx is counter in toal, we are making the upper 2 bits 0 manually
cld

l2:
	cmpsb
	jnz l1
	loop l2

mov ax,0ffffh
jmp l3 ;otherwise 0ffffh is overwritten by 1111h

l1:
	mov ax,1111h

l3:
	mov bx,0050h
	mov [bx],ax
	int 03h
	mov ah,4ch
	int 21h
	main endp
	end main
