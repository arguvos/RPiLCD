#include <bcm2835.h>

#define LCD_RS  RPI_GPIO_P1_26
#define LCD_E   RPI_GPIO_P1_24
#define LCD_D4  RPI_GPIO_P1_22
#define LCD_D5  RPI_GPIO_P1_18
#define LCD_D6  RPI_GPIO_P1_16
#define LCD_D7  RPI_GPIO_P1_12

#define LCD_WIDTH 16
#define LCD_CHR 1
#define LCD_CMD 0

#define LCD_LINE_1 0x80 // LCD RAM address for the 1st line
#define LCD_LINE_2 0xC0 // LCD RAM address for the 2nd line 

#define DELAY 5

int init()
{
        //return 1 if bcm2835 is'nt initialization
        if (!bcm2835_init()){
                        return 1;
        }
        //set pin
        bcm2835_gpio_fsel(LCD_RS, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(LCD_E, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(LCD_D4, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(LCD_D5, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(LCD_D6, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(LCD_D7, BCM2835_GPIO_FSEL_OUTP);        
        turn_off_pin(1);
}


/* N-number of line; 0-1 line mode; 1-2 line mode
 * C-cursor; 0-off; 1-on
 * SH-entire shift; 0-off; 1-on
 */
void init_LCD(char N, char C, char SH)
{	
	//function set
	lcd_byte_8bit(0x20, LCD_CMD);	
	lcd_byte_8bit(0x20, LCD_CMD);
	if (N==1)
		lcd_byte_8bit(0xC0, LCD_CMD);
	else
		lcd_byte_8bit(0x40, LCD_CMD);
	delay(5);
	
	//display on/off
	lcd_byte_8bit(0x00, LCD_CMD);
	if (C==1)
		lcd_byte_8bit(0xF0, LCD_CMD);
	else
		lcd_byte_8bit(0xD0, LCD_CMD);
	delay(5);
	
	//desplay clear
	lcd_byte_8bit(0x00, LCD_CMD);
	lcd_byte_8bit(0x10, LCD_CMD);
	delay(5);
	
	//entry mode set
	lcd_byte_8bit(0x00, LCD_CMD);
	if (SH==1)
		lcd_byte_8bit(0x70, LCD_CMD);
	else
		lcd_byte_8bit(0x60, LCD_CMD);
	delay(5);
}

void turn_off_pin(char logicPIN)
{
        if (logicPIN==1)
        {
                bcm2835_gpio_write(LCD_RS, LOW);
                bcm2835_gpio_write(LCD_E, LOW);
        }
        bcm2835_gpio_write(LCD_D4, LOW);
        bcm2835_gpio_write(LCD_D5, LOW);
        bcm2835_gpio_write(LCD_D6, LOW);
        bcm2835_gpio_write(LCD_D7, LOW);
}

void lcd_byte_4bit(char data, char mode)
{
	if (mode==LCD_CHR)
			bcm2835_gpio_write(LCD_RS, HIGH);		
       
        if ((data&0x10)==0x10)
                bcm2835_gpio_write(LCD_D4, HIGH);
        if ((data&0x20)==0x20)
                bcm2835_gpio_write(LCD_D5, HIGH);
        if ((data&0x40)==0x40)
                bcm2835_gpio_write(LCD_D6, HIGH);
        if ((data&0x80)==0x80)
                bcm2835_gpio_write(LCD_D7, HIGH);            
        
        delay(DELAY);
        bcm2835_gpio_write(LCD_E, HIGH);
        bcm2835_gpio_write(LCD_E, LOW);
        delay(DELAY);
        
        turn_off_pin(0);        
        if ((data&0x01)==0x01)
                bcm2835_gpio_write(LCD_D4, HIGH);
        if ((data&0x02)==0x02)
                bcm2835_gpio_write(LCD_D5, HIGH);
        if ((data&0x04)==0x04)
                bcm2835_gpio_write(LCD_D6, HIGH);
        if ((data&0x08)==0x08)
                bcm2835_gpio_write(LCD_D7, HIGH);    
        
        delay(DELAY);        
        bcm2835_gpio_write(LCD_E, HIGH);
		bcm2835_gpio_write(LCD_E, LOW);
        delay(DELAY);
        
        turn_off_pin(1);
}

void lcd_byte_8bit(char data, char mode)
{		
	if (mode==LCD_CHR)
			bcm2835_gpio_write(LCD_RS, HIGH);		

	if ((data&0x10)==0x10)
		bcm2835_gpio_write(LCD_D4, HIGH);
	if ((data&0x20)==0x20)
		bcm2835_gpio_write(LCD_D5, HIGH);
	if ((data&0x40)==0x40)
		bcm2835_gpio_write(LCD_D6, HIGH);
	if ((data&0x80)==0x80)
		bcm2835_gpio_write(LCD_D7, HIGH);    
	delay(DELAY);
	
	bcm2835_gpio_write(LCD_E, HIGH);
	bcm2835_gpio_write(LCD_E, LOW);
	delay(DELAY);	
	
	turn_off_pin(1);
}
