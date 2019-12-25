	.text
	.syntax unified
	.thumb
	.global	member_array
	.type member_array, %function
member_array:
	push {r4-r7}
	movs r3, #0
LP1:
	ldr r4,[r0, r3]
	cmp r4, r1
	beq T
        adds r3, #4
	subs r2, #1
	cmp r2, #0
	bne LP1
	movs r0, #0
	b END
T:
	movs r0, #1
        b END
	
END:	
	pop {r4-r7}
	bx	lr
	
