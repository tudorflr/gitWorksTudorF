DATA SEGMENT PARA PUBLIC 'DATA'
    ATTR_NORMAL         DW  0000H
    IN_FILE             DB  'in.txt',0
    ADR_IN_FILE         DW  IN_FILE_NAME
    OUT_FILE            DB  'out.txt',0
    ADR_OUT_FILE        DW  OUT_FILE_NAME
    ATTR_RO             DW  0001H
    HANDLE1             DW  ?
    HANDLE2             DW  ?
    buffer              DB  255 DUP (?) 

DATA ENDS

; Macro declaration zone

; End of macro declaration zone

CODE SEGMENT PARA PUBLIC 'CODE'
ASSUME CS:CODE, DS:DATA
START PROC FAR
PUSH DS
XOR AX, AX
MOV DS, AX
PUSH AX
MOV AX, DATA
MOV DS, AX
; your code starts here

    CALL OPEN_FILE  ;   for the input file
    MOV HANDLE1, AX  ;   save file handle

    CALL CREATE_OPEN_FILE   ;for the output file (includes creation)
    MOV HANDLE2, AX  ;   save file handle
    
    CALL READ_INFO
    MOV AH, buffer + 2 ; the symbol should be there
; your code ends here
RET
START ENDP

; Near procedures declaration zone
OPEN_FILE PROC NEAR 

    MOV AH , 3DH
    MOV AL, 0
    MOV DX, ADR_IN_FILE
    INT 21H

    RET

OPEN_FILE ENDP

CREATE_OPEN_FILE PROC NEAR 
    ;create file
    MOV AH , 3CH
    XOR CX, CX 
    OR CX, ATTR_NORMAL
    MOV DX, ADR_OUT_FILE
    INT 21H

    RET
CREATE_OPEN_FILE ENDP

READ_INFO PROC NEAR

    ;read size
    MOV AH , 3FH
    MOV BX, HANDLE1 ;file handle
    MOV CX, 2 ;nr of bytes to read
    MOV DX, OFFSET buffer
    INT 21H

    ;read letter
    MOV AH , 3FH
    MOV BX, HANDLE1
    MOV CX, 1
    MOV DX, OFFSET buffer 
    INT 21H

    ;read symbol to replace with
    MOV AH, 3FH
    MOV BX, HANDLE1
    MOV CX, 1
    MOV DX, OFFSET buffer + 2
    INT 21H
    

    RET
READ_INFO ENDP

ABOUT_TEXT PROC NEAR

    ;read the text with a loop
    MOV AH, 3FH
    MOV BX, HANDLE1
    MOV DX, OFFSET buffer
    INT 21H

    MOV SI, OFFSET buffer ; points to where buffer starts

    read:
    MOV AL, [SI] ; remember the value
    INC SI ; increment SI to point to the next elem
    CMP AL, 0 ;if we're at the end
    JE endRead

    CMP AL, 'a' 
    JNE writeChar ; if it's not that elem then write it the same
    MOV AL, AH

    writeChar: 
        MOV AH, 40H
        MOV BX, HANDLE2
        MOV DX, OFFSET buffer
        INT 21H
        JMP read ; go on to read the next char
    
    endRead: 
    RET
    
ABOUT_TEXT ENDP
; End of near procedures declaration zone

CODE ENDS
END START