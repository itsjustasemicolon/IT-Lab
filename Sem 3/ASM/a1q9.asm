dosseg
.model small
.stack 100h
.data
.code

main proc

mov ax,@data
mov ds,ax
mov si,0040h
mov ax,[si]
mov si,0050h
mov bx,[si]
mul bx

mov si,0060h
mov [si],ax
mov si,0062h
mov [si],dx

int 03h
mov ah,4ch
int 21h

main endp
end main
