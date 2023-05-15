/*!
 * \file:   main.c
 * \author: Gonçalo Martins <goncalom23@ua.pt> and Filipe Silva <filipe.msilva@ua.pt>
 * 
 * \date May 15, 2023, 10:32 AM
 * \brief
 * SETR 22/23, Assignment 3

 * Application that emulates an automated ticket vending machine for movies. 
 * The vending machine accepts a subset of coins and bills and
 * allows the user to browse a list to select the movie and session, eventually returning the remaining
 * credit. The inputs are push-buttons and the output is done via UART/Terminal (which emulates a
 * screen).
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

/* Defenitions for funciton returns */
#define EXIT_SUCESSFUL 0                                    // Function worked as suposed     
#define STATE_MACHINE_ERROR 1                               // State machine used a state not suposed to                                                            

/* State machine - state defenitions */
#define BROWSING_MOVIES 1                                   // State machine state when user is browsing movies
#define ADD_CREDIT 2                                        // State machine state when user is adding credit
#define MOVIE_SELECTED 3                                    // State machine state when user is selecting a movie
#define RETURN_CREDIT 4                                     // State machine state when user is returning credit

char movie_name[5] = {'A','A','A','B','B'};                 // Array containing the names of the movies in the movie list by order
uint8_t movie_price[5] = {9,11,9,10,12};                    // Array containing the prices of the movies in the movie list by order
uint8_t movie_session[5] = {19,21,23,19,21};                // Array containing the sessions hours of the movies in the movie list by order

extern uint8_t button_state[8];                             
int credit = 0;                                             // User available credit
int select_movie = 0;                                       // Number of the movie to be selected by the user
uint32_t timer_counter = 0;                                 // Counter to track time, used to minimize prints
char arrow [5][10];                                         // String array to display an arrow showing the user which movie he is pointing to chose

/** \brief
 *  function to update the string array that contains one arrow pointing to the movie beeing selected by the user   
 *  \return                                                     
 *  0: if success                 	 
 */ 
int change_arrow()
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
    return EXIT_SUCESSFUL; 
}

/** \brief
 *  print interface shown by default while user is browsing movies or adding credit                      	 
 *  \return                                                     
 *  0: if success                 	 
 */ 
int print_interface()
{
    printf("\033[2J\033[H");                                // clear window code
    printf("\n CREDIT= %i",credit); 
    printf("\n"); 
    printf("\n%s Movie A, 19H00 session, 9 EUR",arrow[0]); 
    printf("\n%s Movie A, 21H00 session, 11 EUR",arrow[1]); 
    printf("\n%s Movie A, 23H00 session, 9 EUR",arrow[2]);
    printf("\n%s Movie B, 19H00 session, 10 EUR",arrow[3]);
    printf("\n%s Movie B, 21H00 session, 12 EUR",arrow[4]);
    return EXIT_SUCESSFUL; 
}

/** \brief
 *  print interface to check if button states are changing correctly                          	 
 *  \return                                                     
 *  0: if success                 	 
 */ 
int print_button_state(){
    printf("\033[2J\033[H");   
	printf("\nButton 1: %i", button_state[0]);
	printf("\nButton 2: %i", button_state[1]);
	printf("\nButton 3: %i", button_state[2]);
	printf("\nButton 4: %i", button_state[3]);
	printf("\nButton 5: %i", button_state[4]);
	printf("\nButton 6: %i", button_state[5]);
	printf("\nButton 7: %i", button_state[6]);
	printf("\nButton 8: %i", button_state[7]);
    return EXIT_SUCESSFUL; 
}

/** \brief
 *  main function with a state machine that emulates an automated ticket vending machine for movies                        	 
 *  \return                                                     
 *  0: if success   
 *  1: if state machine got into a invalid state              	 
 */ 
int main(void)
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
                //k_msleep(3000);
                if(button_state[4] == 1)                // Browse down button used to return to browsing movies
                {
                    state = BROWSING_MOVIES;
                }
                break;
            }

            case RETURN_CREDIT:
            {
                if(button_state[7] == 1)                // Return credit
                {
                    credit = 0;   
                    printf("\033[2J\033[H");            // clear window code
                    printf("\n %i EUR return",credit);
                    button_state[7] = 0;      
                }

                //k_msleep(3000);
                if(button_state[4] == 1)                // Browse down button used to return to browsing movies
                {
                    state = BROWSING_MOVIES;
                }
                break;
            }

            default:                                    
                return STATE_MACHINE_ERROR;             // Error, the state machine should never get into this state
            break;
        }
    }
    return EXIT_SUCESSFUL;    
}
