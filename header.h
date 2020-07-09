
#define ARRIVE 0
#define DEPART 1
struct plane
{
    int plane_number;/*identification number of airplane*/
    int tm;/*time of arrival of airplane in the queue*/
};

struct queue
{
    int count;/*number of airplanes in the queue*/
    int front;/*front end of the queue*/
    int rear;/*rear end of the queue*/
    struct plane p[5];/*total number of planes in the queue*/
};
struct airport
{
    struct queue landing;/*queue for landing*/
    struct queue takeoff;/*queue for takeoff*/
    struct queue *pl;/*A pointer to the landing planes in the queue */
    struct queue *pt;/*A pointer to plane sabout to takeoff in the queue*/
    int idletime;/*total amount of time runway has been idle*/
    int landwait;/*tottal amount of time waited to land*/
    int takeoffwait;/*total amounr of time waited to takeoff*/
    int nland;/*total number of planes landed*/
    int nplanes;/*tottal number of planes*/
    int nrefuse;/*total number of planes refused to land*/
    int ntakeoff;/*total number of planes taken off*/
    struct plane pln;/*structure pln that holds the details about plane number and arrival of time*/
};
void initqueue(struct queue*);/*function used to initiakise values of the queue*/
void addqueue(struct queue*,struct plane);/*function used to add a plane to the end of a queue*/
struct plane delqueue(struct queue *);/*structure of type plane used to remove planes from the end of queue after takeoff*/
int size(struct queue);/*returns size(length) of the queue*/
int empty(struct queue);/*returns if the queue is empty or not*/
int full(struct queue);/*returns if the queue is full or not*/
void initairport(struct airport *);/*function used to initialise landing and takeoff queues*/
void start(int *,double *,double *);/*function used to simulate the code and take necessary details from the suer*/
void newplane(struct airport *,int,int);/*makes a record for a plane,updates nplanes*/
void refuse(struct airport *,int);/*processes a plane wanting to use runway but queue is full*/
void land(struct airport *,struct plane,int);/*processes a plane  that is landing*/
void fly(struct airport *,struct plane,int);/*processes a plane p1 that is takingoff*/
void idle(struct airport *, int);/*the function calculates amount of time runway was idle*/
void conclude(struct airport *,int);/*function that displays all the processed details of the runway*/
int randomnumber(double);/*function returns a random used to generate number of arrivals or departures per unit time*/
void apaddqueue(struct airport *,char);/*function to add an airplane the end of queue*/
struct plane apdelqueue(struct airport *, char);/*a structure of type plane which deletes the plane takenoff*/
int queuesize(struct airport,char);/*function that holds the number of planes in the landing or takeoff queue*/
int queuefull(struct airport, char);/*function that calls the full function if the landing or takeoff queues are full */
int queueempty(struct airport, char);/*function that calls the empty function if the landing or takeoff queus are empty*/
void myrandomize();/*set starting point for pseudo random integers*/
