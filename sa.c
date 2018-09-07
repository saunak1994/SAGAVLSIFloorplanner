#include <math.h>
#include <string.h>
#include "annealing.h"			
#include "bool.h"

#include "fp.h"




void solution_count_update(FPTREE * solution, NET* net_arr, MODULE * module_arr)
{
	static solution_count ;
        solution_count = solution_count+1;
        if ((solution_count % PRINT_FREQUENCY) == 0)
		{
	                printf("%d %ld\n",solution_count,solution_cost(solution, net_arr, module_arr));
		}
}



void anneal(NET * net_arr, MODULE * module_arr ,int module_num){
	int i1, i2;				
	int i,j;				
	double temperature;			
	long current_value;			
	long start_value;			
	long initcost;
	int delta;				
	double merit, flip;			
	double exponent;			

	FPTREE * tempnodes[3 * OPERATOR_LIMIT];
//	double random_float();
	//double solution_cost();
	//double transition(); 

	temperature = INITIAL_TEMPERATURE;
	current_value = solution_cost(solution, net_arr, module_arr);
	initcost = current_value;

	for (i=1; i<=COOLING_STEPS; i++) {
		temperature *= COOLING_FRACTION;
		start_value = current_value;
		for (j=1; j<=STEPS_PER_TEMP; j++) {
			current_value = solution_cost(solution, net_arr, module_arr);
			fprintf(stderr, "current cost: %ld against start cost: %ld \n", current_value, initcost);
			int randint1 = random_int(0,module_num);
			if (j<=700){delta = operatorChange(net_arr,module_arr,randint1); fprintf(stderr,"randint1: %d\n",randint1);}
			if (j>700){delta = operandSwap(net_arr,module_arr,randint1); fprintf(stderr,"randint1: %d\n",randint1);}
			int type = (nodes[randint1]->operator == 0 ? 1 : 0);
			//delta = transition( net_arr, module_arr, randint1);
			fprintf(stderr, "delta: %d\n", delta);
			flip = rand()/(RAND_MAX - 1.0);//random_float(0.0,1.0);
			exponent = (-delta)/(K * temperature);
			merit = pow(E,exponent);
			/*printf("merit = %f  flip=%f  exponent=%f\n",merit,flip,exponent); */
			/*if (merit >= 1.0)
			merit = 0.0;*/ /* don't do unchanging swaps*/

			if(delta < 0) {	/*ACCEPT-WIN choose a better solution*/
				//current_value = current_value + delta;
				if (TRACE_OUTPUT) {
					fprintf(stderr, "swap WIN %d value %ld  temp=%f \n",
					delta, solution_cost(solution,net_arr, module_arr),temperature);
					fprintf(stderr, "\n\n");
				}
			}else{if(merit >= flip){ 		/*ACCEPT-LOSS choose a worse solution*/
				//current_value = current_value+delta;
				if (TRACE_OUTPUT) {
					fprintf(stderr, "swap LOSS %d value %ld merit=%f flip=%f\n",
					delta,solution_cost(solution,net_arr, module_arr) , merit, flip) ;
					fprintf(stderr, "\n\n") ;
				}
			}



			else{
				if(j<=700){if(nodes[i1]->operator == 'V' || nodes[i1]->operator == 'H')				//if node is operator
						{
						if(nodes[i1]->operator == 'H'){nodes[i1]->operator = 'V';}			//Change back operator
						else{if(nodes[i1]->operator == 'V'){nodes[i1]->operator = 'H';}}
					}
					solution = list2tree(nodes);
					iter_update_tree(solution);
					iter_update_module(0, 0, solution, module_arr);
					}
				if(j>700){FPTREE * temp;
						if(nodes[i1]->operator==0 && nodes[i1+1]->operator==0) 				//if node is an operand
						{
						temp = nodes[i1] ;								//change back operand
						nodes[i1] = nodes[i1 + 1] ;
						nodes[i1 + 1] = temp ;
						}
						solution = list2tree(nodes);
						iter_update_tree(solution);
						iter_update_module(0, 0, solution, module_arr);
				}
			}


	}
   }
}}



				/*

				else{ 				
					if(type == 0)
					{
						int i ;
						for(i = randint1; ; i--)
						{
							if(nodes[i] == NULL || nodes[i]->operator == 0)
							{
								break;
							}
							else{
								if(nodes[i]->operator == 'H'){
									nodes[i]->operator = 'V';}
								else{if(nodes[i]->operator == 'V'){
									nodes[i]->operator = 'H';}}
						             }
						}
						for(i = randint1; ; i++){
								if(nodes[i] == NULL || nodes[i]->operator == 0){
								break;}
								else{
									if(nodes[i]->operator == 'H'){
									nodes[i]->operator = 'V';}
									else{if(nodes[i]->operator == 'V'){
										nodes[i]->operator = 'H';
										}}
								}
							}
					}
					else{if(type == 1){
							FPTREE * temp ;
							temp = nodes[randint1] ;
							nodes[randint1] = nodes[randint1 + 1];
							nodes[randint1 + 1] = temp ;
							}}
					solution = list2tree(nodes);
					iter_update_tree(solution);
					iter_update_module(0, 0, solution, module_arr);
				}}

		solution_count_update(solution, net_arr, module_arr) ;
		}
		if((current_value-start_value) > 0.0){ // rerun at this temp 
			temperature /= COOLING_FRACTION;
			if (TRACE_OUTPUT) {printf("rerun at temperature %f\n",temperature);}
		}
	}
}
*/

