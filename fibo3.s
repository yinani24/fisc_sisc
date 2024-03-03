step: not r0 r1
      add r0 r0 r0
      not r0 r0
      add r3 r1 r1
      and r3 r0 r0
      not r2 r2
loop: add r3 r1 r0
      and r1 r0 r0
      and r0 r3 r3
      add r2 r2 r2
      bnz loop
firs: not r2 r2
      add r2 r2 r2
      add r2 r2 r2
      add r2 r2 r2
      add r2 r2 r2
      add r2 r2 r2
      add r2 r2 r2
seco: add r3 r1 r0
      and r1 r0 r0
      and r0 r3 r3
      add r2 r2 r2
      bnz seco

 