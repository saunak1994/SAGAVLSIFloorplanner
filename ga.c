#include <math.h>
#include <string.h>
#include "annealing.h"			
#include "bool.h"

#include "fp.h"


#define N 1000

struct DeadSpace{
	int index;
	int value;
	int random;
	
};
typedef struct DeadSpace DEADSPACE;
DEADSPACE DS_arr[N];
DEADSPACE DS_arr2[N];
FPTREE * Solution[N];
FPTREE * Solution2[N];

void genetic(NET * net_arr, MODULE * module_arr, int module_num, int soln_area)
{
int i,j,m,l,x,y;
int module_area=0;
int deadspace=0;
int current_value,initcost,initcost2;
int delta,delta2;
int solnar,solnar2;
current_value = solution_cost(solution, net_arr, module_arr);
initcost = current_value;
initcost2=current_value;
int alpha = 10000;
while(alpha>0){
for (j=1; j<=N; j++) {
			module_area=0;			
			//current_value = solution_cost(solution, net_arr, module_arr);
			//fprintf(stderr, "current cost: %ld against start cost: %ld \n", current_value, initcost);
			int randint1 = random_int(0, (module_num*2)-4);
			delta = transition( net_arr, module_arr, randint1);
	                
			//fprintf(stderr, "delta: %d\n", delta);
			//printf("total modules: %d\n", module_num);

			/*for(i = 1; i <= module_num; i++){
			if(module_arr[i].x_width == 0){continue;}
			printf("[%d] x:%d y:%d w:%d h:%d pio:%s\n", i, module_arr[i].x_coordinate, module_arr[i].y_coordinate, 				module_arr[i].x_width, module_arr[i].y_width, module_arr[i].pio ? "yes" : "no");
			}*/
			
			//printf("Area of module 100: %d\n",module_arr[100].x_width*module_arr[100].y_width); 
			for(i=1; i<=module_num; i++)
			{
			if(module_arr[i].x_width == 0){continue;}
			module_area+=module_arr[i].x_width*module_arr[i].y_width;
			}
			//fprintf(stderr,"module area: %d\n",module_area);
			solnar=solution->width*solution->height;
			//fprintf(stderr,"soln area: %d \n", solnar);
			deadspace=(solnar-module_area);
			DS_arr[j].index=j;
			DS_arr[j].value=deadspace;
			DS_arr[j].random=randint1;
			Solution[j]=solution;
			//fprintf(stderr,"Solution[%d] Area: %d\n",j,Solution[j]->width*Solution[j]->height);
			//fprintf(stderr,"%d . Deadspace: %d against random: %d\n",DS_arr[j].index,DS_arr[j].value,DS_arr[j].random);
			}

int minDS=DS_arr[1].value;
int minDSrandom=DS_arr[1].random;
int minDSindex=1;
for(x=1;x<=N;x++){
	if (DS_arr[x].value<minDS){
	minDS=DS_arr[x].value;
	minDSrandom=DS_arr[x].random;
	minDSindex=DS_arr[x].index;}
	else {continue;}
}

	
for (m=1;m<=N;m++){
 
		module_area=0;
		if(m==minDSindex){continue;}
		//fprintf(stderr,"gnhgh\n");
		int randint2 = random_int(0, (module_num*2)-4);
		//fprintf(stderr,"%d\n",randint2);
		delta = transition( net_arr, module_arr, randint2);
		for(l=1; l<=module_num; l++)
		{
		if(module_arr[l].x_width == 0){continue;}
		module_area+=module_arr[l].x_width*module_arr[l].y_width;
		//fprintf(stderr,"ghgh\n");
		}
		//fprintf(stderr,"module area: %d\n",module_area);
		solnar=solution->width*solution->height;
		//fprintf(stderr,"soln area: %d \n", solnar);
		deadspace=(solnar-module_area);
		DS_arr2[m].index=m;
		DS_arr2[m].value=deadspace;
		DS_arr2[m].random=randint2;
		Solution2[m]=solution;
		//fprintf(stderr,"%d . Deadspace: %d against random: %d\n",DS_arr2[m].index,DS_arr2[m].value,DS_arr2[m].random);
	
		}
int minDS2=DS_arr2[m-1].value;
int minDSrandom2=DS_arr2[m-1].random;
//fprintf(stderr,"JHSJHF: %d %d",minDS2,minDSrandom2);
for(y=1;y<=N;y++){
	if(y==minDSindex){continue;}
	if (DS_arr2[y].value<minDS2){
	minDS2=DS_arr2[y].value;
	minDSrandom2=DS_arr2[y].random;}
	else {continue;}
}



fprintf(stderr,"Min deadspace: %d at random: %d at index: %d\n",minDS,minDSrandom,minDSindex);
fprintf(stderr,"Second Min deadspace: %d at random: %d\n",minDS2,minDSrandom2);

delta = crossoverTransition(net_arr, module_arr, minDSrandom, minDSrandom2);
current_value = solution_cost(solution, net_arr, module_arr);
if(current_value<initcost){initcost=current_value;}

alpha--;
}

fprintf(stderr,"Final cost: %d against Initial cost: %d\n",initcost,initcost2);	
}
