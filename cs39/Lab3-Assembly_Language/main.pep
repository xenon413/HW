;lab3

         STRO    promptA,d
         DECI    valueA,d

         STRO    promptB,d
         DECI    valueB,d

         STRO    promptC,d
         DECI    valueC,d
         
         LDWA    valueB,d
         ANDA    valueC,d
         STWA    temp,d

         LDWA    valueA,d
         ORA     temp,d
         STWA    result,d

         DECO    result,d
         STOP

valueA:  .WORD   0
promptA: .ASCII  "Enter A\n" 

valueB:  .WORD   0
promptB: .ASCII  "Enter B\n" 

valueC:  .WORD   0
promptC: .ASCII  "Enter C\n" 

result:  .WORD   0
temp:    .WORD   0

         .END         
