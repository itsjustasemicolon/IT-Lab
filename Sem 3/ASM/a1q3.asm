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
cld
mov cx,0008h
rep movsb ;repeat command

mov ah,4ch
int 21h
main endp
end main

