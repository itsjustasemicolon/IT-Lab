dosseg
.model small
.stack 100h
.data
.code

main proc
mov ax,@data
mov ds,ax
mov si,0050h
mov al,[si]
mov si,0040h
sub al,[si]
das

mov si,0060h
mov [si],al
mov ah,00h
adc ah,ah
inc si
mov [si],ah

int 03h
mov ah,4ch
int 21h
main endp
end main
