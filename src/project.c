#include <bcm2835.h>

#define LCD_RS  RPI_GPIO_P1_26
#define LCD_E   RPI_GPIO_P1_24
#define LCD_D4  RPI_GPIO_P1_22
#define LCD_D5  RPI_GPIO_P1_18
#define LCD_D6  RPI_GPIO_P1_16
#define LCD_D7  RPI_GPIO_P1_12

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
	return 0;
}

//Set DDRAM address
void setposition(char data)
{	
	bcm2835_gpio_write(LCD_RS, LOW);
	delay(1);
	
	bcm2835_gpio_write(LCD_D4, LOW);
	bcm2835_gpio_write(LCD_D5, LOW);
	bcm2835_gpio_write(LCD_D6, LOW);
	bcm2835_gpio_write(LCD_D7, LOW);
	if ((data&0x10)==0x10)
		bcm2835_gpio_write(LCD_D4, HIGH);
	if ((data&0x20)==0x20)
		bcm2835_gpio_write(LCD_D5, HIGH);
	if ((data&0x40)==0x40)
		bcm2835_gpio_write(LCD_D6, HIGH);
	if ((data&0x80)==0x80)
		bcm2835_gpio_write(LCD_D7, HIGH);    
	delay(1);
	
	bcm2835_gpio_write(LCD_E, HIGH);
	bcm2835_gpio_write(LCD_E, LOW);
	delay(1);
	
	bcm2835_gpio_write(LCD_D4, LOW);
	bcm2835_gpio_write(LCD_D5, LOW);
	bcm2835_gpio_write(LCD_D6, LOW);
	bcm2835_gpio_write(LCD_D7, LOW);
	if ((data&0x01)==0x01)
		bcm2835_gpio_write(LCD_D4, HIGH);
	if ((data&0x02)==0x02)
		bcm2835_gpio_write(LCD_D5, HIGH);
	if ((data&0x04)==0x04)
		bcm2835_gpio_write(LCD_D6, HIGH);
	if ((data&0x08)==0x08)
		bcm2835_gpio_write(LCD_D7, HIGH);    
	delay(1);
	
	bcm2835_gpio_write(LCD_E, HIGH);
	bcm2835_gpio_write(LCD_E, LOW);
	delay(1);
	
	bcm2835_gpio_write(LCD_D4, HIGH);
	bcm2835_gpio_write(LCD_D5, HIGH);
	bcm2835_gpio_write(LCD_D6, HIGH);
	bcm2835_gpio_write(LCD_D7, HIGH);
	delay(1);  
}

//Write data to RAM
void writechar(char data)
{
	bcm2835_gpio_write(LCD_RS, HIGH);
	delay(1);
	
	bcm2835_gpio_write(LCD_D4, LOW);
	bcm2835_gpio_write(LCD_D5, LOW);
	bcm2835_gpio_write(LCD_D6, LOW);
	bcm2835_gpio_write(LCD_D7, LOW);
	if ((data&0x10)==0x10)
		bcm2835_gpio_write(LCD_D4, HIGH);
	if ((data&0x20)==0x20)
		bcm2835_gpio_write(LCD_D5, HIGH);
	if ((data&0x40)==0x40)
		bcm2835_gpio_write(LCD_D6, HIGH);
	if ((data&0x80)==0x80)
		bcm2835_gpio_write(LCD_D7, HIGH);    
	delay(1);
	
	bcm2835_gpio_write(LCD_E, HIGH);
	bcm2835_gpio_write(LCD_E, LOW);
	delay(1);
	
	bcm2835_gpio_write(LCD_D4, LOW);
	bcm2835_gpio_write(LCD_D5, LOW);
	bcm2835_gpio_write(LCD_D6, LOW);
	bcm2835_gpio_write(LCD_D7, LOW);
	if ((data&0x01)==0x01)
		bcm2835_gpio_write(LCD_D4, HIGH);
	if ((data&0x02)==0x02)
		bcm2835_gpio_write(LCD_D5, HIGH);
	if ((data&0x04)==0x04)
		bcm2835_gpio_write(LCD_D6, HIGH);
	if ((data&0x08)==0x08)
		bcm2835_gpio_write(LCD_D7, HIGH);    
	delay(1);
	
	bcm2835_gpio_write(LCD_E, HIGH);
	bcm2835_gpio_write(LCD_E, LOW);
	delay(1);
	
	bcm2835_gpio_write(LCD_D4, HIGH);
	bcm2835_gpio_write(LCD_D5, HIGH);
	bcm2835_gpio_write(LCD_D6, HIGH);
	bcm2835_gpio_write(LCD_D7, HIGH);
	delay(1);
}
