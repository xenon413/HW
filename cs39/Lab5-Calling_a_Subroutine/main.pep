         LDWA    0x0000,i    
         STWA    index,d 
         STWA    total,d 

         CALL load
         
forloop: LDWA    index,d     
         CPWA    10,i        
         BREQ    isdone      

         LDWX    index,d     
         ASLX                ; x2 to index WORD

         ; add the values[index] to totals
         LDWA    total,d 
         ADDA    values,x
         STWA    total,d 

         LDWX    index,d     
         ADDX    0x0001,i    
         STWX    index,d     
         BR      forloop     
         
isdone:  DECO total,d
         ; output the contents of the total variable
         
         STOP  

;load subroutine             
load:    SUBSP   2,i
         LDWA    0x00,i
         STWA    0,s

loadloop:LDWA    0,s   
         CPWA    10,i        
         BREQ    loaddone      

         LDWX    0,s     
         ASLX                ; x2 to index WORD

         ; input a value into values[index]
         DECI    values,x

         LDWX    0,s    
         ADDX    0x0001,i    
         STWX    0,s    
         BR      loadloop


loaddone:ADDSP   2,i
         RET

index:   .WORD   0           
values:  .BLOCK  20  
total:   .WORD   0        

         .END                  
