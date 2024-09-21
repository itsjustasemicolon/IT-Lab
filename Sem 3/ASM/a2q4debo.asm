.model small
.stack 100h
.data
.code 

main proc
mov ax,@data
mov ds,ax
mov si,0030h
mov di, 0034h
mov cx,02h
l2 :
mov ah,[si]
mov bh, [di]
cmp ah,bh
jnz l1
inc SI
dec DI


mov ax,0FFFFh
mov bx,0040h
mov [bx],ax
loop l2
jmp l3

l1:
mov ax,1111h
mov bx,0040h
mov [bx],ax
l3:
int 03h
mov ah,4ch
int 21h
main endp
end main
