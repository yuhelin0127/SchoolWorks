/* H4
 * C335 / Fall 2019
 * Yuheng Lin
 * 11/13/2019
 */
 
 #include <stdio.h>
 
#define rm(x) (((x)>>3)&7)
#define rn(x) (((x)>>3)&7)
#define op(x) (((x)>>6)&15)
#define rd(x) ((x)&7)
#define rdn(x) ((x)&7)
#define rmc(x) (((x)>>6)&7)
#define opc(x) (((x)>>9)&1)
#define dn(x) ((x)&7)

const char* regnames[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "sp", "lr", "pc"};
// data-processing opcode
const char* opname[] = {"ands", "eors", "lsls", "lsrs", "asrs", "adcs", "sbcs", "rors", "tsts", "rsbs", "cmps", "cmns", "orrs", "muls", "bics", "mvns"};
// add and subtract opcode
const char* opname_as[] = {"adds", "subs"};

void assembly(int word, int mode){
  switch (mode) {
  case 0: 
    printf("\t%s %s,%s,%s\n", opname[opc(word)], regnames[rd(word)], regnames[rm(word)], rmc(word));
    break;
  case 6: 
    printf("\t%s %s,%s,%s\n", opname_as[opc(word)], regnames[rd(word)], regnames[rn(word)], regnames[rmc(word)]);
    break;
  case 7: 
    printf("\t%s %s,%s,%s\n", opname_as[opc(word)], regnames[rd(word)], regnames[rn(word)], rmc(word));
    break;
  case 1: 
    printf("\t%s %s,%s\n", opname[opc(word)], rmc(word), regnames[rdn(word)]);
	break;
  case 16: 
    printf("\t%s %s,%s\n", opname[op(word)], regnames[rdn(word)], regnames[rm(word)]);
    break;
  case 17: 
    printf("\t%s %s,%s,%s\n", opname[opc(word)], regnames[rdn(word)], regnames[rm(word)], regnames[dn(word)]);
    break;
  }
}

int main(){
  int word, mode;
  printf(".text\n.syntax unified\n.thumb\n");
  while (scanf("%x", &word) == 1){
    mode = word >> 10;
    assembly(word, mode);
  }
  return 0;
}
