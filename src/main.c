#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>	// For gettimeofday()
#include <stddef.h>	// For NULL
#include <string.h> // For strcmp()
#include <time.h>	

#include "chip8.c"
// DELETED PLATFORM.H BECAUSE ITS IN CHIP8.C
#include "tests.c"

long currentMillis();

int main(int argc, char *argv[])
{

    tests();
    char * filename;
    int timed = 1;

    if(argc < 2)
    {
        printf("Usage: ./main fliename --timed/untimed\n");
        return 1;
    }
    else
    {
        filename = argv[1];
    }
    if(argc > 2)
    {
        char * proxy = argv[2];
        if(strcmp(proxy, "--timed")) timed = 0;
        if(strcmp(proxy, "--untimed")) timed = 1;
    }


    printf("%s, ",filename);

    chip8 CH8;

    // IF I TRY TO MAKE THE PROGRAM WORK WITH OTHER SYSTEMS I NEET TO MAKE SOME SETTINGS
    // but for now it is just set to default = 0
    CH8.emuset = 0;


    long time_since = 0;
    long time_sinceT = 0;
    long startT = 0;
    long start = 0;
    long end = 0;

    //starting the chip8 engine
    c8start(&CH8);

    //loadint form the rom file
    loadprog(&CH8,filename);

    startT = currentMillis();
    start = currentMillis();


    while(1 == 1)
    {

        // calculating delta
        end = currentMillis();

        // sum of time since last timer decrement for cycle
        time_since = end - start;
        // sum of time since last timer decrement for timer
        time_sinceT = end - startT;
        // timer frequency
        long T = 1000/60;

        // clock freq
        long C = 1;


        if(!timed)
        {
            cycle(&CH8);
        }else if(time_since > C)
        {
            cycle(&CH8);
            // set start after the decrement
            start = currentMillis();
        }
        
        // if sum is above the 1/60s
        if(time_sinceT > T)
        {
            // if above zero decrement
            if(CH8.delay_t > 0) CH8.delay_t--;
            if(CH8.sound_t > 0) CH8.sound_t--;
            
            // set start after the decrement
            startT = currentMillis();
        }
    
        // wait for the input (breaks the timer)
        //char a = getchar(); kupka
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