	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	movs r2, #0
	movs r4, #1
LP1:
	movs r3, r0
	ands r3, r3, r4
	bne LP2
	mov r3, r1
	ands r3, r3, r4
	bne LP2
	lsrs r0, r0, #1
	lsrs r1, r1, #1
	adds r2, r2, #1
	b LP1
LP2:
	cmp r0, r1
	beq DONE
CASE1:
	mov r3, r0
	ands r3, r3, r4
	bne CASE2
	lsrs r0, r0, #1
	b LP2
CASE2:
	mov r3, r1
	ands r3, r3, r4
	bne CASE3
	lsrs r1, r1, #1
	b LP2
CASE3:
	cmp r0, r1
	bcc DEFAULT
	beq DEFAULT
	subs r0, r0, r1
	lsrs r0, r0, #1
	b LP2
DEFAULT:
	subs r1, r1, r0
	lsrs r1, r1, #1
	b LP2
DONE:
	lsls r0, r0, r2
	pop {r4-r7}
	bx	lr
	
