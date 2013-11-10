/*
 * test.c
 *
 *  Created on: Oct 19, 2013
 *      Author: cos
 */
#include <stdlib.h>
#include <stdio.h>

void __lwt_start_test0(void){
	printf("*******__lwt_start_test0)\n");
}

void __lwt_start_test1(unsigned int i){
	//params->a
	printf("*******__lwt_start_test1, executed thread %i)\n", i);
}

void __lwt_start_test2(unsigned int i, unsigned int j){
	printf("__lwt_start_test, %i %i)\n", i,j);
}

void __lwt_start_test3(unsigned int i, unsigned int j, unsigned int k){
	printf("*** __lwt_start_test,%i %i %i)\n", i,j,k);
}

void __lwt_start_test4(unsigned int i, unsigned int j, unsigned int k, unsigned int l){
	printf("__lwt_start_test,%i %i %i %i)\n", i,j,k,l);
}

void __lwt_start_test5(unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m){
	printf("__lwt_start_test5: %i %i %i %i %i\n", i, j, k, l, m);
}
