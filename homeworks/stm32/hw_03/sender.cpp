// C libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Linux Headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int main(int argc, char * argv[]){

	char buff[255];
	char ch;
	int i = 0;
	/* Create new termios struct, 'o_tty' */

	struct termios o_tty;
	
	/* fill o_tty with 0*/
	memset (&o_tty, 0, sizeof(o_tty));
	memset (&buff, 0, sizeof (buff));
	// printf(">> %d", o_tty.c_cflag.CSTOPB);
	/* setting up baudrate
	Set in/out baud rate to be 115200 
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);*/ 
	if (argc < 2){
    
    		printf("Input_Error\n");
    		
	} else {
		FILE * text = fopen(argv[1], "r");
			/* open the serial port device */
		int hSerial = open("/dev/ttyACM0", O_RDWR| O_NONBLOCK | O_NDELAY);	


		/* Check for errors. in case you see error 'Permission denied', you are not part of dial out group.
		solve it by command 'sudo adduser $USER dialout' and put your user name instead of $USER. Log out and back
		for changes to happen.*/
		if(hSerial< 0) {
			printf("Error %i from open: %s\n", errno, strerror(errno));
		}
		
		
		while((ch = getc(text)) != EOF){
			
			if(ch != 46){
				
				buff[i] = ch;
				i++;
				
			} else {
				
				buff[i] = ch;
				printf("%s", buff);
				for(int j = 0; j <= i; j++){
					write(hSerial, &buff[j], 1);
					usleep(1000);
				}

				memset(buff, 0, 255);
				i = 0;
			
			}
		}


			//char n_written = write(hSerial, &buff[i], sizeof(ch));
			//usleep(10);

		
		/* Get the attributes for a terminal */
		//int iRetVal = tcgetattr (hSerial , &o_tty);

		/* message we want to send to NUCLEO */
		//unsigned char chArrCmd[] = {'l', 'e', 'd', '1', '\0'};

		
		//printf("sending %s\n",chArrCmd);
		/* send message */
		//int n_written = write( hSerial, chArrCmd, sizeof(chArrCmd)-1 ); 

		//printf("n_written returns %d\n",n_written);
		     //while(1){;}
		/* close the serial communication  */
		close(hSerial);
		
		fclose(text);
		
	}
	
	return 0;
}
