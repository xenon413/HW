         LDWA    0x0000,i    
         STWA    index,d 
         STWA    total,d 
    
forloop: LDWA    index,d     
         CPWA    10,i        
         BREQ    isdone      

         LDWX    index,d     
         ASLX                ; x2 to index WORD

         ; input a value into values[index]
         DECI    values,x

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
              
index:   .WORD   0           
values:  .BLOCK  20  
total:   .WORD   0        

         .END                  
