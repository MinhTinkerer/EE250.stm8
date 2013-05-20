   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  74                     .const:	section	.text
  75  0000               L6:
  76  0000 00004000      	dc.l	16384
  77                     ; 17 void FLASH_Putstring(u32 addr, char* s) {
  78                     	scross	off
  79                     	switch	.text
  80  0000               _FLASH_Putstring:
  82  0000 5204          	subw	sp,#4
  83       00000004      OFST:	set	4
  86                     ; 18 	u32 i = 0;
  88  0002 ae0000        	ldw	x,#0
  89  0005 1f03          	ldw	(OFST-1,sp),x
  90  0007 ae0000        	ldw	x,#0
  91  000a 1f01          	ldw	(OFST-3,sp),x
  93  000c 2028          	jra	L34
  94  000e               L73:
  95                     ; 20 		FLASH_ProgramByte(ADDRESS_CHAINE+i, s[i]);
  97  000e 1e0b          	ldw	x,(OFST+7,sp)
  98  0010 72fb03        	addw	x,(OFST-1,sp)
  99  0013 f6            	ld	a,(x)
 100  0014 88            	push	a
 101  0015 96            	ldw	x,sp
 102  0016 1c0002        	addw	x,#OFST-2
 103  0019 cd0000        	call	c_ltor
 105  001c ae0000        	ldw	x,#L6
 106  001f cd0000        	call	c_ladd
 108  0022 be02          	ldw	x,c_lreg+2
 109  0024 89            	pushw	x
 110  0025 be00          	ldw	x,c_lreg
 111  0027 89            	pushw	x
 112  0028 cd0000        	call	_FLASH_ProgramByte
 114  002b 5b05          	addw	sp,#5
 115                     ; 21 		i++;
 117  002d 96            	ldw	x,sp
 118  002e 1c0001        	addw	x,#OFST-3
 119  0031 a601          	ld	a,#1
 120  0033 cd0000        	call	c_lgadc
 122  0036               L34:
 123                     ; 19 	while(s[i]) {
 125  0036 1e0b          	ldw	x,(OFST+7,sp)
 126  0038 72fb03        	addw	x,(OFST-1,sp)
 127  003b 7d            	tnz	(x)
 128  003c 26d0          	jrne	L73
 129                     ; 23 	FLASH_ProgramByte(ADDRESS_CHAINE+i, '\0');
 131  003e 4b00          	push	#0
 132  0040 96            	ldw	x,sp
 133  0041 1c0002        	addw	x,#OFST-2
 134  0044 cd0000        	call	c_ltor
 136  0047 ae0000        	ldw	x,#L6
 137  004a cd0000        	call	c_ladd
 139  004d be02          	ldw	x,c_lreg+2
 140  004f 89            	pushw	x
 141  0050 be00          	ldw	x,c_lreg
 142  0052 89            	pushw	x
 143  0053 cd0000        	call	_FLASH_ProgramByte
 145  0056 5b05          	addw	sp,#5
 146                     ; 24 }
 149  0058 5b04          	addw	sp,#4
 150  005a 81            	ret
 205                     ; 26 char* FLASH_Readstring(u32 addr, char* buffer) {
 206                     	switch	.text
 207  005b               _FLASH_Readstring:
 209  005b 88            	push	a
 210       00000001      OFST:	set	1
 213                     ; 27 	char i = 0;
 215  005c 0f01          	clr	(OFST+0,sp)
 216  005e               L57:
 217                     ; 30 		buffer[i] = FLASH_ReadByte(addr+i);
 219  005e 7b08          	ld	a,(OFST+7,sp)
 220  0060 97            	ld	xl,a
 221  0061 7b09          	ld	a,(OFST+8,sp)
 222  0063 1b01          	add	a,(OFST+0,sp)
 223  0065 2401          	jrnc	L21
 224  0067 5c            	incw	x
 225  0068               L21:
 226  0068 02            	rlwa	x,a
 227  0069 89            	pushw	x
 228  006a 96            	ldw	x,sp
 229  006b 1c0006        	addw	x,#OFST+5
 230  006e cd0000        	call	c_ltor
 232  0071 7b03          	ld	a,(OFST+2,sp)
 233  0073 cd0000        	call	c_ladc
 235  0076 be02          	ldw	x,c_lreg+2
 236  0078 89            	pushw	x
 237  0079 be00          	ldw	x,c_lreg
 238  007b 89            	pushw	x
 239  007c cd0000        	call	_FLASH_ReadByte
 241  007f 5b04          	addw	sp,#4
 242  0081 85            	popw	x
 243  0082 f7            	ld	(x),a
 244                     ; 31 		i++;
 246  0083 0c01          	inc	(OFST+0,sp)
 247                     ; 29 	while(i < BUFFER_SIZE ){//&& buffer[i] != '\0') {
 249  0085 7b01          	ld	a,(OFST+0,sp)
 250  0087 a120          	cp	a,#32
 251  0089 25d3          	jrult	L57
 252                     ; 34 	return buffer;
 254  008b 1e08          	ldw	x,(OFST+7,sp)
 257  008d 84            	pop	a
 258  008e 81            	ret
 261                     	switch	.const
 262  0004               L301_buffer:
 263  0004 00            	dc.b	0
 264  0005 000000000000  	ds.b	31
 314                     ; 37 main() {
 315                     	switch	.text
 316  008f               _main:
 318  008f 5221          	subw	sp,#33
 319       00000021      OFST:	set	33
 322                     ; 39 	u8 buffer[BUFFER_SIZE] = {0};
 324  0091 96            	ldw	x,sp
 325  0092 1c0001        	addw	x,#OFST-32
 326  0095 90ae0004      	ldw	y,#L301_buffer
 327  0099 a620          	ld	a,#32
 328  009b cd0000        	call	c_xymvx
 330                     ; 41 	UART2_init();
 332  009e cd0000        	call	_UART2_init
 334                     ; 43 	FLASH_DeInit();
 336  00a1 cd0000        	call	_FLASH_DeInit
 338                     ; 44 	FLASH_Unlock(FLASH_MEMTYPE_DATA);
 340  00a4 a601          	ld	a,#1
 341  00a6 cd0000        	call	_FLASH_Unlock
 343                     ; 45 	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
 345  00a9 4f            	clr	a
 346  00aa cd0000        	call	_FLASH_SetProgrammingTime
 348                     ; 47 	FLASH_Putstring(ADDRESS_CHAINE, "Texte 1");
 350  00ad ae00d9        	ldw	x,#L531
 351  00b0 89            	pushw	x
 352  00b1 ae4000        	ldw	x,#16384
 353  00b4 89            	pushw	x
 354  00b5 ae0000        	ldw	x,#0
 355  00b8 89            	pushw	x
 356  00b9 cd0000        	call	_FLASH_Putstring
 358  00bc 5b06          	addw	sp,#6
 359  00be               L731:
 360                     ; 50 		UART2_Putstring("Bienvenue dans le programme d'edition de l'EEPROM.\r\n");
 362  00be ae00a4        	ldw	x,#L341
 363  00c1 cd0000        	call	_UART2_Putstring
 365                     ; 51 		UART2_Putstring("R to read, W to write.\r\n");
 367  00c4 ae008b        	ldw	x,#L541
 368  00c7 cd0000        	call	_UART2_Putstring
 370                     ; 52 		c = UART2_GetChar();
 372  00ca cd0000        	call	_UART2_GetChar
 374  00cd 6b21          	ld	(OFST+0,sp),a
 375                     ; 53 		switch(c) {
 377  00cf 7b21          	ld	a,(OFST+0,sp)
 379                     ; 65 			default:
 379                     ; 66 			break;
 380  00d1 a052          	sub	a,#82
 381  00d3 270e          	jreq	L501
 382  00d5 a005          	sub	a,#5
 383  00d7 272d          	jreq	L701
 384  00d9 a01b          	sub	a,#27
 385  00db 2706          	jreq	L501
 386  00dd a005          	sub	a,#5
 387  00df 2725          	jreq	L701
 388  00e1 20db          	jra	L731
 389  00e3               L501:
 390                     ; 54 			case 'R':
 390                     ; 55 			case 'r':
 390                     ; 56 				UART2_Putstring("Valeur : ");
 392  00e3 ae0081        	ldw	x,#L351
 393  00e6 cd0000        	call	_UART2_Putstring
 395                     ; 57 				UART2_Putstring(FLASH_Readstring(ADDRESS_CHAINE, buffer));
 397  00e9 96            	ldw	x,sp
 398  00ea 1c0001        	addw	x,#OFST-32
 399  00ed 89            	pushw	x
 400  00ee ae4000        	ldw	x,#16384
 401  00f1 89            	pushw	x
 402  00f2 ae0000        	ldw	x,#0
 403  00f5 89            	pushw	x
 404  00f6 cd005b        	call	_FLASH_Readstring
 406  00f9 5b06          	addw	sp,#6
 407  00fb cd0000        	call	_UART2_Putstring
 409                     ; 58 				UART2_Putstring("\r\n");
 411  00fe ae007e        	ldw	x,#L551
 412  0101 cd0000        	call	_UART2_Putstring
 414                     ; 59 			break;
 416  0104 20b8          	jra	L731
 417  0106               L701:
 418                     ; 60 			case 'W':
 418                     ; 61 			case 'w':
 418                     ; 62 				UART2_Putstring("Ecriture de la chaine \"Le STM8 c'est biv !\" dans l'EEPROM du STM8\r\n");
 420  0106 ae003a        	ldw	x,#L751
 421  0109 cd0000        	call	_UART2_Putstring
 423                     ; 63 				FLASH_Putstring(ADDRESS_CHAINE, "Le STM8 c'est biv !\r\n");
 425  010c ae0024        	ldw	x,#L161
 426  010f 89            	pushw	x
 427  0110 ae4000        	ldw	x,#16384
 428  0113 89            	pushw	x
 429  0114 ae0000        	ldw	x,#0
 430  0117 89            	pushw	x
 431  0118 cd0000        	call	_FLASH_Putstring
 433  011b 5b06          	addw	sp,#6
 434                     ; 64 			break;
 436  011d 209f          	jra	L731
 437  011f               L111:
 438                     ; 65 			default:
 438                     ; 66 			break;
 440  011f 209d          	jra	L731
 441  0121               L151:
 443  0121 209b          	jra	L731
 456                     	xdef	_main
 457                     	xdef	_FLASH_Readstring
 458                     	xdef	_FLASH_Putstring
 459                     	xref	_UART2_Putstring
 460                     	xref	_UART2_GetChar
 461                     	xref	_UART2_init
 462                     	xref	_FLASH_SetProgrammingTime
 463                     	xref	_FLASH_ReadByte
 464                     	xref	_FLASH_ProgramByte
 465                     	xref	_FLASH_DeInit
 466                     	xref	_FLASH_Unlock
 467                     	switch	.const
 468  0024               L161:
 469  0024 4c652053544d  	dc.b	"Le STM8 c'est biv "
 470  0036 210d          	dc.b	"!",13
 471  0038 0a00          	dc.b	10,0
 472  003a               L751:
 473  003a 456372697475  	dc.b	"Ecriture de la cha"
 474  004c 696e652022    	dc.b	"ine ",34
 475  0051 4c652053544d  	dc.b	"Le STM8 c'est biv "
 476  0063 2122          	dc.b	"!",34
 477  0065 2064616e7320  	dc.b	" dans l'EEPROM du "
 478  0077 53544d380d    	dc.b	"STM8",13
 479  007c 0a00          	dc.b	10,0
 480  007e               L551:
 481  007e 0d0a00        	dc.b	13,10,0
 482  0081               L351:
 483  0081 56616c657572  	dc.b	"Valeur : ",0
 484  008b               L541:
 485  008b 5220746f2072  	dc.b	"R to read, W to wr"
 486  009d 6974652e0d    	dc.b	"ite.",13
 487  00a2 0a00          	dc.b	10,0
 488  00a4               L341:
 489  00a4 4269656e7665  	dc.b	"Bienvenue dans le "
 490  00b6 70726f677261  	dc.b	"programme d'editio"
 491  00c8 6e206465206c  	dc.b	"n de l'EEPROM.",13
 492  00d7 0a00          	dc.b	10,0
 493  00d9               L531:
 494  00d9 546578746520  	dc.b	"Texte 1",0
 495                     	xref.b	c_lreg
 496                     	xref.b	c_x
 516                     	xref	c_xymvx
 517                     	xref	c_ladc
 518                     	xref	c_lgadc
 519                     	xref	c_ladd
 520                     	xref	c_ltor
 521                     	end
