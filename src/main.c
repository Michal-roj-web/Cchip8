#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>	// For gettimeofday()
#include <stddef.h>	// For NULL
#include <time.h>	

#include "chip-8.h"
#include "platform.h"

long currentMillis();

int main(int argc, char *argv[])
{

    char * filename;

    if(argc < 2)
    {
        printf("Usage: ./main fliename\n");
        return 1;
    }
    else
    {
        filename = argv[1];
    }


    printf("%s, ",filename);

    chip8 CH8;

    // IF I TRY TO MAKE THE PROGRAM WORK WITH OTHER SYSTEMS I NEET TO MAKE SOME SETTINGS
    // but for now it is just set to default = 0
    CH8.emuset = 0;

    long time_since = 0;
    long start = 0;
    long end = 0;

    //starting the chip8 engine
    c8start(&CH8);

    //loadint form the rom file
    loadprog(&CH8,filename);

    start = currentMillis();


    while(1 == 1)
    {

        cycle(&CH8);

        // calculating delta
        end = currentMillis();

        // sum of time since last timer decrement
        time_since = end - start;
        long T = 1000/60;

        // if sum is above the 1/60s
        if(time_since > T)
        {
            // if above zero decrement
            if(CH8.delay_t > 0) CH8.delay_t--;
            if(CH8.sound_t > 0) CH8.sound_t--;
            
            // set start after the decrement
            start = currentMillis();
        }
    
        // wait for the input (breaks the timer)
        //char a = getchar();
        //if(a == 'q')
        //{
        //    exit(0);
        //}
    }

    
    printf("0x%x\n", CH8.PC);

}


long currentMillis() {
	struct timeval tp;

	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
	// Convert the seconds to milliseconds by multiplying by 1000
	// Convert the microseconds to milliseconds by dividing by 1000
}
//g++ *.c -o pico8