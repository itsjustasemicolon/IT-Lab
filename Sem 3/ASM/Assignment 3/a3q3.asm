 .model small
.stack 100h
.code

main proc
mov ax, @data
mov ds, ax

mov bl, 06h
l3:
mov si,0030h
mov cl,06h
l1:
mov al,[si]
inc si
cmp al,[si]
jc l2
mov dl,[si]
mov [si],al
dec si
mov [si],dl
inc si
l2:
loop l1
dec bl
cmp bl,00h
jnz l3

int 03h
mov ah,4ch
int 21h

main endp
end main
