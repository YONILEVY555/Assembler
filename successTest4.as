.define size=2
mov r5,r3
mov #5,r3
mov x,r3
mov r3,x
mov x[1],x[size]
			mov size,x[1]
cmp #5,#5
cmp r3,r7
cmp #5,r3
			cmp x,size
cmp x[1],x[size]
add r5,r3
add #5,r3
add x,r3
			add r3,x
add x[1],x[		size		]
add size,x[		1		]
sub r5,r3
sub #5,r3
sub x,r3
sub r3,x
sub x[1],x[	size	]
			sub size,x[1]
not r4
not x
		not x[	2	]
clr r4


clr x
clr x[2]
		inc r4
inc x
inc x[2]
dec            r4
dec x
dec x[2]


		jmp x
jmp r1
bne x
bne r1
red r4
red x
red x[2]
prn r4
prn x
prn x[2]
prn #5
jsr x
jsr r1
lea x,r3
lea x,x
lea x,x[2]
lea x[1],x
lea x[1],r3
lea x[1],x[1]
rts
stop
x: .data 9,9,size,9,9
y: .string "hfghfgdhgg"
