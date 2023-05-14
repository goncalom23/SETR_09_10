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

char movie_name[5] = {'A','A','A','B','B'};
uint8_t movie_price[5] = {9,11,9,10,12};
uint8_t movie_session[5] = {19,21,23,19,21};

extern uint8_t button_state[8];
int credit;
int select_movie;
uint32_t timer_counter = 0;
char arrow [5][10];


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


void main(void)
{   
        button_config();

        credit = 0;
	select_movie = 0;

        int state = BROWSING_MOVIES;        
        while (1)
        {
                k_msleep(10);
                timer_counter++;
                if(timer_counter == 10 && state == BROWSING_MOVIES)
                {
                        print_interface();
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

                                if(select_movie < 0)                    // Rotacao entre o ultimo e primeiro filme
                                {
                                        select_movie = 4;
                                }
                                if(select_movie > 4)
                                {
                                        select_movie = 0;
                                }

                                if(button_state[0] == 1 || button_state[1] == 1 || button_state[2] == 1 || button_state[3] == 1)
                                {
                                        state = ADD_CREDIT;
                                } 


                                if(button_state[6] == 1)                // Select
                                {
                                        state = MOVIE_SELECTED;
                                        button_state[6] = 0;                    
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
                                else if(button_state[7] == 1)           // Return
                                {
                                credit = 0;   
                                printf("\033[2J\033[H");                                // clear window code
                                printf("\n %i EUR return",credit);
                                k_msleep(1000);
                                button_state[7] = 0;      
                                }

                                state = BROWSING_MOVIES;
                                break;
                        }

                        case MOVIE_SELECTED:
                        {
                                printf("\033[2J\033[H");                                // clear window code
                                printf("\n Ticket for movie %c, session %uH00 issued",movie_name,movie_session);

                                if(movie_price[select_movie] > credit)
                                {
                                        printf("\n Not enought credit. Ticket not issued");                
                                }
                                else if(movie_price[select_movie] < credit)
                                {
                                        printf("\n Remaining credit %i",credit);                
                                }

                                k_msleep(1000);
                                state = BROWSING_MOVIES;
                                break;
                        }

                        default:                                        /** Error */
                        break;
                }
        }   
 
}
