#include "quotient.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct tquotient {
	quotient q;
	const bool reducible;
}tquotient;

static bool is_reducible(quotient * self_ptr);
static void reduce(quotient ** self_ptr);
static void qadd(quotient ** self_ptr, quotient * other);
static void qprint(quotient * q);
static void qfree(quotient ** self_ptr);

static int get_pgcd(int a, int b);
static int get_ppmc(int a, int b);
static void set_reducible(quotient * q);

quotient * quotient_create(
	int numerator,
	int denominator
) {
	tquotient * tq = (tquotient*)malloc(sizeof(*tq));
	*(int*)(&tq->q.numerator) = numerator;
	*(int*)(&tq->q.denominator) = denominator;
	
	tq->q.is_reducible = &is_reducible;
	tq->q.reduce = &reduce;
	tq->q.add = &qadd;
	tq->q.print = &qprint;
	tq->q.free = &qfree;
	
	set_reducible(&tq->q);
	
	return &tq->q;
}

bool is_reducible(quotient * self_ptr) {
	tquotient * tq = (tquotient*)self_ptr;
	return tq->reducible;
}

void reduce(quotient ** self_ptr) {
	tquotient * tq = (tquotient*)(*self_ptr);
	
	const int a = tq->q.numerator;
	const int b = tq->q.denominator;
	
	const int pgcd = get_pgcd(a, b);
	*(int*)(&tq->q.numerator) /= pgcd;
	*(int*)(&tq->q.denominator) /= pgcd;
	
	set_reducible(&tq->q);
}

void qadd(quotient ** self_ptr, quotient * other) {
	// = a/b + c/d = (a*d + c*b)/(b*d)
	const int a = (*self_ptr)->numerator;
	const int b = (*self_ptr)->denominator;
	
	const int c = other->numerator;
	const int d = other->denominator;	
	
	*(int*)(&(*self_ptr)->numerator) = a*d + c*b;
	*(int*)(&(*self_ptr)->denominator) = d*b;
	
	set_reducible(*self_ptr);
}

static void printq(quotient * q) {
	if(q->denominator == 1) {
		printf("%d", q->numerator);
	} else {
		printf("%d/%d", q->numerator, q->denominator);
	}
}

void qprint(quotient * q) {
	if(q->is_reducible(q)) {
		printf("quotient ");
		printq(q);
		printf(" is reducible\n");
		
		q->reduce(&q);
		printf("after reducing, it becomes: ");
		printq(q);
		printf("\n");
	} else {
		printf("quotient ");
		printq(q);
		printf(" is NOT reducible\n");
	}
}

void qfree(quotient ** self_ptr) {
	if(*self_ptr == NULL) return;
	free(*self_ptr);
	self_ptr = NULL;
}

void set_reducible(quotient * q) {
	tquotient * tq = (tquotient*)q;
	
	const int numerator = tq->q.numerator;
	const int denominator = tq->q.denominator;
	
	const int ppmc = get_ppmc(numerator, denominator);	
	*(bool*)(&tq->reducible) = ppmc != numerator*denominator;
}

int get_ppmc(int a, int b) {
	int min = a;
	int max = a > b ? a : b;
	if(max == a) {
		min = b;
	}
	
	int i;
	for(i = 1; i < min; i++) {
		if((i*max) % min == 0) {
			return i*max;
		}
	}
	
	return a*b;
}

int get_pgcd(int a, int b) {
	const int ppmc = get_ppmc(a, b);	
	return (a*b) / ppmc;
}
