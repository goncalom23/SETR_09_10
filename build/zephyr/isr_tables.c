
/* AUTO-GENERATED by gen_isr_tables.py, do not edit! */

#include <toolchain.h>
#include <linker/sections.h>
#include <sw_isr_table.h>
#include <arch/cpu.h>

#if defined(CONFIG_GEN_SW_ISR_TABLE) && defined(CONFIG_GEN_IRQ_VECTOR_TABLE)
#define ISR_WRAPPER ((uintptr_t)&_isr_wrapper)
#else
#define ISR_WRAPPER NULL
#endif

typedef void (* ISR)(const void *);
uintptr_t __irq_vector_table _irq_vector_table[48] = {
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
	ISR_WRAPPER,
};
struct _isr_table_entry __sw_isr_table _sw_isr_table[48] = {
	{(const void *)0x2f31, (ISR)0x5467},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x598c, (ISR)0x51c7},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x34ad, (ISR)0x5467},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)0x29e9},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x5974, (ISR)0x51c7},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
	{(const void *)0x0, (ISR)&z_irq_spurious},
};
