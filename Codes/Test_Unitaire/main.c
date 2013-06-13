/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include<stdio.h>
#include<stdlib.h>
#include<MonSTM8.h>
#include<assert.h>

#define SIZE 16

main()
{ 
	char *buff = NULL;
	char c;
	uint32_t addr = FLASH_ADDR_MIN;
	
	GLED_init();
	FLASH_init();
	Serial_init(RW);
	Serial_enableRI(1);
	
	Serial_Putstring("Hello World !!\r\n");
	
	
	buff = malloc( SIZE * sizeof (char) );
	if ( buff == 0 ) {
		Serial_Putstring("\r\n              GAME OVER !! \r\n");
		assert(0);
	}
	
	buff[ addr - FLASH_ADDR_MIN ] = '\0';
	
	while (1) {
		if ( Serial_RXNE() ) {
			/* fait clignoter la LED verte */
			GLED_enable( ! GLED_stat() );
			c = Serial_Getchar();
			
			if ( c == 'r' ) {
				FLASH_read(addr, buff, 11);
				Serial_Putstring( buff );
			}
			else if ( c == 'w' ) {
				FLASH_write(addr, "0123456789", 11);
			}
		}
	}
}


