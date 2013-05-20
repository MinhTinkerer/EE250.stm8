   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  43                     ; 41 void TIM4_DeInit(void)
  43                     ; 42 {
  45                     	switch	.text
  46  0000               _TIM4_DeInit:
  50                     ; 43     TIM4->CR1 = TIM4_CR1_RESET_VALUE;
  52  0000 725f5340      	clr	21312
  53                     ; 44     TIM4->IER = TIM4_IER_RESET_VALUE;
  55  0004 725f5341      	clr	21313
  56                     ; 45     TIM4->CNTR = TIM4_CNTR_RESET_VALUE;
  58  0008 725f5344      	clr	21316
  59                     ; 46     TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
  61  000c 725f5345      	clr	21317
  62                     ; 47     TIM4->ARR = TIM4_ARR_RESET_VALUE;
  64  0010 35ff5346      	mov	21318,#255
  65                     ; 48     TIM4->SR1 = TIM4_SR1_RESET_VALUE;
  67  0014 725f5342      	clr	21314
  68                     ; 49 }
  71  0018 81            	ret
 177                     ; 57 void TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler, u8 TIM4_Period)
 177                     ; 58 {
 178                     	switch	.text
 179  0019               _TIM4_TimeBaseInit:
 183                     ; 60     assert_param(IS_TIM4_PRESCALER_OK(TIM4_Prescaler));
 185                     ; 62     TIM4->PSCR = (u8)(TIM4_Prescaler);
 187  0019 9e            	ld	a,xh
 188  001a c75345        	ld	21317,a
 189                     ; 64     TIM4->ARR = (u8)(TIM4_Period);
 191  001d 9f            	ld	a,xl
 192  001e c75346        	ld	21318,a
 193                     ; 65 }
 196  0021 81            	ret
 251                     ; 75 void TIM4_Cmd(FunctionalState NewState)
 251                     ; 76 {
 252                     	switch	.text
 253  0022               _TIM4_Cmd:
 257                     ; 78     assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 259                     ; 81     if (NewState != DISABLE)
 261  0022 4d            	tnz	a
 262  0023 2706          	jreq	L511
 263                     ; 83         TIM4->CR1 |= TIM4_CR1_CEN;
 265  0025 72105340      	bset	21312,#0
 267  0029 2004          	jra	L711
 268  002b               L511:
 269                     ; 87         TIM4->CR1 &= (u8)(~TIM4_CR1_CEN);
 271  002b 72115340      	bres	21312,#0
 272  002f               L711:
 273                     ; 89 }
 276  002f 81            	ret
 334                     ; 101 void TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState)
 334                     ; 102 {
 335                     	switch	.text
 336  0030               _TIM4_ITConfig:
 338  0030 89            	pushw	x
 339       00000000      OFST:	set	0
 342                     ; 104     assert_param(IS_TIM4_IT_OK(TIM4_IT));
 344                     ; 105     assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 346                     ; 107     if (NewState != DISABLE)
 348  0031 9f            	ld	a,xl
 349  0032 4d            	tnz	a
 350  0033 2709          	jreq	L151
 351                     ; 110         TIM4->IER |= (u8)TIM4_IT;
 353  0035 9e            	ld	a,xh
 354  0036 ca5341        	or	a,21313
 355  0039 c75341        	ld	21313,a
 357  003c 2009          	jra	L351
 358  003e               L151:
 359                     ; 115         TIM4->IER &= (u8)(~TIM4_IT);
 361  003e 7b01          	ld	a,(OFST+1,sp)
 362  0040 43            	cpl	a
 363  0041 c45341        	and	a,21313
 364  0044 c75341        	ld	21313,a
 365  0047               L351:
 366                     ; 117 }
 369  0047 85            	popw	x
 370  0048 81            	ret
 406                     ; 125 void TIM4_UpdateDisableConfig(FunctionalState NewState)
 406                     ; 126 {
 407                     	switch	.text
 408  0049               _TIM4_UpdateDisableConfig:
 412                     ; 128     assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 414                     ; 131     if (NewState != DISABLE)
 416  0049 4d            	tnz	a
 417  004a 2706          	jreq	L371
 418                     ; 133         TIM4->CR1 |= TIM4_CR1_UDIS;
 420  004c 72125340      	bset	21312,#1
 422  0050 2004          	jra	L571
 423  0052               L371:
 424                     ; 137         TIM4->CR1 &= (u8)(~TIM4_CR1_UDIS);
 426  0052 72135340      	bres	21312,#1
 427  0056               L571:
 428                     ; 139 }
 431  0056 81            	ret
 489                     ; 149 void TIM4_UpdateRequestConfig(TIM4_UpdateSource_TypeDef TIM4_UpdateSource)
 489                     ; 150 {
 490                     	switch	.text
 491  0057               _TIM4_UpdateRequestConfig:
 495                     ; 152     assert_param(IS_TIM4_UPDATE_SOURCE_OK(TIM4_UpdateSource));
 497                     ; 155     if (TIM4_UpdateSource != TIM4_UPDATESOURCE_GLOBAL)
 499  0057 4d            	tnz	a
 500  0058 2706          	jreq	L522
 501                     ; 157         TIM4->CR1 |= TIM4_CR1_URS;
 503  005a 72145340      	bset	21312,#2
 505  005e 2004          	jra	L722
 506  0060               L522:
 507                     ; 161         TIM4->CR1 &= (u8)(~TIM4_CR1_URS);
 509  0060 72155340      	bres	21312,#2
 510  0064               L722:
 511                     ; 163 }
 514  0064 81            	ret
 571                     ; 173 void TIM4_SelectOnePulseMode(TIM4_OPMode_TypeDef TIM4_OPMode)
 571                     ; 174 {
 572                     	switch	.text
 573  0065               _TIM4_SelectOnePulseMode:
 577                     ; 176     assert_param(IS_TIM4_OPM_MODE_OK(TIM4_OPMode));
 579                     ; 179     if (TIM4_OPMode != TIM4_OPMODE_REPETITIVE)
 581  0065 4d            	tnz	a
 582  0066 2706          	jreq	L752
 583                     ; 181         TIM4->CR1 |= TIM4_CR1_OPM;
 585  0068 72165340      	bset	21312,#3
 587  006c 2004          	jra	L162
 588  006e               L752:
 589                     ; 185         TIM4->CR1 &= (u8)(~TIM4_CR1_OPM);
 591  006e 72175340      	bres	21312,#3
 592  0072               L162:
 593                     ; 188 }
 596  0072 81            	ret
 664                     ; 210 void TIM4_PrescalerConfig(TIM4_Prescaler_TypeDef Prescaler, TIM4_PSCReloadMode_TypeDef TIM4_PSCReloadMode)
 664                     ; 211 {
 665                     	switch	.text
 666  0073               _TIM4_PrescalerConfig:
 670                     ; 213     assert_param(IS_TIM4_PRESCALER_RELOAD_OK(TIM4_PSCReloadMode));
 672                     ; 214     assert_param(IS_TIM4_PRESCALER_OK(Prescaler));
 674                     ; 217     TIM4->PSCR = (u8)Prescaler;
 676  0073 9e            	ld	a,xh
 677  0074 c75345        	ld	21317,a
 678                     ; 220     TIM4->EGR = (u8)TIM4_PSCReloadMode;
 680  0077 9f            	ld	a,xl
 681  0078 c75343        	ld	21315,a
 682                     ; 221 }
 685  007b 81            	ret
 721                     ; 229 void TIM4_ARRPreloadConfig(FunctionalState NewState)
 721                     ; 230 {
 722                     	switch	.text
 723  007c               _TIM4_ARRPreloadConfig:
 727                     ; 232     assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 729                     ; 235     if (NewState != DISABLE)
 731  007c 4d            	tnz	a
 732  007d 2706          	jreq	L333
 733                     ; 237         TIM4->CR1 |= TIM4_CR1_ARPE;
 735  007f 721e5340      	bset	21312,#7
 737  0083 2004          	jra	L533
 738  0085               L333:
 739                     ; 241         TIM4->CR1 &= (u8)(~TIM4_CR1_ARPE);
 741  0085 721f5340      	bres	21312,#7
 742  0089               L533:
 743                     ; 243 }
 746  0089 81            	ret
 795                     ; 252 void TIM4_GenerateEvent(TIM4_EventSource_TypeDef TIM4_EventSource)
 795                     ; 253 {
 796                     	switch	.text
 797  008a               _TIM4_GenerateEvent:
 801                     ; 255     assert_param(IS_TIM4_EVENT_SOURCE_OK(TIM4_EventSource));
 803                     ; 258     TIM4->EGR = (u8)(TIM4_EventSource);
 805  008a c75343        	ld	21315,a
 806                     ; 259 }
 809  008d 81            	ret
 843                     ; 268 void TIM4_SetCounter(u8 Counter)
 843                     ; 269 {
 844                     	switch	.text
 845  008e               _TIM4_SetCounter:
 849                     ; 271     TIM4->CNTR = (u8)(Counter);
 851  008e c75344        	ld	21316,a
 852                     ; 272 }
 855  0091 81            	ret
 889                     ; 281 void TIM4_SetAutoreload(u8 Autoreload)
 889                     ; 282 {
 890                     	switch	.text
 891  0092               _TIM4_SetAutoreload:
 895                     ; 284     TIM4->ARR = (u8)(Autoreload);
 897  0092 c75346        	ld	21318,a
 898                     ; 285 }
 901  0095 81            	ret
 924                     ; 293 u8 TIM4_GetCounter(void)
 924                     ; 294 {
 925                     	switch	.text
 926  0096               _TIM4_GetCounter:
 930                     ; 296     return (u8)(TIM4->CNTR);
 932  0096 c65344        	ld	a,21316
 935  0099 81            	ret
 959                     ; 305 TIM4_Prescaler_TypeDef TIM4_GetPrescaler(void)
 959                     ; 306 {
 960                     	switch	.text
 961  009a               _TIM4_GetPrescaler:
 965                     ; 308     return (TIM4_Prescaler_TypeDef)(TIM4->PSCR);
 967  009a c65345        	ld	a,21317
 970  009d 81            	ret
1039                     ; 318 FlagStatus TIM4_GetFlagStatus(TIM4_FLAG_TypeDef TIM4_FLAG)
1039                     ; 319 {
1040                     	switch	.text
1041  009e               _TIM4_GetFlagStatus:
1045                     ; 321     assert_param(IS_TIM4_GET_FLAG_OK(TIM4_FLAG));
1047                     ; 323     if ((TIM4->SR1 & TIM4_FLAG) != RESET )
1049  009e c45342        	and	a,21314
1050  00a1 2703          	jreq	L374
1051                     ; 325         return (FlagStatus)(SET);
1053  00a3 a601          	ld	a,#1
1056  00a5 81            	ret
1057  00a6               L374:
1058                     ; 329         return (FlagStatus)(RESET);
1060  00a6 4f            	clr	a
1063  00a7 81            	ret
1098                     ; 340 void TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG)
1098                     ; 341 {
1099                     	switch	.text
1100  00a8               _TIM4_ClearFlag:
1104                     ; 343     assert_param(IS_TIM4_GET_FLAG_OK(TIM4_FLAG));
1106                     ; 346     TIM4->SR1 = (u8)(~TIM4_FLAG);
1108  00a8 43            	cpl	a
1109  00a9 c75342        	ld	21314,a
1110                     ; 348 }
1113  00ac 81            	ret
1149                     ; 357 ITStatus TIM4_GetITStatus(TIM4_IT_TypeDef TIM4_IT)
1149                     ; 358 {
1150                     	switch	.text
1151  00ad               _TIM4_GetITStatus:
1153  00ad 88            	push	a
1154       00000000      OFST:	set	0
1157                     ; 360     assert_param(IS_TIM4_IT_OK(TIM4_IT));
1159                     ; 362     if (((TIM4->SR1 & TIM4_IT) != RESET ) && ((TIM4->IER & TIM4_IT) != RESET ))
1161  00ae c45342        	and	a,21314
1162  00b1 270c          	jreq	L335
1164  00b3 c65341        	ld	a,21313
1165  00b6 1501          	bcp	a,(OFST+1,sp)
1166  00b8 2705          	jreq	L335
1167                     ; 364         return (ITStatus)(SET);
1169  00ba a601          	ld	a,#1
1172  00bc 5b01          	addw	sp,#1
1173  00be 81            	ret
1174  00bf               L335:
1175                     ; 368         return (ITStatus)(RESET);
1177  00bf 4f            	clr	a
1180  00c0 5b01          	addw	sp,#1
1181  00c2 81            	ret
1217                     ; 379 void TIM4_ClearITPendingBit(TIM4_IT_TypeDef TIM4_IT)
1217                     ; 380 {
1218                     	switch	.text
1219  00c3               _TIM4_ClearITPendingBit:
1223                     ; 382     assert_param(IS_TIM4_IT_OK(TIM4_IT));
1225                     ; 385     TIM4->SR1 = (u8)(~TIM4_IT);
1227  00c3 43            	cpl	a
1228  00c4 c75342        	ld	21314,a
1229                     ; 386 }
1232  00c7 81            	ret
1245                     	xdef	_TIM4_ClearITPendingBit
1246                     	xdef	_TIM4_GetITStatus
1247                     	xdef	_TIM4_ClearFlag
1248                     	xdef	_TIM4_GetFlagStatus
1249                     	xdef	_TIM4_GetPrescaler
1250                     	xdef	_TIM4_GetCounter
1251                     	xdef	_TIM4_SetAutoreload
1252                     	xdef	_TIM4_SetCounter
1253                     	xdef	_TIM4_GenerateEvent
1254                     	xdef	_TIM4_ARRPreloadConfig
1255                     	xdef	_TIM4_PrescalerConfig
1256                     	xdef	_TIM4_SelectOnePulseMode
1257                     	xdef	_TIM4_UpdateRequestConfig
1258                     	xdef	_TIM4_UpdateDisableConfig
1259                     	xdef	_TIM4_ITConfig
1260                     	xdef	_TIM4_Cmd
1261                     	xdef	_TIM4_TimeBaseInit
1262                     	xdef	_TIM4_DeInit
1281                     	end
