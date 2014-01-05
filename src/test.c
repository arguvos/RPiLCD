#include "project.c"

int main(){
		init();
		setposition(0xC0);
		writechar('a');
		writechar('b');
		writechar('c');
		return 0;
}
