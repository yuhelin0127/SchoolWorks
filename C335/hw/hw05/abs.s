	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
/*
	Your implementation goes here. 
*/
	asrs r1, r0, #31
	adds r0, r0, r1
	eors r0, r0, r1
	pop {r4-r7}	
	bx	lr
