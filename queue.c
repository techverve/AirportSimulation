
#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "header.h"



void initqueue(struct queue *pq)
{
    pq->count=0;
    pq->front=0;
    pq->rear=-1;
}

void addqueue(struct queue *pq, struct plane item)
{
    if(pq->count>=5)
    {
        printf( "\nQueue is full.\n");
        
    }
    (pq->count)++;

    pq->rear=(pq->rear+1)%5;
    pq->p[pq->rear]=item;
}

struct plane delqueue(struct queue *pq)
{
    struct plane p1;

    if(pq->count<=0)
    {
        printf("\nQueue is empty.\n");
        p1.plane_number=0;
        p1.tm=0;
    }
    else
    {
        (pq->count)--;
        p1=pq->p[pq->front];
        pq->front=(pq->front+1)%5;
    }
    return p1;
}

int size(struct queue q)
{
    return q.count;
}

int empty(struct queue q)
{
    return(q.count<= 0);
}

int full(struct queue q)
{
    return(q.count>=5);
}


void initairport(struct airport *ap)
{
    initqueue(&(ap->landing));
    initqueue(&(ap->takeoff));

    ap->pl=&(ap->landing);
    ap->pt=&(ap->takeoff);
    ap->nplanes=ap->nland=ap->ntakeoff=ap->nrefuse=0;
    ap->landwait=ap->takeoffwait=ap->idletime=0;
}

void start(int *endtime,double *expectarrive,double *expectdepart)
{
    int flag=0;
    char wish;

    
    printf("One plane can land or depart in each unit of time.\n" );
    printf("Up to %d planes can be waiting to land or take off at any time.\n",5);
    printf("How many units of time will the simulation run?");
    scanf("%d",endtime);
    myrandomize();/*initialize random number generation*/
    do
    {
        printf("\nExpected number of arrivals per unit time? ");
        scanf("%lf",expectarrive);
        printf("\nExpected number of departures per unit time? ");
        scanf("%lf",expectdepart);

        if(*expectarrive<0.0||*expectdepart<0.0)
        {
            printf("These numbers must be nonnegative.\n");
            flag=0;
        }
        else
        {
            if(*expectarrive+*expectdepart>1.0)
            {
                printf("The airport will become saturated. Read new numbers? ");
                fflush(stdin);
                scanf("%c",&wish);
                if(tolower(wish)=='y')
                    flag=0;
                else
                    flag=1;
            }
            else
                flag=1;
        }
    } while(flag==0);
}

void newplane(struct airport *ap,int curtime,int action)/*makes a record for a plane,updates nplanes*/
{
    (ap->nplanes)++;
    ap->pln.plane_number=ap->nplanes;
    ap->pln.tm=curtime;

    switch(action)
    {
        case ARRIVE:
            
            printf("\n    Plane %d ready to land.\n",ap->nplanes);
            break;

        case DEPART:
            printf("\n    Plane %d ready to take off.\n",ap->nplanes);
            break;
    }
}

void refuse(struct airport *ap, int action)/*processes a plane wanting to use runway but queue is full*/
{
    switch(action)
    {
        case ARRIVE:

             printf("    Plane  %d directed to another airport.\n",ap->pln.plane_number);
             break;

        case DEPART:

             printf("    Plane %d told to try later.\n",ap->pln.plane_number);
             break;
    }
    (ap->nrefuse)++;
}

void land(struct airport *ap,struct plane pl,int curtime)/*processes a plane p1 that is landing*/
{
    int wait;

    wait=curtime-pl.tm;
    printf("%d: Plane %d landed ",curtime,pl.plane_number);
    printf("In queue %d units \n",wait);
    (ap->nland)++;
    (ap->landwait)+=wait;
}

void fly(struct airport *ap,struct plane pl,int curtime)/*processes a plane p1 that is takingoff*/
{
    int wait;

    wait=curtime-pl.tm;
    printf("%d: Plane %d took off ",curtime,pl.plane_number);
    printf("In queue %d units \n",wait);
    (ap->ntakeoff)++;
    (ap->takeoffwait)+=wait;
}

void idle(struct airport *ap,int curtime)/*updates variables for a unittime when the runway is idle */
{
    printf("%d: Runway is idle.\n",curtime);
    ap->idletime++;
}

void conclude(struct airport *ap,int endtime)/*prints out statistics and conclude stimulation*/
{
    printf("Simulation has concluded after %d units.\n",endtime);
    printf("Total number of planes processed: %d\n",ap->nplanes);
    printf("Number of planes landed: %d\n",ap->nland);
    printf("Number of planes taken off: %d\n",ap->ntakeoff);
    printf("Number of planes refused use: %d\n",ap->nrefuse);
    printf("Number left ready to land: %d\n",queuesize(*ap,'l'));
    printf("Number left ready to take off: %d\n",queuesize(*ap,'t'));

    if(endtime>0)
        printf("Percentage of time runway idle: %lf \n",((double)ap->idletime/endtime)*100.0);

    if(ap->nland>0)
        printf("Average wait time to land: %lf \n",((double)ap->landwait/ap->nland));

    if(ap->ntakeoff>0)
        printf("Average wait time to take off: %lf \n",((double)ap->takeoffwait/ap->ntakeoff));
}

int randomnumber(double expectedvalue)
{
    int number=0;
    double em;
    double x;

    em=exp(-expectedvalue);
    x=rand()/(double)INT_MAX;

    while(x>em)
    {
        number++;
        x*=rand()/(double)INT_MAX;
    }

    return number;
}

void apaddqueue(struct airport *ap,char type)
{
    switch(tolower(type))
    {
        case 'l':
              addqueue(ap->pl,ap->pln);
              break;

        case 't':
              addqueue(ap->pt,ap->pln);
              break;
    }
}

struct plane apdelqueue(struct airport *ap,char type)
{
    struct plane p1;

    switch(tolower(type))
    {
        case 'l':
              p1=delqueue(ap->pl);
              break;

        case 't':
              p1=delqueue(ap->pl);
              break;
    }

    return p1;
}

int queuesize(struct airport ap,char type)
{
    switch(tolower(type))
    {
        case 'l':
              return(size(*(ap.pl)));

        case 't':
              return(size(*(ap.pt)));
    }

    return 0;
}

int queuefull(struct airport ap,char type)
{
    switch(tolower(type))
    {
        case 'l':
              return(full(*(ap.pl)));

        case 't':
              return(full(*(ap.pt)));
    }

    return 0;
}

int queueempty(struct airport ap,char type)
{
    switch(tolower(type))
    {
        case 'l':
              return(empty(*(ap.pl)));

        case 't':
              return(empty(*(ap.pt)));
    }

    return 0;
}

void myrandomize()/*set starting point for pseudo random integers*/
{
    srand((unsigned int)(time(NULL)%10000));
}

