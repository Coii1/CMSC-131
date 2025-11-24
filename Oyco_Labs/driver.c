#include "cdecl.h"

int PRE_CDECL asm_main( void ) POST_CDECL;
//extern int _asm_main(void);

int main()
{
  int ret_status;
  ret_status = asm_main();
  return ret_status;
}
