.model small
.stack 100h
.data
.code

main proc
mov ax, @data
mov ds, ax
mov si, 0030h
mov al, [si]
not al
add al,01h
mov si, 0040h
add al,[si]

jc li 
;neg al
;do not use <neg> as it will modify the carry
not al
inc al

li:
mov si, 0050h
mov [si],al
mov ah,00h
cmc
adc ah, ah
inc si

mov [si], ah
int 03h
mov ah,4ch
int 21h
main endp
end main