#include "project.c"

int main(){
	int i=0;
		init();
		init_LCD();

		
		send_data_4bit(0x40); //set CGRAM 0x00		
		for(i=0; i<8; i++)
			write_data(0x11);

		send_data_4bit(0x80);		
		write_data('a');
		write_data('b');
		write_data('c');
		write_data(0x00);
				
		return 0;
}
