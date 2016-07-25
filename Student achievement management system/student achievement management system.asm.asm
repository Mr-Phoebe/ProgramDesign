data segment

;struct student declaration
student struc
    myname db 10 dup(0)
    class dw 0
    number dw 0
    score dw 0
student ends

	STU student 64 dup(<>) ;max student number is 64
	STU_NUM db 0 ;number of students
	TMP_STR dw 5 dup(0) ;for reading issues
	TEN dw 10
	STR_NAME db 'Please input your name', 0dh, 0ah, '$'
	STR_CLASS db 'Please input your class', 0dh, 0ah, '$'
	STR_NUMBER db 'Please input your number', 0dh, 0ah, '$'
	STR_SCORE db 'Please input your score', 0dh, 0ah, '$'
	STR_SHOWNAME db 'Name: ', 0dh, 0ah, '$'
	STR_SHOWCLASS db 'Class: ', 0dh, 0ah, '$'
	STR_SHOWNUMBER db 'Number: ', 0dh, 0ah, '$'
	STR_SHOWSCORE db 'Score: ', 0dh, 0ah, '$'
	STR_NOSTUDENT db 'No student right now!', 0dh, 0ah, '$'
	STR_AVERAGE db 'The average score is: ', 0dh, 0ah, '$'
	STR_0_60 db 'The number of students below 60 is: $'
	STR_60_70 db 'The number of students between 60 and 70 is: $'
	STR_70_80 db 'The number of students between 70 and 80 is: $'
	STR_80_90 db 'The number of students between 80 and 90 is: $'
	STR_90_100 db 'The number of students above 90 is: $'
	STR_INS db 'Please input the number: ', 0dh, 0ah, '$'
	STR_INS1 db '1. add a student', 0dh, 0ah, '$'
	STR_INS2 db '2. sort by class', 0dh, 0ah, '$'
	STR_INS3 db '3. sort by number', 0dh, 0ah, '$'
	STR_INS4 db '4. sort by score', 0dh, 0ah, '$'
	STR_INS5 db '5. show the average score', 0dh, 0ah, '$'
	STR_INS6 db '6. show the number of students in different interval' , 0dh, 0ah, '$'
	STR_INS7 db '7. exit', 0dh, 0ah, '$'
	STR_ERR db 'Wrong input!$'

data ends

stack segment
    dw   128  dup(0)
stack ends

code segment
    assume cs:code, ds:data, ss:stack 
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    mov ax, stack
    mov ss, ax

Begin:
; output the memu 
	lea dx, STR_INS
	mov ah, 09h
	int 21h
	lea dx, STR_INS1
	mov ah, 09h
	int 21h
	lea dx, STR_INS2
	mov ah, 09h
	int 21h
	lea dx, STR_INS3
	mov ah, 09h
	int 21h
	lea dx, STR_INS4
	mov ah, 09h
	int 21h
	lea dx, STR_INS5
	mov ah, 09h
	int 21h
	lea dx, STR_INS6
	mov ah, 09h
	int 21h
	lea dx, STR_INS7
	mov ah, 09h
	int 21h

	mov ah, 01h
	int 21h
	push ax
	mov ah, 02h
	mov dl, 0ah
	int 21h
	mov dl, 0dh
	int 21h
	pop ax

	sub al, '0'
	cmp al, 1
	je Addstu
	cmp al, 2
	je Sortclass
	cmp al, 3
	je Sortnum
	cmp al, 4
	je Sortscr
	cmp al, 5
	je Avescr
	cmp al, 6
	je Interval
	cmp al, 7
	je OVER
	jmp Err

Addstu:
	call getInfo
	jmp Begin
Sortclass:
	push dx
	mov dx, 1
	call sort
	pop dx
	call printInfo
	jmp Begin
Sortnum:
	push dx
	mov dx, 2
	call sort
	pop dx
	call printInfo
	jmp Begin
Sortscr:
	push dx
	mov dx, 3
	call sort
	pop dx
	call printInfo
	jmp Begin
Avescr:
	call average
	jmp Begin
Interval:
	call count
	jmp Begin
Err:
	lea dx, STR_ERR
	mov ah, 09h
	int 21h
	jmp Begin

OVER:    
    mov ax, 4c00h ; exit to operating system.
    int 21h 
	



;below are functions
	
;getInput function
;Store to TMP_STR and add '$',
getInput proc near
	push ax
	push dx
	lea dx, TMP_STR
	mov di, dx 
	mov si, di
	add si, 2 ;point to first valid character
    mov [di], byte ptr 9 ;max 9 characters   
    mov ah, 0Ah
    int 21h

	push cx ;save cx, cx used for loop
	mov cx, 0
	mov cl, [di + 1] ;the second byte is the length

;ignore the di,di+1
LgetInput1:
	
	mov bl, [si]
	mov [di], bl
	
	inc si
	inc di
	loop LgetInput1

	;then add '$'
	mov [di], byte ptr '$'
	
	;echo
	lea dx, TMP_STR
	mov ah, 09h
	int 21h
	mov dl, 0dh
	mov ah, 02h
	int 21h
	mov dl, 0ah
	int 21h

	pop cx
	pop dx
	pop ax

	ret
