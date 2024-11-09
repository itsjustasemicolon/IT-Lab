.model small
.stack 100h
.data
.code
main proc
    mov ax, @data
    mov ds, ax

    mov cx, 5            
outer_loop:
    mov si, 0030h      
    mov bx, cx          
    
inner_loop:
    mov al, [si]         
    cmp al, [si+1]       
    jnc no_swap         
    
    mov dl, [si+1]       
    mov [si+1], al      
    mov [si], dl         

no_swap:
    inc si              
    dec bx              
    jnz inner_loop    

    dec cx             
    jnz outer_loop      

    int 03h             
    mov ah, 4ch
    int 21h
main endp
end main
