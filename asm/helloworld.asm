;
; \author Jxtopher
; \version 1
; \date 2019-05
; \brief Hello world for a simple exemple code
;
; @compilation *
; @execution *
;

 section .data
        helloMsg:     db 'Hello world!',10 
        helloSize:    equ $-helloMsg
 section .text
        global _start
 _start:
        mov eax,4             ; Appel système "write" (sys_write)
        mov ebx,1             ; File descriptor, 1 pour STDOUT (sortie standard)
        mov ecx, helloMsg     ; Adresse de la chaîne a afficher
        mov edx, helloSize    ; Taille de la chaîne
        int 80h               ; Execution de l'appel système
   
                              ; Sortie du programme
        mov eax,1             ; Appel système "exit"
        mov ebx,0             ; Code de retour
        int 80h               ; Execution de l'appel système
