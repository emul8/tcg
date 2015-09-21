/*
 * Copyright (c) 2010-2015 Antmicro Ltd <www.antmicro.com>
 * Copyright (c) 2011-2015 Realtime Embedded AB <www.rte.se>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>
#include <string.h>
#include "tcg.h"

uint16_t *gen_opc_buf;
TCGArg *gen_opparam_buf;
uint8_t *code_gen_prologue __attribute__((aligned (32)));

TCGContext *tcg_ctx;

void *qemu_ld_helpers[4] = {
 NULL, NULL, NULL, NULL
};

void *qemu_st_helpers[4] = {
 NULL, NULL, NULL, NULL
};

void attach_gen_opc_buf(void *buf) {
	gen_opc_buf = buf;
}

void attach_tcg_ctx(void *tcg_c) {
	tcg_ctx = tcg_c;
}

void attach_code_gen_prologue(void *prol) {
	code_gen_prologue = prol;
}

void attach_gen_opparam_buf(void *buf) {
	gen_opparam_buf = buf;
}

void attach_ld_helpers(void *__ldb, void *__ldw, void *__ldl, void *__ldq) {
	qemu_ld_helpers[0] = __ldb;
	qemu_ld_helpers[1] = __ldw;
	qemu_ld_helpers[2] = __ldl;
	qemu_ld_helpers[3] = __ldq;
}

void attach_st_helpers(void *__stb, void *__stw, void *__stl, void *__stq) {
	qemu_st_helpers[0] = __stb;
	qemu_st_helpers[1] = __stw;
	qemu_st_helpers[2] = __stl;
	qemu_st_helpers[3] = __stq;
}

void *(*_TCG_malloc)(size_t);

void attach_malloc(void *malloc_callback) {
        _TCG_malloc = malloc_callback;
}

void *TCG_malloc(size_t size) {
	return _TCG_malloc(size);
}

void *(*_TCG_realloc)(void *, size_t);

void attach_realloc(void * reall) {
    _TCG_realloc = reall;
}

void *TCG_realloc(void *ptr, size_t size) {
    return _TCG_realloc(ptr, size);
}

void TCG_pstrcpy(char *buf, int buf_size, const char *str)
{
    int c;
    char *q = buf;

    if (buf_size <= 0)
        return;

    for(;;) {
        c = *str++;
        if (c == 0 || q >= buf + buf_size - 1)
            break;
        *q++ = c;
    }
    *q = '\0';
}

char *TCG_pstrcat(char *buf, int buf_size, const char *s)
{
    int len;
    len = strlen(buf);
    if (len < buf_size)
        TCG_pstrcpy(buf + len, buf_size - len, s);
    return buf;
}

unsigned int temp_buf_offset;
unsigned int tlb_table_n_0[7];
unsigned int tlb_table_n_0_addr_read[7];
unsigned int tlb_table_n_0_addr_write[7];
unsigned int tlb_table_n_0_addend[7];
unsigned int tlb_entry_addr_read;
unsigned int tlb_entry_addr_write;
unsigned int tlb_entry_addend;
unsigned int sizeof_CPUTLBEntry;
int TARGET_PAGE_BITS;

void set_TARGET_PAGE_BITS(int val) {
    TARGET_PAGE_BITS = val;
}

void set_sizeof_CPUTLBEntry(unsigned int sz) {
        sizeof_CPUTLBEntry = sz;
}

void set_temp_buf_offset(unsigned int offset) {
        temp_buf_offset = offset;
}

void set_tlb_entry_addr_rwu(unsigned int read, unsigned int write, unsigned int addend) {
        tlb_entry_addr_read = read;
        tlb_entry_addr_write = write;
        tlb_entry_addend = addend;
}

void set_tlb_table_n_0(int i, unsigned int offset) {
        tlb_table_n_0[i] = offset;
}

void set_tlb_table_n_0_rwa(int i, unsigned int read, unsigned int write, unsigned int addend) {
        tlb_table_n_0_addr_read[i] = read;
        tlb_table_n_0_addr_write[i] = write;
        tlb_table_n_0_addend[i] = addend;
}

