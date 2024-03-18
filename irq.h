#ifndef R01LIB_IRQ_H
#define	R01LIB_IRQ_H

void GPIO0_IRQHandler( void );
void GPIO1_IRQHandler( void );
void GPIO2_IRQHandler( void );
void GPIO3_IRQHandler( void );

void irq_handler( int num );

#endif // R01LIB_IRQ_H
