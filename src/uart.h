#pragma once

void uart_init();
void uart_send(unsigned int c);
char uart_getc();
char uart_getc_no_block();
void uart_puts(char *s);
void uart_hex(unsigned int d);
void printf(char *fmt, ...);
