     //
     //  Site
     //
     // http://extremeelectronics.co.in/avr-tutorials/4x3-matrix-keypad-interface-avr-tutorial/
     //
     //


#include "stm8s.h"                // file needed only for registers mask

#define LCD_PORT GPIOB
#define LCD_RS   GPIO_PIN_2
#define LCD_E    GPIO_PIN_3

//---------------------------------------------------------------------------------------
//Addresses of cursor position for 16x2 HD44780 LCD
//line1  80H  81H  82H  83H  84H  85H  86H  87H  88H  89H  8AH  8BH  8CH  8DH  8EH  8FH  
//line2  C0H  C1H  C2H  C3H  C4H  C5H  C6H  C7H  C8H  C9H  CAH  CBH  CCH  CDH  CEH  CFH  
//---------------------------------------------------------------------------------------

void DelayMS(int delay);
void initLCD(void);
void resetLCD(void);
void LCD_DATA(unsigned char data,unsigned char type);
void LCD_NYB(unsigned char nyb, char type);
void LCD_LINE(char line);
void LCD_STR(const unsigned char *text);
void LCD_CHR(u8);
u8   GetKeyPressed(void);

int main(void) 
{
    u8 key;
    u8 oldkey;

/**
    * LCD PORT initialization pin [2..7] push-pull out
    */
    GPIO_DeInit(LCD_PORT);
    GPIO_Init(LCD_PORT, GPIO_PIN_HNIB | GPIO_PIN_3 | GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
    
/**
    * KEYPAD PORT initialization
    * Port A pin[4,5,6] push-pull out, columns selection active LOW
    */
    GPIO_DeInit(GPIOA); 
    GPIO_Init(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);
    
/** 
    * Port E pin[0,1,2,3] pull up input, rows read in, 
    * NOTE: PE.2 and PE.3 DON'T HAVE INTERNAL PULL UP RESISTOR (see STM8S105xx datasheet)
    *    47 kOHm EXTERNAL RESISTORS REQUIRED
    */
    GPIO_DeInit(GPIOE);
    GPIO_Init(GPIOE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);

    // initialize the LCD
    initLCD();
    LCD_LINE(1);
    LCD_STR("Press a key:");
    
    oldkey = 255;
    LCD_LINE(2);

    while(1)
    {
        key = GetKeyPressed(); //Get the code of the key pressed
        if (key != oldkey) //new key has been pressed
        {
            if (key < 12) // a valid key is pressed
            {
                switch(key)
                {
                    case 9: // backspace (mode entry is "right after writing" so we need to cursor left twice)
                        LCD_DATA(0x10,0); 
                        LCD_CHR(32);
                        LCD_DATA(0x10,0); 
                    break;

                    case 11:
                        LCD_DATA(0x14,0); // cursor right
                    break;

                    default:
                        LCD_CHR(key + 48 + 1); // display keycode
                    break;
                }
                oldkey = key;
            }
            else // keypad has been released then wait for a new key pressed
            {
                oldkey = 255;
            }
        }
    }
}

u8 GetKeyPressed()
{
    u8 r, c, data;
    
    for(c=0; c<3; c++)
    {
        // First deactivate all coloumns
        GPIO_WriteHigh(GPIOA, GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4);
        // Then pull the coloumn low for selection
        GPIO_WriteLow(GPIOA, (GPIO_PIN_6 >> c) ); 

        for(r=0; r<4; r++)
        {
            data = GPIO_ReadInputData(GPIOE) & 0x0F;
            data &= (0x08 >> r);
            // Rows input pins have pull-up resistors so a negative logic is used
            if(!data)
            {
                return (r*3+c);
            }
        }
    }
    return 0xff;
}

void LCD_CHR(u8 val)
{
        LCD_DATA(val,1);
}

void LCD_STR(const unsigned char *text)
{
    while(*text)
    {
        LCD_DATA(*text++,1);
    }
}

void resetLCD(void)
{
    // Special procedure: "Initializing by instruction". See HD44780 lcd controller datasheet)
    
    GPIO_WriteLow(LCD_PORT, LCD_E); //clear enable
    GPIO_WriteLow(LCD_PORT, LCD_RS); //going to write command
    DelayMS(40); //delay more than 15 ms after power on
    LCD_NYB(0x03,0); // first init: lcd DB.4 = 1, DB.5 = 1
    DelayMS(10); // delay more then 4.1 ms
    LCD_NYB(0x03,0); // second init: lcd DB.4 =1, DB.5 = 1
    DelayMS(5); // delay more than 100 microsecs
    LCD_NYB(0x03,0); // third init: lcd DB.4 = 1, DB.5 = 1
    
    // lcd is inizialized (but the interface is still 8 bit long)
    LCD_NYB(0x02,0); // Set data width = 4 bit lcd DB.4 = 0, DB.5 = 1
    DelayMS(1);
}

void initLCD(void)
{
    resetLCD();
    LCD_DATA(0x28,0); //4 bit mode, 2 line and 5*8 font
    //LCD_DATA(0x0c,0); //c = 1100 Set display ON, cursor OFF
    //LCD_DATA(0x0e,0); //e = 1110 Set display ON, cursor ON type "_"
    //LCD_DATA(0x0d,0); //d = 1101 Set display ON, cursor ON type "solid" + BLINK
    LCD_DATA(0x0F,0); //f = 1111 Set display ON, cursor ON type "_" + "solid" + BLINK
    LCD_DATA(0x01,0); //clear display
    LCD_DATA(0x06,0); //entry mode set move cursor right after write
    LCD_DATA(0x80,0); //start writing upper left corner of the lcd
}

void LCD_DATA(unsigned char data,unsigned char type)
{
    DelayMS(5); //TEST LCD FOR BUSY
    LCD_NYB(data>>4, type); //WRITE THE UPPER NIBBLE
    LCD_NYB(data, type); //WRITE THE LOWER NIBBLE
}

void LCD_NYB(unsigned char nyb, char type)
{
    unsigned char temp;
    
    temp = (nyb<<4) & 0xF0;
    GPIO_Write(LCD_PORT, temp);
    if(type == 0)
    {
        GPIO_WriteLow(LCD_PORT, LCD_RS); //COMMAND MODE
    }
    else 
    {
        GPIO_WriteHigh(LCD_PORT, LCD_RS); //CHARACTER/DATA MODE
    }
    GPIO_WriteHigh(LCD_PORT, LCD_E); //ENABLE LCD DATA LINE
    DelayMS(1); //SMALL DELAY
    GPIO_WriteLow(LCD_PORT, LCD_E); //DISABLE LCD DATA LINE
}

void LCD_LINE(char line)
{
    switch(line)
    {
        case 0:
        case 1:
            LCD_DATA(0x80,0);
        break;
        case 2:
            LCD_DATA(0xC0,0);
        break;
    }
}

void DelayMS(int delay)
{
    int nCount = 0;
    while (delay != 0)
    {
        nCount = 100;
        while (nCount != 0)
     {
        nCount--;
     }
        delay--;
    }
}