#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "header.h"


int main()/*main function*/
{
    struct airport ap;/*structure ap of type airport*/
    int time;/*variable used to traverse from 1 to the random number generated */
    int pri;/*pseudo random integer,holds the random number generated which denoted the time */
    int curtime;/*time recorded at which the plane arrives*/
    int endtime;/*time recorded at which the plane takesoff or land*/
    double expectarrive,expectdepart;/*variable that holds the value expected arrival or departure per unit time*/
    struct plane temp;/*structure of type plane*/

    

    initairport(&ap);

    start(&endtime,&expectarrive,&expectdepart);

    for(curtime=1;curtime<=endtime;curtime++)
    {
        pri=randomnumber(expectarrive);

        for(time=1;time<=pri;time++)
        {
            newplane(&ap,curtime,ARRIVE);
            if(queuefull(ap,'l'))
                 refuse(&ap,ARRIVE);
            else
                apaddqueue(&ap,'l');
        }

        pri=randomnumber(expectdepart);
        for(time=1;time<=pri;time++)
        {
            newplane(&ap,curtime,DEPART);
            if(queuefull(ap,'t'))
               refuse(&ap,DEPART);
            else
               apaddqueue(&ap,'t');
        }

        if(!(queueempty(ap,'l')))
        {
            temp=apdelqueue(&ap,'l');
            land(&ap,temp,curtime);
        }
        else if(!(queueempty(ap,'t')))
            {
                temp=apdelqueue(&ap,'t');
                fly(&ap,temp,curtime);
            }
        else
                idle(&ap,curtime);
        
    }

    conclude(&ap,endtime);


}

