// C libraries
#include<stdio.h>
#include<string.h>

// Linux Headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int main(){

     int dots = 0;
     int i = 0;
     char Rx_char;
     char prev_Rx_char;
     FILE * text = fopen("file.txt", "w");

          /* Create new termios struct, 'o_tty' */
     struct termios o_tty;

          /* fill o_tty with 0*/
     memset (&o_tty, 0, sizeof o_tty);

          /* open the serial port device */
     int hSerial = open("/dev/ttyACM0", O_RDWR| O_NONBLOCK | O_NDELAY);      

          /* Check for errors. in case you see error 'Permission denied', you are not part of dial out group.
          solve it by command 'sudo adduser $USER dialout' and put your user name instead of $USER. Log out and back
          for changes to happen.*/
     if ( hSerial< 0) {
      printf("Error %i from open: %s\n", errno, strerror(errno));
     }

          /* Get the attributes for a terminal */
     int iRetVal = tcgetattr (hSerial , &o_tty);

          /* string to receive message */
     char chArrBuff [256];

          /* pre-fill receive string with nulls. do you know why?  */
     memset (&chArrBuff , 0, sizeof(chArrBuff) );


     while(dots < 9){

          read(hSerial, &Rx_char, 1);
          if (prev_Rx_char == 46){
               fgets(chArrBuff, sizeof(chArrBuff),stdin);
               fprintf(text, "%s", chArrBuff);
               dots++;
               printf("%s", chArrBuff);
               memset (&chArrBuf , 0, sizeof(chArrBuff));
               i = 0;
          } 
          chArrBuff[i] = Rx_char;
          i++;
          prev_Rx_char = Rx_char;

     }     

     /* close the serial communication  */
     close(hSerial);
        
     fclose(text);

     return 0;
}

