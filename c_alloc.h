
#undef malloc 
#define malloc(x)   o_virtualalloc(0, x, 0x00001000 | 0x00002000, 0x04)

#undef free
#define free(x)     o_virtualfree(x, 0, 0x00008000)