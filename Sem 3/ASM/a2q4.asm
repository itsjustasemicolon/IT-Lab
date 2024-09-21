dosseg
.model small
.stack 100h
.data
.code

main proc
    mov ax, @data
    mov ds, ax
    mov es, ax
    
    ; Load the string start and end addresses
    mov si, 0030h  ; Start of the string
    mov di, 0034h  ; End of the string (0030h + 4 bytes = 0034h for 5-byte string)

    ; Calculate number of comparisons (5 / 2) and store in CX
    mov ax, 0005h  ; Load 5 into AX
    mov bl, 2      ; Divisor = 2 (to divide by)
    div bl         ; AX = AX / BL, quotient in AL, remainder in AH
    mov cx, ax     ; Store quotient (number of comparisons) in CX

    cld            ; Clear direction flag to increment SI/DI

check_palindrome:
    mov al, [si]   ; Load the current byte from start of the string
    mov ah, [di]   ; Load the current byte from end of the string
    cmp al, ah     ; Compare the bytes
    jnz not_palindrome  ; If they don't match, it's not a palindrome
    
    inc si         ; Move SI to the next byte from the start
    dec di         ; Move DI to the previous byte from the end
    loop check_palindrome  ; Repeat until cx comparisons are done

palindrome:
    mov ax, 0ffffh ; If palindrome, store 0FFFFh
    jmp done

not_palindrome:
    mov ax, 1111h  ; If not palindrome, store 1111h

done:
    mov bx, 0050h  ; Store the result at address 0050h
    mov [bx], ax
    int 03h        ; Debug interrupt
    mov ah, 4ch
    int 21h

main endp
end main
