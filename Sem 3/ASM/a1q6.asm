dosseg
.model small
.stack 100h
.data
.code

main proc
    mov ax, @data    ; Initialize data segment
    mov ds, ax
    
    mov si, 0030h    ; Starting address of BCD numbers
    mov di, 0040h    ; Address to store result (low byte)
    mov cx, 0005h    ; Loop counter for 5 BCD numbers
    mov ax, 0000h    ; Initialize accumulator for the result
    mov dl, 00h      ; DL will hold the overflow (if any)

l1: 
    mov bl, [si]     ; Load 1 BCD number from DS:0030H
    add al, bl       ; Add it to the accumulator's low byte
    daa              ; Decimal adjust after addition
    adc dl, 00h      ; Add any carry to the high byte (DL)
    inc si           ; Move to the next BCD number
    loop l1          ; Repeat for all 5 numbers

    mov [di], al     ; Store the lower byte of result in DS:0040H
    inc di           ; Move to the next memory location
    mov [di], dl     ; Store the higher byte (overflow) in DS:0041H

    int 03h          ; Software interrupt for debugging (optional)
    mov ah, 4Ch      ; Terminate program
    int 21h          ; DOS interrupt to return control to the operating system

main endp
end main
