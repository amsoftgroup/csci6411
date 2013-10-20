/*
 * test.c
 *
 *  Created on: Oct 19, 2013
 *      Author: cos
 */
#include <stdlib.h>
#include <stdio.h>

void __lwt_start_test0(void){
	printf("hello world! (__lwt_start_test0)\n");
}

void __lwt_start_test1(int old){
	printf("hello world! (__lwt_start_test1, %i)\n", old);
}

void __lwt_start_test2(int i, int j){
	printf("hello world! (__lwt_start_test, %i %i)\n", i,j);
}

void __lwt_start_test3(int i, int j, int k){
	printf("hello world! (__lwt_start_test, %i %i %i)\n", i,j,k);
}

void __lwt_start_test4(int i, int j, int k, int l){
	printf("hello world! (__lwt_start_test, %i %i %i %i)\n", i,j,k,l);
}

void __lwt_start_test5(int i, int j, int k, int l, int m){
	printf("size __lwt_start_test5: %i %i %i %i %i\n", i, j, k, l, m);
}
