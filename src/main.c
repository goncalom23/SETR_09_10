/*!
 * \file:   main.c
 * \author: Gonçalo Martins <goncalom23@ua.pt> and Filipe Silva <filipe.msilva@ua.pt>
 * 
 * \date May 15, 2023, 10:32 AM
 * \brief
 * SETR 22/23
 * 
 * 
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <string.h>
#include <console/console.h>
#include <stdio.h>
#include <stdint.h>

#include "button/button.h"

#define BROWSING_MOVIES 1
#define ADD_CREDIT 2
#define MOVIE_SELECTED 3
#define RETURN_CREDIT 4


char movie_name[5] = {'A','A','A','B','B'};
uint8_t movie_price[5] = {9,11,9,10,12};
uint8_t movie_session[5] = {19,21,23,19,21};

extern uint8_t button_state[8];
int credit = 0;
int select_movie = 0;
uint32_t timer_counter = 0;
char arrow [5][10];

/** \brief
 *  Processes the the chars received so far looking for commands 
 *	\return                                                     
 *	 0: if a valid command was found and executed           	
 * 	-1: if empty string found            						 
 * 	-2: if there is no valid command found                      
 * 	-3: if a CS error is detected (command not executed)         
 * 	-4: if string format is wrong 									
 *	-5: incomplete command found                             	 
 */ 
void change_arrow()
{
    for(int i = 0; i<5; i++)
    {
        if(i == select_movie)
        {
                strcpy(arrow[i],"->");
        }
        else
        {
                strcpy(arrow[i],"");
        }
    }     
}

/** \brief
 *  Processes the the chars received so far looking for commands 
 *	\return                                                     
 *	 0: if a valid command was found and executed           	
 * 	-1: if empty string found            						 
 * 	-2: if there is no valid command found                      
 * 	-3: if a CS error is detected (command not executed)         
 * 	-4: if string format is wrong 									
 *	-5: incomplete command found                             	 
 */ 
void print_interface()
{

    printf("\033[2J\033[H");                                // clear window code
    printf("\n CREDIT= %i",credit); 
    printf("\n"); 
    printf("\n%s Movie A, 19H00 session, 9 EUR",arrow[0]); 
    printf("\n%s Movie A, 21H00 session, 11 EUR",arrow[1]); 
    printf("\n%s Movie A, 23H00 session, 9 EUR",arrow[2]);
    printf("\n%s Movie B, 19H00 session, 10 EUR",arrow[3]);
    printf("\n%s Movie B, 21H00 session, 12 EUR",arrow[4]);
}

void print_button_state(){
    printf("\033[2J\033[H");   
	printf("\nButton 1: %i", button_state[0]);
	printf("\nButton 2: %i", button_state[1]);
	printf("\nButton 3: %i", button_state[2]);
	printf("\nButton 4: %i", button_state[3]);
	printf("\nButton 5: %i", button_state[4]);
	printf("\nButton 6: %i", button_state[5]);
	printf("\nButton 7: %i", button_state[6]);
	printf("\nButton 8: %i", button_state[7]);
}

/** \brief
 *  Processes the the chars received so far looking for commands 
 *	\return                                                     
 *	 0: if a valid command was found and executed           	
 * 	-1: if empty string found            						 
 * 	-2: if there is no valid command found                      
 * 	-3: if a CS error is detected (command not executed)         
 * 	-4: if string format is wrong 									
 *	-5: incomplete command found                             	 
 */ 
void main(void)
{   
    button_config();
    change_arrow();

    int state = BROWSING_MOVIES;        
    while (1)
    {
        k_msleep(10);
        timer_counter++;
        if(timer_counter == 50 && state == BROWSING_MOVIES)
        {
            print_interface();
			//print_button_state();
            timer_counter = 0;
        }
        switch(state)
        {
            case BROWSING_MOVIES:
            {
                if(button_state[4] == 1)                // Browse Up
                {
                    select_movie = select_movie - 1; 
                    change_arrow(); 
                    button_state[4] = 0;                    
                }
                else if(button_state[5] == 1)           // Browse Down
                {
                    select_movie = select_movie + 1;
                    change_arrow();     
                    button_state[5] = 0;                    
                }
                else if(button_state[0] == 1 || button_state[1] == 1 || button_state[2] == 1 || button_state[3] == 1)   // add credit
                {
                    state = ADD_CREDIT;
                } 
                else if(button_state[6] == 1)           // Select
                {
                    state = MOVIE_SELECTED;
                    button_state[6] = 0;                    
                }
                else if(button_state[7] == 1)           // Return credit
                {
                    state = RETURN_CREDIT;
                }
                
                if(select_movie < 0)                    // Rotacao entre o ultimo e primeiro filme
                {
                    select_movie = 4;
                    change_arrow();
                }
                if(select_movie > 4)
                {
                    select_movie = 0;
                    change_arrow();
                }

                break;
            }
            
            case ADD_CREDIT:
            {
                if(button_state[0] == 1)               // 1 EUR
                {
                    credit = credit + 1;
                    button_state[0] = 0;       
                }
                else if(button_state[1] == 1)           // 2 EUR
                {
                    credit = credit + 2;
                    button_state[1] = 0;                    
                }
                else if(button_state[2] == 1)           // 5 EUR
                {
                    credit = credit + 5;
                    button_state[2] = 0;                   
                }
                else if(button_state[3] == 1)           // 10 EUR
                {
                    credit = credit + 10;            
                    button_state[3] = 0;      
                }
                state = BROWSING_MOVIES;
                break;
            }
            
            case MOVIE_SELECTED:
            {
                printf("\033[2J\033[H");                // clear window code

                printf("\n Ticket for movie %c, session %uH00 issued",movie_name[select_movie],movie_session[select_movie]);
                if(movie_price[select_movie] > credit)
                {
                    printf("\n Not enought credit. Ticket not issued");                
                }
                else if(movie_price[select_movie] < credit)
                {
                    credit = credit-movie_price[select_movie];
                    printf("\n Remaining credit %i",credit);                
                }
                k_msleep(3000);
                state = BROWSING_MOVIES;
                break;
            }

            case RETURN_CREDIT:
            {
                if(button_state[7] == 1)                // Return credit
                {
                    credit = 0;   
                    printf("\033[2J\033[H");            // clear window code
                    printf("\n %i EUR return",credit);
                    k_msleep(3000);
                    button_state[7] = 0;      
                }
                state = BROWSING_MOVIES;
                break;
            }

            default:                                    //Error 
            break;
        }
    }   
 
}
