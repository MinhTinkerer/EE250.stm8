   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  75                     ; 47 void FLASH_Unlock(FLASH_MemType_TypeDef MemType)
  75                     ; 48 {
  77                     	switch	.text
  78  0000               _FLASH_Unlock:
  82                     ; 50     assert_param(IS_MEMORY_TYPE_OK(MemType));
  84                     ; 53     if (MemType == FLASH_MEMTYPE_PROG)
  86  0000 4d            	tnz	a
  87  0001 260a          	jrne	L73
  88                     ; 55         FLASH->PUKR = FLASH_RASS_KEY1;
  90  0003 35565062      	mov	20578,#86
  91                     ; 56         FLASH->PUKR = FLASH_RASS_KEY2;
  93  0007 35ae5062      	mov	20578,#174
  95  000b 2008          	jra	L14
  96  000d               L73:
  97                     ; 62         FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
  99  000d 35ae5064      	mov	20580,#174
 100                     ; 63         FLASH->DUKR = FLASH_RASS_KEY1;
 102  0011 35565064      	mov	20580,#86
 103  0015               L14:
 104                     ; 65 }
 107  0015 81            	ret
 142                     ; 73 void FLASH_Lock(FLASH_MemType_TypeDef MemType)
 142                     ; 74 {
 143                     	switch	.text
 144  0016               _FLASH_Lock:
 148                     ; 76     assert_param(IS_MEMORY_TYPE_OK(MemType));
 150                     ; 79     if (MemType == FLASH_MEMTYPE_PROG)
 152  0016 4d            	tnz	a
 153  0017 2606          	jrne	L16
 154                     ; 81         FLASH->IAPSR = (u8)(~FLASH_IAPSR_PUL);
 156  0019 35fd505f      	mov	20575,#253
 158  001d 2004          	jra	L36
 159  001f               L16:
 160                     ; 87         FLASH->IAPSR = (u8)(~FLASH_IAPSR_DUL);
 162  001f 35f7505f      	mov	20575,#247
 163  0023               L36:
 164                     ; 89 }
 167  0023 81            	ret
 201                     ; 97 void FLASH_DeInit(void)
 201                     ; 98 {
 202                     	switch	.text
 203  0024               _FLASH_DeInit:
 205  0024 88            	push	a
 206       00000001      OFST:	set	1
 209                     ; 99     u8 temp = 0;
 211                     ; 100     FLASH->CR1 = FLASH_CR1_RESET_VALUE;
 213  0025 725f505a      	clr	20570
 214                     ; 101     FLASH->CR2 = FLASH_CR2_RESET_VALUE;
 216  0029 725f505b      	clr	20571
 217                     ; 102     FLASH->NCR2 = FLASH_NCR2_RESET_VALUE;
 219  002d 35ff505c      	mov	20572,#255
 220                     ; 103     FLASH->IAPSR &= (u8)(~FLASH_IAPSR_DUL);
 222  0031 7217505f      	bres	20575,#3
 223                     ; 104     FLASH->IAPSR &= (u8)(~FLASH_IAPSR_PUL);
 225  0035 7213505f      	bres	20575,#1
 226                     ; 105     temp = FLASH->IAPSR; /* Reading of this register causes the clearing of status flags */
 228  0039 c6505f        	ld	a,20575
 229                     ; 106 }
 232  003c 84            	pop	a
 233  003d 81            	ret
 288                     ; 113 void FLASH_ITConfig(FunctionalState NewState)
 288                     ; 114 {
 289                     	switch	.text
 290  003e               _FLASH_ITConfig:
 294                     ; 115     if (NewState != DISABLE)
 296  003e 4d            	tnz	a
 297  003f 2706          	jreq	L131
 298                     ; 117         FLASH->CR1 |= FLASH_CR1_IE; /* Enables the interrupt sources */
 300  0041 7212505a      	bset	20570,#1
 302  0045 2004          	jra	L331
 303  0047               L131:
 304                     ; 121         FLASH->CR1 &= (u8)(~FLASH_CR1_IE); /* Disables the interrupt sources */
 306  0047 7213505a      	bres	20570,#1
 307  004b               L331:
 308                     ; 123 }
 311  004b 81            	ret
 345                     ; 134 void FLASH_EraseByte(u32 Address)
 345                     ; 135 {
 346                     	switch	.text
 347  004c               _FLASH_EraseByte:
 349       00000000      OFST:	set	0
 352                     ; 137     assert_param(IS_FLASH_ADDRESS_OK(Address));
 354                     ; 138     *((PointerAttr u8*) Address) = FLASH_CLEAR_BYTE; /* Erase byte */
 356  004c 7b04          	ld	a,(OFST+4,sp)
 357  004e b700          	ld	c_x,a
 358  0050 1e05          	ldw	x,(OFST+5,sp)
 359  0052 bf01          	ldw	c_x+1,x
 360  0054 4f            	clr	a
 361  0055 92bd0000      	ldf	[c_x.e],a
 362                     ; 140 }
 366  0059 81            	ret
 409                     ; 152 void FLASH_ProgramByte(u32 Address, u8 Data)
 409                     ; 153 {
 410                     	switch	.text
 411  005a               _FLASH_ProgramByte:
 413       00000000      OFST:	set	0
 416                     ; 155     assert_param(IS_FLASH_ADDRESS_OK(Address));
 418                     ; 156     *((PointerAttr u8*) Address) = Data;
 420  005a 7b07          	ld	a,(OFST+7,sp)
 421  005c 88            	push	a
 422  005d 7b05          	ld	a,(OFST+5,sp)
 423  005f b700          	ld	c_x,a
 424  0061 1e06          	ldw	x,(OFST+6,sp)
 425  0063 84            	pop	a
 426  0064 bf01          	ldw	c_x+1,x
 427  0066 92bd0000      	ldf	[c_x.e],a
 428                     ; 157 }
 431  006a 81            	ret
 465                     ; 167 u8 FLASH_ReadByte(u32 Address)
 465                     ; 168 {
 466                     	switch	.text
 467  006b               _FLASH_ReadByte:
 469       00000000      OFST:	set	0
 472                     ; 170     assert_param(IS_FLASH_ADDRESS_OK(Address));
 474                     ; 171     return(*((PointerAttr u8*) Address)); /* Read byte */
 476  006b 7b04          	ld	a,(OFST+4,sp)
 477  006d b700          	ld	c_x,a
 478  006f 1e05          	ldw	x,(OFST+5,sp)
 479  0071 bf01          	ldw	c_x+1,x
 480  0073 92bc0000      	ldf	a,[c_x.e]
 483  0077 81            	ret
 526                     ; 184 void FLASH_ProgramWord(u32 Address, u32 Data)
 526                     ; 185 {
 527                     	switch	.text
 528  0078               _FLASH_ProgramWord:
 530       00000000      OFST:	set	0
 533                     ; 187     assert_param(IS_FLASH_ADDRESS_OK(Address));
 535                     ; 190     FLASH->CR2 |= FLASH_CR2_WPRG;
 537  0078 721c505b      	bset	20571,#6
 538                     ; 191     FLASH->NCR2 &= (u8)(~FLASH_NCR2_NWPRG);
 540  007c 721d505c      	bres	20572,#6
 541                     ; 193     *((PointerAttr u8*)Address)       = *((u8*)(&Data)); /* Write one byte - from lowest address*/
 543  0080 7b07          	ld	a,(OFST+7,sp)
 544  0082 88            	push	a
 545  0083 7b05          	ld	a,(OFST+5,sp)
 546  0085 b700          	ld	c_x,a
 547  0087 1e06          	ldw	x,(OFST+6,sp)
 548  0089 84            	pop	a
 549  008a bf01          	ldw	c_x+1,x
 550  008c 92bd0000      	ldf	[c_x.e],a
 551                     ; 194     *(((PointerAttr u8*)Address) + 1) = *((u8*)(&Data)+1); /* Write one byte*/
 553  0090 7b08          	ld	a,(OFST+8,sp)
 554  0092 88            	push	a
 555  0093 7b05          	ld	a,(OFST+5,sp)
 556  0095 b700          	ld	c_x,a
 557  0097 1e06          	ldw	x,(OFST+6,sp)
 558  0099 84            	pop	a
 559  009a 90ae0001      	ldw	y,#1
 560  009e bf01          	ldw	c_x+1,x
 561  00a0 93            	ldw	x,y
 562  00a1 92a70000      	ldf	([c_x.e],x),a
 563                     ; 195     *(((PointerAttr u8*)Address) + 2) = *((u8*)(&Data)+2); /* Write one byte*/
 565  00a5 7b09          	ld	a,(OFST+9,sp)
 566  00a7 88            	push	a
 567  00a8 7b05          	ld	a,(OFST+5,sp)
 568  00aa b700          	ld	c_x,a
 569  00ac 1e06          	ldw	x,(OFST+6,sp)
 570  00ae 84            	pop	a
 571  00af 90ae0002      	ldw	y,#2
 572  00b3 bf01          	ldw	c_x+1,x
 573  00b5 93            	ldw	x,y
 574  00b6 92a70000      	ldf	([c_x.e],x),a
 575                     ; 196     *(((PointerAttr u8*)Address) + 3) = *((u8*)(&Data)+3); /* Write one byte - from higher address*/
 577  00ba 7b0a          	ld	a,(OFST+10,sp)
 578  00bc 88            	push	a
 579  00bd 7b05          	ld	a,(OFST+5,sp)
 580  00bf b700          	ld	c_x,a
 581  00c1 1e06          	ldw	x,(OFST+6,sp)
 582  00c3 84            	pop	a
 583  00c4 90ae0003      	ldw	y,#3
 584  00c8 bf01          	ldw	c_x+1,x
 585  00ca 93            	ldw	x,y
 586  00cb 92a70000      	ldf	([c_x.e],x),a
 587                     ; 197 }
 590  00cf 81            	ret
 635                     ; 206 void FLASH_ProgramOptionByte(u16 Address, u8 Data)
 635                     ; 207 {
 636                     	switch	.text
 637  00d0               _FLASH_ProgramOptionByte:
 639  00d0 89            	pushw	x
 640       00000000      OFST:	set	0
 643                     ; 209     assert_param(IS_OPTION_BYTE_ADDRESS_OK(Address));
 645                     ; 212     FLASH->CR2 |= FLASH_CR2_OPT;
 647  00d1 721e505b      	bset	20571,#7
 648                     ; 213     FLASH->NCR2 &= (u8)(~FLASH_NCR2_NOPT);
 650  00d5 721f505c      	bres	20572,#7
 651                     ; 216     *((NEAR u8*)Address) = Data;
 653  00d9 7b05          	ld	a,(OFST+5,sp)
 654  00db 1e01          	ldw	x,(OFST+1,sp)
 655  00dd f7            	ld	(x),a
 656                     ; 217     *((NEAR u8*)(Address + 1)) = (u8)(~Data);
 658  00de 7b05          	ld	a,(OFST+5,sp)
 659  00e0 43            	cpl	a
 660  00e1 1e01          	ldw	x,(OFST+1,sp)
 661  00e3 e701          	ld	(1,x),a
 662                     ; 219     FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
 664  00e5 a601          	ld	a,#1
 665  00e7 cd01b4        	call	_FLASH_WaitForLastOperation
 667                     ; 222     FLASH->CR2 &= (u8)(~FLASH_CR2_OPT);
 669  00ea 721f505b      	bres	20571,#7
 670                     ; 223     FLASH->NCR2 |= FLASH_NCR2_NOPT;
 672  00ee 721e505c      	bset	20572,#7
 673                     ; 224 }
 676  00f2 85            	popw	x
 677  00f3 81            	ret
 713                     ; 232 void FLASH_EraseOptionByte(u16 Address)
 713                     ; 233 {
 714                     	switch	.text
 715  00f4               _FLASH_EraseOptionByte:
 719                     ; 235     assert_param(IS_OPTION_BYTE_ADDRESS_OK(Address));
 721                     ; 238     FLASH->CR2 |= FLASH_CR2_OPT;
 723  00f4 721e505b      	bset	20571,#7
 724                     ; 239     FLASH->NCR2 &= (u8)(~FLASH_NCR2_NOPT);
 726  00f8 721f505c      	bres	20572,#7
 727                     ; 242     *((NEAR u8*)Address) = FLASH_CLEAR_BYTE;
 729  00fc 7f            	clr	(x)
 730                     ; 243     *((NEAR u8*)(Address + 1 )) = FLASH_SET_BYTE;
 733  00fd a6ff          	ld	a,#255
 734  00ff e701          	ld	(1,x),a
 735                     ; 245     FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
 738  0101 a601          	ld	a,#1
 739  0103 cd01b4        	call	_FLASH_WaitForLastOperation
 741                     ; 248     FLASH->CR2 &= (u8)(~FLASH_CR2_OPT);
 743  0106 721f505b      	bres	20571,#7
 744                     ; 249     FLASH->NCR2 |= FLASH_NCR2_NOPT;
 746  010a 721e505c      	bset	20572,#7
 747                     ; 250 }
 750  010e 81            	ret
 813                     ; 256 u16 FLASH_ReadOptionByte(u16 Address)
 813                     ; 257 {
 814                     	switch	.text
 815  010f               _FLASH_ReadOptionByte:
 817  010f 5204          	subw	sp,#4
 818       00000004      OFST:	set	4
 821                     ; 258     u8 value_optbyte, value_optbyte_complement = 0;
 823                     ; 259     u16 res_value = 0;
 825                     ; 262     assert_param(IS_OPTION_BYTE_ADDRESS_OK(Address));
 827                     ; 265     value_optbyte = *((NEAR u8*)Address); /* Read option byte */
 829  0111 f6            	ld	a,(x)
 830  0112 6b01          	ld	(OFST-3,sp),a
 831                     ; 266     value_optbyte_complement = *(((NEAR u8*)Address) + 1); /* Read option byte complement*/
 833  0114 e601          	ld	a,(1,x)
 834  0116 6b02          	ld	(OFST-2,sp),a
 835                     ; 268     if (value_optbyte == (u8)(~value_optbyte_complement))
 837  0118 7b02          	ld	a,(OFST-2,sp)
 838  011a 43            	cpl	a
 839  011b 1101          	cp	a,(OFST-3,sp)
 840  011d 2617          	jrne	L723
 841                     ; 270         res_value = (u16)((u16)value_optbyte << 8);
 843  011f 7b01          	ld	a,(OFST-3,sp)
 844  0121 5f            	clrw	x
 845  0122 97            	ld	xl,a
 846  0123 4f            	clr	a
 847  0124 02            	rlwa	x,a
 848  0125 1f03          	ldw	(OFST-1,sp),x
 849                     ; 271         res_value = res_value | (u16)value_optbyte_complement;
 851  0127 7b02          	ld	a,(OFST-2,sp)
 852  0129 5f            	clrw	x
 853  012a 97            	ld	xl,a
 854  012b 01            	rrwa	x,a
 855  012c 1a04          	or	a,(OFST+0,sp)
 856  012e 01            	rrwa	x,a
 857  012f 1a03          	or	a,(OFST-1,sp)
 858  0131 01            	rrwa	x,a
 859  0132 1f03          	ldw	(OFST-1,sp),x
 861  0134 2005          	jra	L133
 862  0136               L723:
 863                     ; 275         res_value = FLASH_OPTIONBYTE_ERROR;
 865  0136 ae5555        	ldw	x,#21845
 866  0139 1f03          	ldw	(OFST-1,sp),x
 867  013b               L133:
 868                     ; 278     return(res_value);
 870  013b 1e03          	ldw	x,(OFST-1,sp)
 873  013d 5b04          	addw	sp,#4
 874  013f 81            	ret
 948                     ; 287 void FLASH_SetLowPowerMode(FLASH_LPMode_TypeDef LPMode)
 948                     ; 288 {
 949                     	switch	.text
 950  0140               _FLASH_SetLowPowerMode:
 952  0140 88            	push	a
 953       00000000      OFST:	set	0
 956                     ; 290     assert_param(IS_FLASH_LOW_POWER_MODE_OK(LPMode));
 958                     ; 292     FLASH->CR1 &= (u8)(~(FLASH_CR1_HALT | FLASH_CR1_AHALT)); /* Clears the two bits */
 960  0141 c6505a        	ld	a,20570
 961  0144 a4f3          	and	a,#243
 962  0146 c7505a        	ld	20570,a
 963                     ; 293     FLASH->CR1 |= (u8)LPMode; /* Sets the new mode */
 965  0149 c6505a        	ld	a,20570
 966  014c 1a01          	or	a,(OFST+1,sp)
 967  014e c7505a        	ld	20570,a
 968                     ; 294 }
 971  0151 84            	pop	a
 972  0152 81            	ret
1030                     ; 302 void FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef ProgTime)
1030                     ; 303 {
1031                     	switch	.text
1032  0153               _FLASH_SetProgrammingTime:
1036                     ; 305     assert_param(IS_FLASH_PROGRAM_TIME_OK(ProgTime));
1038                     ; 307     FLASH->CR1 &= (u8)(~FLASH_CR1_FIX);
1040  0153 7211505a      	bres	20570,#0
1041                     ; 308     FLASH->CR1 |= (u8)ProgTime;
1043  0157 ca505a        	or	a,20570
1044  015a c7505a        	ld	20570,a
1045                     ; 309 }
1048  015d 81            	ret
1073                     ; 317 FLASH_LPMode_TypeDef FLASH_GetLowPowerMode(void)
1073                     ; 318 {
1074                     	switch	.text
1075  015e               _FLASH_GetLowPowerMode:
1079                     ; 319     return((FLASH_LPMode_TypeDef)(FLASH->CR1 & (FLASH_CR1_HALT | FLASH_CR1_AHALT)));
1081  015e c6505a        	ld	a,20570
1082  0161 a40c          	and	a,#12
1085  0163 81            	ret
1110                     ; 328 FLASH_ProgramTime_TypeDef FLASH_GetProgrammingTime(void)
1110                     ; 329 {
1111                     	switch	.text
1112  0164               _FLASH_GetProgrammingTime:
1116                     ; 330     return((FLASH_ProgramTime_TypeDef)(FLASH->CR1 & FLASH_CR1_FIX));
1118  0164 c6505a        	ld	a,20570
1119  0167 a401          	and	a,#1
1122  0169 81            	ret
1156                     ; 339 u32 FLASH_GetBootSize(void)
1156                     ; 340 {
1157                     	switch	.text
1158  016a               _FLASH_GetBootSize:
1160  016a 5204          	subw	sp,#4
1161       00000004      OFST:	set	4
1164                     ; 341     u32 temp = 0;
1166                     ; 344     temp = (u32)((u32)FLASH->FPR * (u32)512);
1168  016c c6505d        	ld	a,20573
1169  016f 5f            	clrw	x
1170  0170 97            	ld	xl,a
1171  0171 90ae0200      	ldw	y,#512
1172  0175 cd0000        	call	c_umul
1174  0178 96            	ldw	x,sp
1175  0179 1c0001        	addw	x,#OFST-3
1176  017c cd0000        	call	c_rtol
1178                     ; 347     if (FLASH->FPR == 0xFF)
1180  017f c6505d        	ld	a,20573
1181  0182 a1ff          	cp	a,#255
1182  0184 2611          	jrne	L154
1183                     ; 349         temp += 512;
1185  0186 ae0200        	ldw	x,#512
1186  0189 bf02          	ldw	c_lreg+2,x
1187  018b ae0000        	ldw	x,#0
1188  018e bf00          	ldw	c_lreg,x
1189  0190 96            	ldw	x,sp
1190  0191 1c0001        	addw	x,#OFST-3
1191  0194 cd0000        	call	c_lgadd
1193  0197               L154:
1194                     ; 353     return(temp);
1196  0197 96            	ldw	x,sp
1197  0198 1c0001        	addw	x,#OFST-3
1198  019b cd0000        	call	c_ltor
1202  019e 5b04          	addw	sp,#4
1203  01a0 81            	ret
1312                     ; 365 FlagStatus FLASH_GetFlagStatus(FLASH_Flag_TypeDef FLASH_FLAG)
1312                     ; 366 {
1313                     	switch	.text
1314  01a1               _FLASH_GetFlagStatus:
1316  01a1 88            	push	a
1317       00000001      OFST:	set	1
1320                     ; 367     FlagStatus status = RESET;
1322                     ; 369     assert_param(IS_FLASH_FLAGS_OK(FLASH_FLAG));
1324                     ; 372     if ((FLASH->IAPSR & (u8)FLASH_FLAG) != (u8)RESET)
1326  01a2 c4505f        	and	a,20575
1327  01a5 2706          	jreq	L325
1328                     ; 374         status = SET; /* FLASH_FLAG is set */
1330  01a7 a601          	ld	a,#1
1331  01a9 6b01          	ld	(OFST+0,sp),a
1333  01ab 2002          	jra	L525
1334  01ad               L325:
1335                     ; 378         status = RESET; /* FLASH_FLAG is reset*/
1337  01ad 0f01          	clr	(OFST+0,sp)
1338  01af               L525:
1339                     ; 382     return status;
1341  01af 7b01          	ld	a,(OFST+0,sp)
1344  01b1 5b01          	addw	sp,#1
1345  01b3 81            	ret
1438                     ; 393 FLASH_Status_TypeDef FLASH_WaitForLastOperation(FLASH_MemType_TypeDef MemType)
1438                     ; 394 {
1439                     	switch	.text
1440  01b4               _FLASH_WaitForLastOperation:
1442  01b4 5203          	subw	sp,#3
1443       00000003      OFST:	set	3
1446                     ; 395     u8 flagstatus = 0x00;
1448  01b6 0f03          	clr	(OFST+0,sp)
1449                     ; 396     u16 timeout = OPERATION_TIMEOUT;
1451  01b8 ae1000        	ldw	x,#4096
1452  01bb 1f01          	ldw	(OFST-2,sp),x
1453                     ; 399     if (MemType == FLASH_MEMTYPE_PROG)
1455  01bd 4d            	tnz	a
1456  01be 2628          	jrne	L706
1458  01c0 200e          	jra	L575
1459  01c2               L375:
1460                     ; 403             flagstatus = (u8)(FLASH->IAPSR & (FLASH_IAPSR_EOP |
1460                     ; 404                                               FLASH_IAPSR_WR_PG_DIS));
1462  01c2 c6505f        	ld	a,20575
1463  01c5 a405          	and	a,#5
1464  01c7 6b03          	ld	(OFST+0,sp),a
1465                     ; 405             timeout--;
1467  01c9 1e01          	ldw	x,(OFST-2,sp)
1468  01cb 1d0001        	subw	x,#1
1469  01ce 1f01          	ldw	(OFST-2,sp),x
1470  01d0               L575:
1471                     ; 401         while ((flagstatus == 0x00) && (timeout != 0x00))
1473  01d0 0d03          	tnz	(OFST+0,sp)
1474  01d2 261c          	jrne	L306
1476  01d4 1e01          	ldw	x,(OFST-2,sp)
1477  01d6 26ea          	jrne	L375
1478  01d8 2016          	jra	L306
1479  01da               L506:
1480                     ; 412             flagstatus = (u8)(FLASH->IAPSR & (FLASH_IAPSR_HVOFF |
1480                     ; 413                                               FLASH_IAPSR_WR_PG_DIS));
1482  01da c6505f        	ld	a,20575
1483  01dd a441          	and	a,#65
1484  01df 6b03          	ld	(OFST+0,sp),a
1485                     ; 414             timeout--;
1487  01e1 1e01          	ldw	x,(OFST-2,sp)
1488  01e3 1d0001        	subw	x,#1
1489  01e6 1f01          	ldw	(OFST-2,sp),x
1490  01e8               L706:
1491                     ; 410         while ((flagstatus == 0x00) && (timeout != 0x00))
1493  01e8 0d03          	tnz	(OFST+0,sp)
1494  01ea 2604          	jrne	L306
1496  01ec 1e01          	ldw	x,(OFST-2,sp)
1497  01ee 26ea          	jrne	L506
1498  01f0               L306:
1499                     ; 425     if (timeout == 0x00 )
1501  01f0 1e01          	ldw	x,(OFST-2,sp)
1502  01f2 2604          	jrne	L516
1503                     ; 427         flagstatus = FLASH_STATUS_TIMEOUT;
1505  01f4 a602          	ld	a,#2
1506  01f6 6b03          	ld	(OFST+0,sp),a
1507  01f8               L516:
1508                     ; 430     return((FLASH_Status_TypeDef)flagstatus);
1510  01f8 7b03          	ld	a,(OFST+0,sp)
1513  01fa 5b03          	addw	sp,#3
1514  01fc 81            	ret
1576                     ; 457 void FLASH_EraseBlock(u16 BlockNum, FLASH_MemType_TypeDef MemType)
1576                     ; 458 {
1577                     	switch	.text
1578  01fd               _FLASH_EraseBlock:
1580  01fd 89            	pushw	x
1581  01fe 5206          	subw	sp,#6
1582       00000006      OFST:	set	6
1585                     ; 459     u16 timeout = OPERATION_TIMEOUT;
1587  0200 ae1000        	ldw	x,#4096
1588  0203 1f01          	ldw	(OFST-5,sp),x
1589                     ; 461     u32 StartAddress = 0;
1591                     ; 468     assert_param(IS_MEMORY_TYPE_OK(MemType));
1593                     ; 469     if (MemType == FLASH_MEMTYPE_PROG)
1595  0205 0d0b          	tnz	(OFST+5,sp)
1596  0207 260c          	jrne	L156
1597                     ; 471         assert_param(IS_FLASH_PROG_BLOCK_NUMBER_OK(BlockNum));
1599                     ; 472         StartAddress = FLASH_PROG_START_PHYSICAL_ADDRESS;
1601  0209 ae8000        	ldw	x,#32768
1602  020c 1f05          	ldw	(OFST-1,sp),x
1603  020e ae0000        	ldw	x,#0
1604  0211 1f03          	ldw	(OFST-3,sp),x
1606  0213 200a          	jra	L356
1607  0215               L156:
1608                     ; 476         assert_param(IS_FLASH_DATA_BLOCK_NUMBER_OK(BlockNum));
1610                     ; 477         StartAddress = FLASH_DATA_START_PHYSICAL_ADDRESS;
1612  0215 ae4000        	ldw	x,#16384
1613  0218 1f05          	ldw	(OFST-1,sp),x
1614  021a ae0000        	ldw	x,#0
1615  021d 1f03          	ldw	(OFST-3,sp),x
1616  021f               L356:
1617                     ; 481     StartAddress = StartAddress + ((u32)BlockNum * FLASH_BLOCK_SIZE);
1619  021f 1e07          	ldw	x,(OFST+1,sp)
1620  0221 a680          	ld	a,#128
1621  0223 cd0000        	call	c_cmulx
1623  0226 96            	ldw	x,sp
1624  0227 1c0003        	addw	x,#OFST-3
1625  022a cd0000        	call	c_lgadd
1627                     ; 484     FLASH->CR2 |= FLASH_CR2_ERASE;
1629  022d 721a505b      	bset	20571,#5
1630                     ; 485     FLASH->NCR2 &= (u8)(~FLASH_NCR2_NERASE);
1632  0231 721b505c      	bres	20572,#5
1633                     ; 487     *((PointerAttr u8*) StartAddress) = FLASH_CLEAR_BYTE;
1635  0235 7b04          	ld	a,(OFST-2,sp)
1636  0237 b700          	ld	c_x,a
1637  0239 1e05          	ldw	x,(OFST-1,sp)
1638  023b bf01          	ldw	c_x+1,x
1639  023d 4f            	clr	a
1640  023e 92bd0000      	ldf	[c_x.e],a
1641                     ; 488     *((PointerAttr u8*) StartAddress + 1) = FLASH_CLEAR_BYTE;
1644  0242 7b04          	ld	a,(OFST-2,sp)
1645  0244 b700          	ld	c_x,a
1646  0246 1e05          	ldw	x,(OFST-1,sp)
1647  0248 90ae0001      	ldw	y,#1
1648  024c bf01          	ldw	c_x+1,x
1649  024e 93            	ldw	x,y
1650  024f 4f            	clr	a
1651  0250 92a70000      	ldf	([c_x.e],x),a
1652                     ; 489     *((PointerAttr u8*) StartAddress + 2) = FLASH_CLEAR_BYTE;
1655  0254 7b04          	ld	a,(OFST-2,sp)
1656  0256 b700          	ld	c_x,a
1657  0258 1e05          	ldw	x,(OFST-1,sp)
1658  025a 90ae0002      	ldw	y,#2
1659  025e bf01          	ldw	c_x+1,x
1660  0260 93            	ldw	x,y
1661  0261 4f            	clr	a
1662  0262 92a70000      	ldf	([c_x.e],x),a
1663                     ; 490     *((PointerAttr u8*) StartAddress + 3) = FLASH_CLEAR_BYTE;
1666  0266 7b04          	ld	a,(OFST-2,sp)
1667  0268 b700          	ld	c_x,a
1668  026a 1e05          	ldw	x,(OFST-1,sp)
1669  026c 90ae0003      	ldw	y,#3
1670  0270 bf01          	ldw	c_x+1,x
1671  0272 93            	ldw	x,y
1672  0273 4f            	clr	a
1673  0274 92a70000      	ldf	([c_x.e],x),a
1676  0278 2007          	jra	L756
1677  027a               L556:
1678                     ; 507         timeout--;
1680  027a 1e01          	ldw	x,(OFST-5,sp)
1681  027c 1d0001        	subw	x,#1
1682  027f 1f01          	ldw	(OFST-5,sp),x
1683  0281               L756:
1684                     ; 505     while ((FLASH->IAPSR & FLASH_IAPSR_HVOFF) != 0x00 || (timeout == 0x00))
1686  0281 c6505f        	ld	a,20575
1687  0284 a540          	bcp	a,#64
1688  0286 26f2          	jrne	L556
1690  0288 1e01          	ldw	x,(OFST-5,sp)
1691  028a 27ee          	jreq	L556
1692                     ; 510 }
1695  028c 5b08          	addw	sp,#8
1696  028e 81            	ret
1809                     ; 525 void FLASH_ProgramBlock(u16 BlockNum, FLASH_MemType_TypeDef MemType, FLASH_ProgramMode_TypeDef ProgMode, u8 *Buffer)
1809                     ; 526 {
1810                     	switch	.text
1811  028f               _FLASH_ProgramBlock:
1813  028f 89            	pushw	x
1814  0290 5208          	subw	sp,#8
1815       00000008      OFST:	set	8
1818                     ; 527     u16 Count = 0;
1820                     ; 528     u32 StartAddress = 0;
1822                     ; 529     u16 timeout = OPERATION_TIMEOUT;
1824  0292 ae1000        	ldw	x,#4096
1825  0295 1f01          	ldw	(OFST-7,sp),x
1826                     ; 531     assert_param(IS_MEMORY_TYPE_OK(MemType));
1828                     ; 532     assert_param(IS_FLASH_PROGRAM_MODE_OK(ProgMode));
1830                     ; 533     if (MemType == FLASH_MEMTYPE_PROG)
1832  0297 0d0d          	tnz	(OFST+5,sp)
1833  0299 260c          	jrne	L147
1834                     ; 535         assert_param(IS_FLASH_PROG_BLOCK_NUMBER_OK(BlockNum));
1836                     ; 536         StartAddress = FLASH_PROG_START_PHYSICAL_ADDRESS;
1838  029b ae8000        	ldw	x,#32768
1839  029e 1f05          	ldw	(OFST-3,sp),x
1840  02a0 ae0000        	ldw	x,#0
1841  02a3 1f03          	ldw	(OFST-5,sp),x
1843  02a5 200a          	jra	L347
1844  02a7               L147:
1845                     ; 540         assert_param(IS_FLASH_DATA_BLOCK_NUMBER_OK(BlockNum));
1847                     ; 541         StartAddress = FLASH_DATA_START_PHYSICAL_ADDRESS;
1849  02a7 ae4000        	ldw	x,#16384
1850  02aa 1f05          	ldw	(OFST-3,sp),x
1851  02ac ae0000        	ldw	x,#0
1852  02af 1f03          	ldw	(OFST-5,sp),x
1853  02b1               L347:
1854                     ; 545     StartAddress = StartAddress + ((u32)BlockNum * FLASH_BLOCK_SIZE);
1856  02b1 1e09          	ldw	x,(OFST+1,sp)
1857  02b3 a680          	ld	a,#128
1858  02b5 cd0000        	call	c_cmulx
1860  02b8 96            	ldw	x,sp
1861  02b9 1c0003        	addw	x,#OFST-5
1862  02bc cd0000        	call	c_lgadd
1864                     ; 548     if (ProgMode == FLASH_PROGRAMMODE_STANDARD)
1866  02bf 0d0e          	tnz	(OFST+6,sp)
1867  02c1 260a          	jrne	L547
1868                     ; 551         FLASH->CR2 |= FLASH_CR2_PRG;
1870  02c3 7210505b      	bset	20571,#0
1871                     ; 552         FLASH->NCR2 &= (u8)(~FLASH_NCR2_NPRG);
1873  02c7 7211505c      	bres	20572,#0
1875  02cb 2008          	jra	L747
1876  02cd               L547:
1877                     ; 557         FLASH->CR2 |= FLASH_CR2_FPRG;
1879  02cd 7218505b      	bset	20571,#4
1880                     ; 558         FLASH->NCR2 &= (u8)(~FLASH_NCR2_NFPRG);
1882  02d1 7219505c      	bres	20572,#4
1883  02d5               L747:
1884                     ; 562     for (Count = 0; Count < FLASH_BLOCK_SIZE; Count++)
1886  02d5 5f            	clrw	x
1887  02d6 1f07          	ldw	(OFST-1,sp),x
1888  02d8               L157:
1889                     ; 564         *((PointerAttr u8*)StartAddress + Count) = ((u8)(Buffer[Count]));
1891  02d8 1e0f          	ldw	x,(OFST+7,sp)
1892  02da 72fb07        	addw	x,(OFST-1,sp)
1893  02dd f6            	ld	a,(x)
1894  02de 88            	push	a
1895  02df 7b05          	ld	a,(OFST-3,sp)
1896  02e1 b700          	ld	c_x,a
1897  02e3 1e06          	ldw	x,(OFST-2,sp)
1898  02e5 84            	pop	a
1899  02e6 1607          	ldw	y,(OFST-1,sp)
1900  02e8 bf01          	ldw	c_x+1,x
1901  02ea 93            	ldw	x,y
1902  02eb 92a70000      	ldf	([c_x.e],x),a
1903                     ; 562     for (Count = 0; Count < FLASH_BLOCK_SIZE; Count++)
1905  02ef 1e07          	ldw	x,(OFST-1,sp)
1906  02f1 1c0001        	addw	x,#1
1907  02f4 1f07          	ldw	(OFST-1,sp),x
1910  02f6 1e07          	ldw	x,(OFST-1,sp)
1911  02f8 a30080        	cpw	x,#128
1912  02fb 25db          	jrult	L157
1913                     ; 568     if (MemType == FLASH_MEMTYPE_DATA)
1915  02fd 7b0d          	ld	a,(OFST+5,sp)
1916  02ff a101          	cp	a,#1
1917  0301 2614          	jrne	L757
1919  0303 2007          	jra	L367
1920  0305               L167:
1921                     ; 573             timeout--;
1923  0305 1e01          	ldw	x,(OFST-7,sp)
1924  0307 1d0001        	subw	x,#1
1925  030a 1f01          	ldw	(OFST-7,sp),x
1926  030c               L367:
1927                     ; 571         while ((FLASH->IAPSR & FLASH_IAPSR_HVOFF) != 0x00 || (timeout == 0x00))
1929  030c c6505f        	ld	a,20575
1930  030f a540          	bcp	a,#64
1931  0311 26f2          	jrne	L167
1933  0313 1e01          	ldw	x,(OFST-7,sp)
1934  0315 27ee          	jreq	L167
1935  0317               L757:
1936                     ; 577 }
1939  0317 5b0a          	addw	sp,#10
1940  0319 81            	ret
1953                     	xdef	_FLASH_WaitForLastOperation
1954                     	xdef	_FLASH_ProgramBlock
1955                     	xdef	_FLASH_EraseBlock
1956                     	xdef	_FLASH_GetFlagStatus
1957                     	xdef	_FLASH_GetBootSize
1958                     	xdef	_FLASH_GetProgrammingTime
1959                     	xdef	_FLASH_GetLowPowerMode
1960                     	xdef	_FLASH_SetProgrammingTime
1961                     	xdef	_FLASH_SetLowPowerMode
1962                     	xdef	_FLASH_EraseOptionByte
1963                     	xdef	_FLASH_ProgramOptionByte
1964                     	xdef	_FLASH_ReadOptionByte
1965                     	xdef	_FLASH_ProgramWord
1966                     	xdef	_FLASH_ReadByte
1967                     	xdef	_FLASH_ProgramByte
1968                     	xdef	_FLASH_EraseByte
1969                     	xdef	_FLASH_ITConfig
1970                     	xdef	_FLASH_DeInit
1971                     	xdef	_FLASH_Lock
1972                     	xdef	_FLASH_Unlock
1973                     	xref.b	c_lreg
1974                     	xref.b	c_x
1975                     	xref.b	c_y
1994                     	xref	c_cmulx
1995                     	xref	c_ltor
1996                     	xref	c_lgadd
1997                     	xref	c_rtol
1998                     	xref	c_umul
1999                     	end
