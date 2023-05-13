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
                printk("%i\n",button_state[0]);      
                printk("%i\n",button_state[1]);       
                printk("%i\n",button_state[2]);       
                printk("%i\n",button_state[3]);       

                switch(state)
                {
                        case IDLE:
                        {
                                printk("%i",button_state[0]);       
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