getInput endp



;di point to the end of the ary (the one after the last one)
getEnd proc near
	lea di, STU
	push ax
	mov al, 16 ;one student take place 16 bytes
	mul STU_NUM ;result is in ax
	add di, ax ;di point to the destination(the end address of the memory students take place)
	pop ax
ret
getEnd endp


;read the number in TMP_STR, use the function to change into the integer
getNumber proc near
	;point to the end
	call getEnd
	push dx
	lea si, TMP_STR
	mov ax, 0
	mov dx, 0

	push cx
	mov cx, 5 ;max 65536(5 digits)
	push bx
	
LgetNumber1:
	cmp [si], byte ptr '$'
	jz NgetNumber1 ;if meets the end of the class

	mul TEN
	mov bx, [si]
	sub bx, byte ptr '0'
	mov bh, 0
	add ax, bx	
	inc si
	loop LgetNumber1

NgetNumber1:
	pop bx
	pop cx
	pop dx
ret
getNumber endp



;first read string in TMP_STR and returns the true value of the input number stored in ax
getScore proc near
	;point to the end
	call getEnd
	push dx
	lea si, TMP_STR
	mov ax, 0
	mov dx, 0

	push cx
	mov cx, 6 ;max 6553.6(6 digits)
	push bx
	
LgetScore1:
	cmp [si], byte ptr '$'
	jz NgetScore1 ;if mets the end of the class
	cmp [si], byte ptr '.'
	jz Incsi ;if mets '.', ignore

	mul TEN
	mov bx, [si]
	sub bx, byte ptr '0'
	mov bh, 0
	add ax, bx

Incsi:		
	inc si
	loop LgetScore1

NgetScore1:
	pop bx
	pop cx
	pop dx
ret
getScore endp




getInfo proc near
	;first read the name
	lea dx, STR_NAME
	mov ah, 09h
	int 21h

	call getInput
	lea si, TMP_STR
	;di point to the end
	call getEnd
	push cx
	mov cx, 5
LgetInfo1:
	push [si]
	pop [di]
	add si, 2
	add di, 2
	loop LgetInfo1
	pop cx

	;then read the class
	lea dx, STR_CLASS
	mov ah, 09h
	int 21h

	call getInput
	push ax
	call getNumber
	mov [di].class, ax ;get class
	pop ax

	;then read the number
	lea dx, STR_NUMBER
	mov ah, 09h
	int 21h

	call getInput
	push ax
	call getNumber
	mov [di].number, ax ;get number
	pop ax

	;then read the score
	lea dx, STR_SCORE
	mov ah, 09h
	int 21h
	call getInput
	push ax
	call getScore
	mov [di].score, ax ;get score
	pop ax

	inc STU_NUM ;the valid number + 1	
	ret
getInfo endp



;print decimal number.The number is stored in ax
printDecimal proc near
	push ax
	push dx
	push cx
	mov cx, 0 ;store the width of digits
	mov dx, 0

LprintDecimal1:
	div TEN
	push dx ;store the quotient 
	mov dx, 0
	inc cx
	cmp ax, 0
	jz next
	jmp LprintDecimal1

next:
	pop dx; get the remainder
	add dl, '0'
	mov ah, 02h
	int 21h
	loop next

	;print '\n'
	mov dl, 0dh
	mov ah, 02h
	int 21h
	mov dl, 0ah
	int 21h

	pop cx
	pop dx
	pop ax
	ret
printDecimal endp

;print score.The score is stored in ax
printScore proc near
	push ax
	push dx
	push cx
	mov cx, 0 ;store the width of digits
	mov dx, 0

	cmp ax, 10
	jae LprintScore1
	;below score 1.0
	push ax
	push dx
	mov cx, 2
	jmp nextS

LprintScore1:
	div TEN
	push dx ;store the quotient 
	mov dx, 0
	inc cx
	cmp ax, 0
	jz nextS
	jmp LprintScore1

nextS:
	pop dx; get the remainder
	add dl, '0'
	mov ah, 02h
	int 21h

	cmp cx, 2
	jne Loopnext
	mov dl, '.'
	int 21h
Loopnext:
	loop nextS

	;print '\n'
	mov dl, 0dh
	mov ah, 02h
	int 21h
	mov dl, 0ah
	int 21h

	pop cx
	pop dx
	pop ax
	ret
printScore endp



printInfo proc near
	push cx
	mov ch, 0
	mov cl, STU_NUM
	lea si, STU
	push dx
LprintInfo1:
	;print name
	lea dx, STR_SHOWNAME
	mov ah, 09h;
	int 21h
	lea dx, [si].myname
	int 21h
	mov dl, 0dh
	mov ah, 02h
	int 21h
	mov dl, 0ah
	int 21h
	
	;print class
	lea dx, STR_SHOWCLASS
	mov ah, 09h;
	int 21h
	mov ax, [si].class
	call printDecimal

	;print number
	lea dx, STR_SHOWNUMBER
	mov ah, 09h;
	int 21h
	mov ax, [si].number
	call printDecimal

	;print score
	lea dx, STR_SHOWSCORE
	mov ah, 09h;
	int 21h
	mov ax, [si].score
	call printScore

	add si, 16 ;point to next
	loop LprintInfo1
	pop dx
	pop cx

	ret
