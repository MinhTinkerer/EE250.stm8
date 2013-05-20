   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  44                     ; 5 void ITC_enableIT(void) {
  46                     	switch	.text
  47  0000               _ITC_enableIT:
  51                     ; 6 	rim();
  54  0000 9a            rim
  56                     ; 7 }
  60  0001 81            	ret
  83                     ; 9 void UART2_init(void) {
  84                     	switch	.text
  85  0002               _UART2_init:
  89                     ; 10 	UART2->CR1 = UART2_ONESTARTBIT_EIGHTDATABITS_NOPARITY;
  91  0002 725f5244      	clr	21060
  92                     ; 11 	UART2->CR3 = UART2->CR3 & ~UART2_CR3_STOP;
  94  0006 c65246        	ld	a,21062
  95  0009 a4cf          	and	a,#207
  96  000b c75246        	ld	21062,a
  97                     ; 13 	UART2->BRR2 = UART2_BRR2_9600;
  99  000e 725f5243      	clr	21059
 100                     ; 14 	UART2->BRR1 = UART2_BRR1_9600;
 102  0012 350d5242      	mov	21058,#13
 103                     ; 16 	UART2->CR2 |= UART2_CR2_TEN;
 105  0016 72165245      	bset	21061,#3
 106                     ; 17 	UART2->CR2 |= UART2_CR2_REN;
 108  001a 72145245      	bset	21061,#2
 109                     ; 18 }
 112  001e 81            	ret
 136                     ; 20 void UART2_initITReceive(void) {
 137                     	switch	.text
 138  001f               _UART2_initITReceive:
 142                     ; 21 	UART2->CR2 |= UART2_CR2_RIEN;
 144  001f 721a5245      	bset	21061,#5
 145                     ; 22 }
 148  0023 81            	ret
 171                     ; 24 char UART2_GetChar(void) {
 172                     	switch	.text
 173  0024               _UART2_GetChar:
 177  0024               L35:
 178                     ; 25 	while((UART2->SR & UART2_SR_RXNE) != UART2_SR_RXNE);
 180  0024 c65240        	ld	a,21056
 181  0027 a420          	and	a,#32
 182  0029 a120          	cp	a,#32
 183  002b 26f7          	jrne	L35
 184                     ; 26 	return UART2->DR;
 186  002d c65241        	ld	a,21057
 189  0030 81            	ret
 223                     ; 29 void UART2_Putchar(char c) {
 224                     	switch	.text
 225  0031               _UART2_Putchar:
 227  0031 88            	push	a
 228       00000000      OFST:	set	0
 231  0032               L77:
 232                     ; 30 	while((UART2->SR & UART2_SR_TXE) != UART2_SR_TXE);
 234  0032 c65240        	ld	a,21056
 235  0035 a480          	and	a,#128
 236  0037 a180          	cp	a,#128
 237  0039 26f7          	jrne	L77
 238                     ; 31 	UART2->DR = c;
 240  003b 7b01          	ld	a,(OFST+1,sp)
 241  003d c75241        	ld	21057,a
 242                     ; 32 }
 245  0040 84            	pop	a
 246  0041 81            	ret
 291                     ; 34 void UART2_Putstring(char* s) {
 292                     	switch	.text
 293  0042               _UART2_Putstring:
 295  0042 89            	pushw	x
 296  0043 89            	pushw	x
 297       00000002      OFST:	set	2
 300                     ; 35 	int i = 0;
 302  0044 5f            	clrw	x
 303  0045 1f01          	ldw	(OFST-1,sp),x
 305  0047 200f          	jra	L131
 306  0049               L521:
 307                     ; 37 		UART2_Putchar(s[i]);
 309  0049 1e01          	ldw	x,(OFST-1,sp)
 310  004b 72fb03        	addw	x,(OFST+1,sp)
 311  004e f6            	ld	a,(x)
 312  004f ade0          	call	_UART2_Putchar
 314                     ; 38 		i++;
 316  0051 1e01          	ldw	x,(OFST-1,sp)
 317  0053 1c0001        	addw	x,#1
 318  0056 1f01          	ldw	(OFST-1,sp),x
 319  0058               L131:
 320                     ; 36 	while(s[i]) {
 322  0058 1e01          	ldw	x,(OFST-1,sp)
 323  005a 72fb03        	addw	x,(OFST+1,sp)
 324  005d 7d            	tnz	(x)
 325  005e 26e9          	jrne	L521
 326                     ; 40 }
 329  0060 5b04          	addw	sp,#4
 330  0062 81            	ret
 353                     ; 42 char UART2_RXNEFlag(void) {
 354                     	switch	.text
 355  0063               _UART2_RXNEFlag:
 359                     ; 43 	return (UART2->SR & UART2_SR_RXNE) == UART2_SR_RXNE;
 361  0063 c65240        	ld	a,21056
 362  0066 a420          	and	a,#32
 363  0068 a120          	cp	a,#32
 364  006a 2604          	jrne	L22
 365  006c a601          	ld	a,#1
 366  006e 2001          	jra	L42
 367  0070               L22:
 368  0070 4f            	clr	a
 369  0071               L42:
 372  0071 81            	ret
 395                     ; 46 void TIL321_init(void) {
 396                     	switch	.text
 397  0072               _TIL321_init:
 401                     ; 47 	GPIOB->DDR = PB_ALL_OUT;				//Sortie
 403  0072 35ff5007      	mov	20487,#255
 404                     ; 48 	GPIOB->CR1 = PB_ALL_PUSH_PULL;	//Push-pull
 406  0076 35ff5008      	mov	20488,#255
 407                     ; 49 }
 410  007a 81            	ret
 445                     ; 51 void TIL321_affiche(char c) {
 446                     	switch	.text
 447  007b               _TIL321_affiche:
 451                     ; 52 	GPIOB->ODR = convertBCD2TIL(c);
 453  007b ad15          	call	_convertBCD2TIL
 455  007d 01            	rrwa	x,a
 456  007e c75005        	ld	20485,a
 457  0081 02            	rlwa	x,a
 458                     ; 53 }
 461  0082 81            	ret
 484                     ; 55 void PortC_init(void) {
 485                     	switch	.text
 486  0083               _PortC_init:
 490                     ; 56 	GPIOC->DDR = PC_ALL_IN;
 492  0083 725f500c      	clr	20492
 493                     ; 57 	GPIOC->CR1 = PC_ALL_PULLUP;
 495  0087 35ff500d      	mov	20493,#255
 496                     ; 58 }
 499  008b 81            	ret
 522                     ; 60 char PortC_IDR_filtre(void) {
 523                     	switch	.text
 524  008c               _PortC_IDR_filtre:
 528                     ; 61 	return GPIOC->IDR & PC_FILTRE_IDR;
 530  008c c6500b        	ld	a,20491
 531  008f a43e          	and	a,#62
 534  0091 81            	ret
 537                     .const:	section	.text
 538  0000               L312_caracteres:
 539  0000 fc            	dc.b	252
 540  0001 60            	dc.b	96
 541  0002 da            	dc.b	218
 542  0003 f2            	dc.b	242
 543  0004 66            	dc.b	102
 544  0005 b6            	dc.b	182
 545  0006 be            	dc.b	190
 546  0007 e0            	dc.b	224
 547  0008 fe            	dc.b	254
 548  0009 f6            	dc.b	246
 590                     ; 64 int convertBCD2TIL(char c) {
 591                     	switch	.text
 592  0092               _convertBCD2TIL:
 594  0092 88            	push	a
 595  0093 520a          	subw	sp,#10
 596       0000000a      OFST:	set	10
 599                     ; 65 	char caracteres[] = {	ZERO_TIL, UN_TIL, DEUX_TIL,	TROIS_TIL, QUATRE_TIL, CINQ_TIL, SIX_TIL, SEPT_TIL, HUIT_TIL, NEUF_TIL};
 601  0095 96            	ldw	x,sp
 602  0096 1c0001        	addw	x,#OFST-9
 603  0099 90ae0000      	ldw	y,#L312_caracteres
 604  009d a60a          	ld	a,#10
 605  009f cd0000        	call	c_xymvx
 607                     ; 67 	if(c >= 0 && c < 10) {
 609  00a2 7b0b          	ld	a,(OFST+1,sp)
 610  00a4 a10a          	cp	a,#10
 611  00a6 2411          	jruge	L732
 612                     ; 68 		return caracteres[c];
 614  00a8 96            	ldw	x,sp
 615  00a9 1c0001        	addw	x,#OFST-9
 616  00ac 9f            	ld	a,xl
 617  00ad 5e            	swapw	x
 618  00ae 1b0b          	add	a,(OFST+1,sp)
 619  00b0 2401          	jrnc	L04
 620  00b2 5c            	incw	x
 621  00b3               L04:
 622  00b3 02            	rlwa	x,a
 623  00b4 f6            	ld	a,(x)
 624  00b5 5f            	clrw	x
 625  00b6 97            	ld	xl,a
 627  00b7 2003          	jra	L24
 628  00b9               L732:
 629                     ; 71 		return ERREUR_TIL;
 631  00b9 ae009e        	ldw	x,#158
 633  00bc               L24:
 635  00bc 5b0b          	addw	sp,#11
 636  00be 81            	ret
 639                     	switch	.const
 640  000a               L342_chaines:
 641  000a 004c          	dc.w	L542
 642  000c 0048          	dc.w	L742
 643  000e 0044          	dc.w	L152
 644  0010 0040          	dc.w	L352
 645  0012 003c          	dc.w	L552
 646  0014 0038          	dc.w	L752
 647  0016 0034          	dc.w	L162
 648  0018 0030          	dc.w	L362
 649  001a 002c          	dc.w	L562
 650  001c 0028          	dc.w	L762
 694                     ; 75 char* convertBCD2String(char c) {
 695                     	switch	.text
 696  00bf               _convertBCD2String:
 698  00bf 88            	push	a
 699  00c0 5216          	subw	sp,#22
 700       00000016      OFST:	set	22
 703                     ; 76 	char* chaines[] = {"0\r\n", "1\r\n", "2\r\n", "3\r\n", "4\r\n", "5\r\n", "6\r\n", "7\r\n", "8\r\n", "9\r\n"};
 705  00c2 96            	ldw	x,sp
 706  00c3 1c0003        	addw	x,#OFST-19
 707  00c6 90ae000a      	ldw	y,#L342_chaines
 708  00ca a614          	ld	a,#20
 709  00cc cd0000        	call	c_xymvx
 711                     ; 78 	if(c >= 0 && c < 10) {
 713  00cf 7b17          	ld	a,(OFST+1,sp)
 714  00d1 a10a          	cp	a,#10
 715  00d3 2411          	jruge	L313
 716                     ; 79 		return chaines[c];
 718  00d5 96            	ldw	x,sp
 719  00d6 1c0003        	addw	x,#OFST-19
 720  00d9 1f01          	ldw	(OFST-21,sp),x
 721  00db 7b17          	ld	a,(OFST+1,sp)
 722  00dd 5f            	clrw	x
 723  00de 97            	ld	xl,a
 724  00df 58            	sllw	x
 725  00e0 72fb01        	addw	x,(OFST-21,sp)
 726  00e3 fe            	ldw	x,(x)
 728  00e4 2003          	jra	L64
 729  00e6               L313:
 730                     ; 82 		return "Erreur.\r\n";
 732  00e6 ae001e        	ldw	x,#L713
 734  00e9               L64:
 736  00e9 5b17          	addw	sp,#23
 737  00eb 81            	ret
 760                     ; 86 void LEDV_init(void) {
 761                     	switch	.text
 762  00ec               _LEDV_init:
 766                     ; 87 	GPIOD->DDR = GPIOD->DDR | GPIO_PIN_0;		//Sortie
 768  00ec 72105011      	bset	20497,#0
 769                     ; 88 	GPIOD->CR1 = GPIOD->CR1 & ~GPIO_PIN_0;	//Open Drain
 771  00f0 72115012      	bres	20498,#0
 772                     ; 89 }
 775  00f4 81            	ret
 809                     ; 91 void LEDV_etat(char c) {
 810                     	switch	.text
 811  00f5               _LEDV_etat:
 815                     ; 92 	if(c == LEDV_ALLUME)
 817  00f5 a101          	cp	a,#1
 818  00f7 2606          	jrne	L743
 819                     ; 93 		GPIOD->ODR = GPIOD->ODR & ~GPIO_PIN_0;
 821  00f9 7211500f      	bres	20495,#0
 823  00fd 2004          	jra	L153
 824  00ff               L743:
 825                     ; 95 		GPIOD->ODR = GPIOD->ODR | GPIO_PIN_0;
 827  00ff 7210500f      	bset	20495,#0
 828  0103               L153:
 829                     ; 96 }
 832  0103 81            	ret
 866                     ; 98 void BP_init(char numero) {
 867                     	switch	.text
 868  0104               _BP_init:
 872                     ; 99 	switch(numero) {
 875                     ; 107 		break;
 876  0104 4a            	dec	a
 877  0105 2705          	jreq	L353
 878  0107 4a            	dec	a
 879  0108 270c          	jreq	L553
 880  010a 2012          	jra	L773
 881  010c               L353:
 882                     ; 100 		case 1:
 882                     ; 101 		GPIOD->DDR = GPIOD->DDR & ~GPIO_PIN_7;	//Entree
 884  010c 721f5011      	bres	20497,#7
 885                     ; 102 		GPIOD->CR1 = GPIOD->CR1 | GPIO_PIN_7;		//Pullup
 887  0110 721e5012      	bset	20498,#7
 888                     ; 103 		break;
 890  0114 2008          	jra	L773
 891  0116               L553:
 892                     ; 104 		case 2:
 892                     ; 105 		GPIOE->DDR = GPIOE->DDR & ~GPIO_PIN_7;	//Entree
 894  0116 721f5016      	bres	20502,#7
 895                     ; 106 		GPIOE->CR1 = GPIOE->CR1 | GPIO_PIN_7;		//Pullup
 897  011a 721e5017      	bset	20503,#7
 898                     ; 107 		break;
 900  011e               L773:
 901                     ; 109 }
 904  011e 81            	ret
 938                     ; 111 char BP_etat(char numero) {
 939                     	switch	.text
 940  011f               _BP_etat:
 944                     ; 112 	switch(numero) {
 947                     ; 117 		default:
 947                     ; 118 		return BP_INACTIF;
 948  011f 4a            	dec	a
 949  0120 2705          	jreq	L104
 950  0122 4a            	dec	a
 951  0123 2719          	jreq	L304
 952  0125               L504:
 955  0125 4f            	clr	a
 958  0126 81            	ret
 959  0127               L104:
 960                     ; 113 		case 1:
 960                     ; 114 		return (GPIOD->IDR | ~GPIO_PIN_7) == ~GPIO_PIN_7;
 962  0127 c65010        	ld	a,20496
 963  012a 5f            	clrw	x
 964  012b 97            	ld	xl,a
 965  012c 01            	rrwa	x,a
 966  012d aa7f          	or	a,#127
 967  012f 01            	rrwa	x,a
 968  0130 aaff          	or	a,#255
 969  0132 01            	rrwa	x,a
 970  0133 a3ff7f        	cpw	x,#65407
 971  0136 2604          	jrne	L06
 972  0138 a601          	ld	a,#1
 973  013a 2001          	jra	L26
 974  013c               L06:
 975  013c 4f            	clr	a
 976  013d               L26:
 979  013d 81            	ret
 980  013e               L304:
 981                     ; 115 		case 2:
 981                     ; 116 		return (GPIOE->IDR | ~GPIO_PIN_7) == ~GPIO_PIN_7;
 983  013e c65015        	ld	a,20501
 984  0141 5f            	clrw	x
 985  0142 97            	ld	xl,a
 986  0143 01            	rrwa	x,a
 987  0144 aa7f          	or	a,#127
 988  0146 01            	rrwa	x,a
 989  0147 aaff          	or	a,#255
 990  0149 01            	rrwa	x,a
 991  014a a3ff7f        	cpw	x,#65407
 992  014d 2604          	jrne	L46
 993  014f a601          	ld	a,#1
 994  0151 2001          	jra	L66
 995  0153               L46:
 996  0153 4f            	clr	a
 997  0154               L66:
1000  0154 81            	ret
1013                     	xdef	_BP_etat
1014                     	xdef	_BP_init
1015                     	xdef	_LEDV_etat
1016                     	xdef	_LEDV_init
1017                     	xdef	_convertBCD2String
1018                     	xdef	_convertBCD2TIL
1019                     	xdef	_PortC_IDR_filtre
1020                     	xdef	_PortC_init
1021                     	xdef	_TIL321_affiche
1022                     	xdef	_TIL321_init
1023                     	xdef	_UART2_RXNEFlag
1024                     	xdef	_UART2_Putstring
1025                     	xdef	_UART2_Putchar
1026                     	xdef	_UART2_GetChar
1027                     	xdef	_UART2_initITReceive
1028                     	xdef	_UART2_init
1029                     	xdef	_ITC_enableIT
1030                     	switch	.const
1031  001e               L713:
1032  001e 457272657572  	dc.b	"Erreur.",13
1033  0026 0a00          	dc.b	10,0
1034  0028               L762:
1035  0028 390d          	dc.b	"9",13
1036  002a 0a00          	dc.b	10,0
1037  002c               L562:
1038  002c 380d          	dc.b	"8",13
1039  002e 0a00          	dc.b	10,0
1040  0030               L362:
1041  0030 370d          	dc.b	"7",13
1042  0032 0a00          	dc.b	10,0
1043  0034               L162:
1044  0034 360d          	dc.b	"6",13
1045  0036 0a00          	dc.b	10,0
1046  0038               L752:
1047  0038 350d          	dc.b	"5",13
1048  003a 0a00          	dc.b	10,0
1049  003c               L552:
1050  003c 340d          	dc.b	"4",13
1051  003e 0a00          	dc.b	10,0
1052  0040               L352:
1053  0040 330d          	dc.b	"3",13
1054  0042 0a00          	dc.b	10,0
1055  0044               L152:
1056  0044 320d          	dc.b	"2",13
1057  0046 0a00          	dc.b	10,0
1058  0048               L742:
1059  0048 310d          	dc.b	"1",13
1060  004a 0a00          	dc.b	10,0
1061  004c               L542:
1062  004c 300d          	dc.b	"0",13
1063  004e 0a00          	dc.b	10,0
1064                     	xref.b	c_x
1084                     	xref	c_xymvx
1085                     	end
