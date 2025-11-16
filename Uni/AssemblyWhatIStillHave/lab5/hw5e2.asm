
; declaration of extern variables or functions

; global public variables defined in this file

; constants definition and INCLUDE instructions

; macro definitions

; data section
DATA SEGMENT PARA PUBLIC 'DATA'

   ; REZ_1 DW 0

    ; define your data here
DATA ENDS

; code section
CODE SEGMENT PARA PUBLIC 'CODE'
START   PROC FAR ; start main procedure
    ASSUME CS:CODE, DS:DATA

    ; instructions to allow the return to OS or
    ; other program
    PUSH DS
    XOR AX, AX
    PUSH AX

    ; initialize DS with the start of the data segment
    MOV AX, DATA
    MOV DS, AX

    MOV AX,267
    MOV BX,572

    MOV DX,AX
    SHL AX,3
    SUB AX,DX
    MOV DX,AX

    MOV CX,BX
    SHL CX,1

    SHR BX,3

    SUB DX,CX
    SUB DX,BX

    RET ; return to OS or other program
START ENDP ; end main procedure

; other procedures (i.e. functions)

CODE ENDS

END START ; end the file