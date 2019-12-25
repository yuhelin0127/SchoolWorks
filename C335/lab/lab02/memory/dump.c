//
// dump.c
//
 
void dump_memory(void *p, int len)
{
  int i;
  printf("address    char hexCh  short   integer       float       doubleFloat\n");
  for (i = 0; i < len; i++) {
//    printf("%8p: %c   0X%02x  +%d +%d +%e +%e\n", p + i, *(unsigned char *)(p + i), *(unsigned char *)(p + i), *(unsigned short *)(p + i), *(unsigned int *)(p + i), *(float *)(p + i), *(double *)(p + i));
	printf("%8p ", p + i);
	if(*(unsigned char *)(p + i) >= 32 && *(unsigned char *)(p + i) <= 127){
			printf("%c ", *(unsigned char *)(p + i));
	}
	else{
			printf("?  ");
	}
	printf("0X%02x ", *(unsigned char *)(p + i));
	if(i % 2 == 0){
		printf("+%d ", *(unsigned short *)(p + i));
	}
	if(i % 4 == 0){
		printf("+%d ", *(unsigned int *)(p + i));
	}
	if(i % 4 == 0){
		printf("+%e ", *(float *)(p + i));
	}
	if(i % 8 == 0){
		printf("+%e\n", *(double *)(p + i));
	}
	else{
		printf("\n");
	}
  }
}
