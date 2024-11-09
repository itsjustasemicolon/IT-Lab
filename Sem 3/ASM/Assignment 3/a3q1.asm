.model small
.stack 100h
.data
.code
main proc
	mov ax, @data
	mov ds, ax
	mov si, 0030h

	mov al, 0ffh
	mov cx, 0007h

l1:
	cmp al, [si]
	jc l2
	mov al, [si]

l2:
	inc si
	loop l1

mov si, 0040h
mov [si], al

int 03h

main endp 
end main
	
