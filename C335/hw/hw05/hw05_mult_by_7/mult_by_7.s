	.text
	.syntax unified
	.thumb
	.global	mult_by_7
	.type mult_by_7, %function
mult_by_7:
	push {r4-r7}
	movs r1, r0
	lsls r0, #3
	subs r0, r1
	.END:
	pop {r4-r7}
	bx	lr