printInfo endp



;method stored in dl, for class: 01h, for number: 02h, for score: 03h
;when call sort, first push dx and after call sort, pop dx
sort proc near
	;one student return
	cmp STU_NUM, 1
	ja Ssort
	ret

Ssort:
	push ax
	push bx
	;outside loop for STU_NUM - 1 times
	mov ah, 0
	mov al, STU_NUM
	sub ax, 2 ;point to the last two student
Loutside:
	mov bx, 0 ;first point to the first student
	;inside loop
Linside:
	;let si point to a[j] and di point to a[j + 1]
	lea si, STU
	push ax
	mov ax, 16;
	mul bl
	add si, ax
	mov di, si
	add di, 16
	pop ax
	
	cmp dl, 1
	je Cclass
	cmp dl, 2
	je Cnumber
	cmp dl, 3
	je Cscore

Cclass:
	push ax
	push bx
	mov ax, [si].class
	mov bx, [di].class
	cmp ax, bx
	pop bx
	pop ax
	ja Swap
	jmp Endinside

Cnumber:
	push ax
	push bx
	mov ax, [si].number
	mov bx, [di].number
	cmp ax, bx
	pop bx
	pop ax
	ja Swap
	jmp Endinside

Cscore:
	push ax
	push bx
	mov ax, [si].score
	mov bx, [di].score
	cmp ax, bx
	pop bx
	pop ax
	ja Swap
	jmp Endinside


Swap:
	push cx
	push dx
	push ax
	mov cx, 8
Lswap:
	;first store di to ax
	mov ax, [di]

	mov dx, [si]
	mov [di], dx

	mov [si], ax

	add si, 2
	add di, 2
	loop Lswap
	pop ax
	pop dx
	pop cx


Endinside:
	inc bx
	cmp bx, ax
	ja Routside
	jmp Linside
Routside:
	dec ax
	cmp ax, 0
	jl Esort ;-1 exit
	jmp Loutside

Esort:
	pop bx
	pop ax
	ret
sort endp



average proc near
	;if there is no student
	cmp STU_NUM, 0
	jnz Nextaverage
	push dx
	push ax
	lea dx, STR_NOSTUDENT
	mov ah, 09h
	int 21h
	pop ax
	pop dx
	ret
	
Nextaverage:
	push cx
	push ax
	mov ax, 0
	mov ch, 0
	mov cl, STU_NUM
	lea si, STU
Laverage1:
	add ax, [si].score
	add si, 16
	loop Laverage1
	push dx
	push bx
	mov dx, 0
	mov bx, 0
	mov bl, STU_NUM
	div bx
	pop bx
	pop dx
	
	

	push dx
	push ax
	lea dx, STR_AVERAGE
	mov ah, 09h
	int 21h
	pop ax
	pop dx
	call printScore

	pop ax
	pop cx
	ret
average endp


;al [0,60),bh [60,70), bl [70, 80), ch [80,90), cl [90, 100]
count proc near
	push ax
	push bx
	push dx
	push cx
	mov ax, 0
	mov bx, 0
	mov dx, 0
	mov ch, 0
	mov cl, STU_NUM
	lea si, STU

Lcount1:
	cmp [si].score, 600
	jb SPAN_0_59
	cmp [si].score, 700
	jb SPAN_60_70
	cmp [si].score, 800
	jb span_70_80
	cmp [si].score, 900
	jb span_80_90
	;greater or equal to 90
	inc dh
	jmp Cmpover
SPAN_0_59:
	inc ah
	jmp Cmpover
SPAN_60_70:
	inc al
	jmp Cmpover
span_70_80:
	inc bh
	jmp Cmpover
span_80_90:
	inc bl
Cmpover:
	add si, 16
	loop Lcount1
	
	;map
	mov cl, dh
	mov ch, bl
	mov bl, bh
	mov bh, al
	mov al, ah
	
	;print 0~59
	lea dx, STR_0_60
	mov ah, 09h
	int 21h
	mov ah, 0
	call printDecimal
	;print 60~69
	lea dx, STR_60_70
	mov ah, 09h
	int 21h
	mov ah, 0
	mov al, bh
	call printDecimal
	;print 70~79
	lea dx, STR_70_80
	mov ah, 09h
	int 21h
	mov ah, 0
	mov al, bl
	call printDecimal
	;print 80~89
	lea dx, STR_80_90
	mov ah, 09h
	int 21h
	mov ah, 0
	mov al, ch
	call printDecimal
	;print 90~100
	lea dx, STR_90_100
	mov ah, 09h
	int 21h
	mov ah, 0
	mov al, cl
	call printDecimal
	
	pop cx
	pop dx
	pop bx
	pop ax
	ret
count endp
   

code ends
end start
