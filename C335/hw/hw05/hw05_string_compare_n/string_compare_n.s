	.text
	.syntax unified
	.thumb
	.global	string_compare_n
	.type string_compare_n, %function
string_compare_n:
	sub     sp, sp, #16
	str     x0, [sp, 8]
	str     x1, [sp]
