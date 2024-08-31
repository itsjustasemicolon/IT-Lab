dosseg
.model small
.stack 100h
.data
.code

main proc
mov ax,@data
mov ds,ax
mov si,0030h
mov di,0050h
mov cx,0005h
mov ax,0000h
mov bx,0000h
mov dl,00h

l1:    mov bx,[si]
	add ax,bx
	adc dl,00h
	inc si
	inc si
	loop l1
mov [di],ax
inc di
inc di
mov [di],dl

int 03h
mov ah,4ch
int 21h
main endp
end main
