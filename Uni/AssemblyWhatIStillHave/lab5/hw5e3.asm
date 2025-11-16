COMMENT * identification information for the program, 
author, program's function, utilization *

; declaration of extern variables or functions

; global public variables defined in this file

; constants definition and INCLUDE instructions

; macro definitions

; data section
DATA SEGMENT PARA PUBLIC 'DATA'

    NUM1 DB 10
    NUM2 DB 20
    AREZ DW 0
    B DW 0
    C DB 0
    DREZ DW 0
    EREZ DW 0
    F DB 0
    REZ DW 0
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

    MOV AX,12ABH
    MOV BX,0CD34H

    MUL NUM1
    MOV AREZ,AX

    MOV AX,12ABH
    MUL NUM2
    MOV C,BL
    ADD AX,WORD PTR C
    MOV DREZ,AX

    MOV AX,12ABH
    SUB BL,AH
    MOV F,BL
    MOV DX,WORD PTR F
    MOV EREZ,DX

    MOV AX,DREZ
    ADD DX,AX
    MOV AX,AREZ
    ADD DX,AX
    MOV REZ,DX

    RET ; return to OS or other program
START ENDP ; end main procedure

; other procedures (i.e. functions)

CODE ENDS

END START ; end the file