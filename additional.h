#include <stdlib.h>

void *TCG_malloc(size_t size);
void *TCG_realloc(void *ptr, size_t size);

extern unsigned int temp_buf_offset;
extern unsigned int tlb_table_n_0_addr_read[7];
extern unsigned int tlb_table_n_0_addr_write[7];
extern unsigned int tlb_table_n_0_addend[7];
extern unsigned int tlb_table_n_0[7];
extern unsigned int tlb_entry_addr_read;
extern unsigned int tlb_entry_addr_write;
extern unsigned int tlb_entry_addend;
extern unsigned int sizeof_CPUTLBEntry;
