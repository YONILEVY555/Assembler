.define size=2
.extern z,yoni,t
.entry x,y,part7,part8,part50
part1: mov r5,r3
part2: mov #5,r3
part3: mov x,r3
part4: mov r3,x
part5: mov x[1],x[size]
part6: mov size,x[1]
part7: mov z,r3
part8: mov r3,yoni
part9: mov x[1],t[size]
part10: mov size,z[1]
part11: cmp #5,#5
part12: cmp r3,r7
part13: cmp #5,r3
part14: cmp x,size
part15: cmp x[1],x[size]
part16: add r5,r3
part17: add #5,r3
part18: add x,r3
part19: add r3,x
part21: add x[1],x[size]
part22: add size,x[1]
part23: sub r5,r3
part24: sub #5,r3
part25: sub x,r3
part26: sub r3,x
part27: sub x[1],x[size]
part28: sub size,x[1]
part29: not r4
part30: not x
part31: not x[2]
part32: clr r4
part33: clr x
part34: clr x[2]
part35: inc r4
part36: inc x
part37: inc x[2]
part38: dec r4
part39: dec x
part40: dec x[2]
part41: jmp x
part42: jmp r1
part43: bne x
part44: bne r1
part45: red r4
part46: red x
part47: red x[2]
part48: prn r4
part49: prn x
part50: prn x[2]
part51: prn #5
part52: jsr x
part53: jsr r1
part54: lea x,r3
part55: lea x,x
part56: lea x,x[2]
part57: lea x[1],x
part58: lea x[1],r3
part59: lea x[1],x[1]
part60: rts
part61: stop
x: .data 9,9,size,9,9
y: .string "hfghfgdhgg"
