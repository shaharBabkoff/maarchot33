#ifndef __REACTOR_H__
#define __REACTOR_H__

typedef void (*reactorFunc) (int fd, void *reactor);

// creates new reactor and returns pointer to it
void * createtReactor ();

// adds fd to Reactor (for reading) ; returns 0 on success.
int addFdToReactor(void * reactor_instance, int fd, reactorFunc func);

// removes fd from reactor
int removeFdFromReactor(void * reactor_instance, int fd);

int startReactor (void * reactor_instance);

// stops reactor
int stopReactor(void * reactor_instance);


#endif