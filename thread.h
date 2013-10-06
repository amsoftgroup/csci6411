/*
 * thread
 *
 *  Created on: Oct 1, 2013
 *      Author: cos
 */

#ifndef THREAD_
#define THREAD_

typedef struct {
	int thread_id;
	void* next;
} lightweight_thread_struct;

typedef lightweight_thread_struct* lwt_t;

typedef void *(*lwt_fn_t)(void *);

lwt_t lwt_create(lwt_fn_t fn, void *data);
void *lwt_join(lwt_t);
void lwt_die(void *);
int lwt_yeild(lwt_t);
lwt_t lwt_current(void);
int lwt_id(lwt_t);



#endif /* THREAD_ */
