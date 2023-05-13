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

void main(void)
{   
        button_config();

        int state = IDLE;        
        while (1) 
        {
                
                k_msleep(100);
                printf("\033[2J\033[H");                // clear window code
                printk("button1: %i\n",button_state[0]);      
                printk("button2: %i\n",button_state[1]);       
                printk("button3: %i\n",button_state[2]);       
                printk("button4: %i\n",button_state[3]);
                printk("button5: %i\n",button_state[4]);      
                printk("button6: %i\n",button_state[5]);       
                printk("button7: %i\n",button_state[6]);       
                printk("button8: %i\n",button_state[7]);       
                 

                switch(state)
                {
                        case IDLE:
                        {
                                //printk("%i",button_state[0]);       
                                break;
                        }

                        case BROWSING_MOVIES:
                        {

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
