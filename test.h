/*
 * test.h
 *
 *  Created on: Oct 19, 2013
 *      Author: cos
 */

#ifndef TEST_H_
#define TEST_H_

/*
 * test.c
 *
 *  Created on: Oct 19, 2013
 *      Author: cos
 */
#include <stdlib.h>
#include <stdio.h>

struct thd_params_t {
	int a;
	int b;
} thd_params_t;

void __lwt_call_test0(struct thd_params_t *args_in);

void __lwt_call_test1(struct thd_params_t *args_in);

void __lwt_start_test0(void);

void __lwt_start_test1(unsigned int i);

/*
void __lwt_start_test2(unsigned int i, unsigned int j);

void __lwt_start_test3(unsigned int i, unsigned int j, unsigned int k);

void __lwt_start_test4(unsigned int i, unsigned int j, unsigned int k, unsigned int l);

void __lwt_start_test5(unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m);

void __lwt_start_test6(unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n);

void __lwt_start_test7(unsigned int i, unsigned int j, unsigned int k, unsigned int l, unsigned int m, unsigned int n, unsigned int o);
*/

#endif /* TEST_H_ */
