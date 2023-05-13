#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <string.h>
#include <console/console.h>
#include <stdio.h>
#include <stdint.h>

#include "button/button.h"

#define IDLE 0
#define BROWSING_MOVIES 1
#define CREDIT_ADDED 2
#define MOVIE_SELECTED 3

extern uint8_t button_state[8];
int credit;
int select_movie;
char arrow [5][10];

void menu_movies(int select)
{
        for(int i = 0; i<5; i++)
        {
                if(i == select)
                {
                        strcpy(arrow[i],"->");
                }
                else
                {
                        strcpy(arrow[i],"");
                }
        }
    printf("\033[2J\033[H");                                // clear window code
    printf("\n CREDIT= %i",credit); 
    printf("\n"); 
    printf("\n%s Movie A, 19H00 session, 9 EUR",arrow[0]); 
    printf("\n%s Movie A, 21H00 session, 11 EUR",arrow[1]); 
    printf("\n%s Movie A, 23H00 session, 9 EUR",arrow[2]);
    printf("\n%s Movie B, 19H00 session, 10 EUR",arrow[3]);
    printf("\n%s Movie B, 21H00 session, 12 EUR",arrow[4]);
}

void main(void)
{   
        button_config();

        credit = 0;
	select_movie = 0;

        int state = BROWSING_MOVIES;        
        while (1)
        {
                
                k_msleep(400);
                //printf("\033[2J\033[H");                // clear window code
                //printk("button1: %i\n",button_state[0]);      
                //printk("button2: %i\n",button_state[1]);       
                //printk("button3: %i\n",button_state[2]);       
                //printk("button4: %i\n",button_state[3]);
                //printk("button5: %i\n",button_state[4]);      
                //printk("button6: %i\n",button_state[5]);       
                //printk("button7: %i\n",button_state[6]);       
                //printk("button8: %i\n",button_state[7]);       
                // 

                switch(state)
                {
                        case IDLE:
                        {
                                //printk("%i",button_state[0]);       
                                break;
                        }

                        case BROWSING_MOVIES:
                        {
                                menu_movies(select_movie);
                                break;
                        }
                        
                        case CREDIT_ADDED:
                        {

                                break;
                        }

                        case MOVIE_SELECTED:
                        {

                                break;
                        }

                        default:                /** Error */
                        break;
                }
        }   
 
}
