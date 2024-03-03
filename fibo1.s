step: not r0 r1 
      add r0 r0 r0
      not r0 r0 ; r0 = 1
      add r3 r1 r1 ; r3 = 0
      and r3 r0 r0 ; r3 = 1
loop: add r3 r1 r0 ; loops till end
      and r1 r0 r0
      and r0 r3 r3
      bnz loop