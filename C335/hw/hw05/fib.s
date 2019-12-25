	.text
	.syntax unified
	.thumb
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	movs r1, #1
	movs r2, #1
	movs r3, #1
	movs r4, #0
	cmp r0, #0
	beq END
	cmp r0, #1
	beq END
LP:
	subs r5, r0, #2
	cmp r4, r5
	bcs RETURN
	adds r3, r1, r2
	movs r2, r1
	movs r1, r3
	adds r4, r4, #1
	b LP
RETURN:
	movs r0, r3
END:
	pop {r4-r7}
	bx	lr		
