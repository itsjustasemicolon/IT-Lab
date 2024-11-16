.model small
.stack 100h
.data
.code

main proc
    mov ax, @data
    mov ds, ax

    mov si, 0030h

    ;mov bl, [si]
    ;mov bh, 01h
    ;mov al, [bx]

    mov al, [si] ; taking input in al
    mov bx, 0100h ; moving to starting address of lookup table
    xlat

    mov si, 0040h
    mov [si], al

    int 03h
    mov ah, 4ch
    int 21h
main endp
end main
