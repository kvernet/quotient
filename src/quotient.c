#include "quotient.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct tquotient {
	quotient q;
	const bool reductible;
}tquotient;

static bool is_reductible(quotient * self_ptr);
static void reduct(quotient ** self_ptr);
static void qadd(quotient ** self_ptr, quotient * other);
static void qprint(quotient * q);
static void qfree(quotient ** self_ptr);

quotient * quotient_create(
	int numerator,
	int denominator
) {
	tquotient * tq = (tquotient*)malloc(sizeof(*tq));
	*(int*)(&tq->q.numerator) = numerator;
	*(int*)(&tq->q.denominator) = denominator;
	*(bool*)(&tq->reductible) = is_reductible(&tq->q);
	
	tq->q.is_reductible = &is_reductible;
	tq->q.reduct = &reduct;
	tq->q.add = &qadd;
	tq->q.print = &qprint;
	tq->q.free = &qfree;
	
	return &tq->q;
}

static int get_max(int a, int b);

static int get_ppmc(int a, int b) {
	int min = a;
	int max = get_max(a, b);
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

bool is_reductible(quotient * self_ptr) {
	const int a = self_ptr->numerator;
	const int b = self_ptr->denominator;
	const int ppmc = get_ppmc(a, b);
	return ppmc != a*b;
}

static int get_pgcd(int a, int b) {
	const int ppmc = get_ppmc(a, b);	
	return (a*b) / ppmc;
}

void reduct(quotient ** self_ptr) {
	const int a = (*self_ptr)->numerator;
	const int b = (*self_ptr)->denominator;
	
	const int pgcd = get_pgcd(a, b);
	*(int*)(&(*self_ptr)->numerator) /= pgcd;
	*(int*)(&(*self_ptr)->denominator) /= pgcd;
}

void qadd(quotient ** self_ptr, quotient * other) {
	// = a/b + c/d = (a*d + c*b)/(b*d)
	const int a = (*self_ptr)->numerator;
	const int b = (*self_ptr)->denominator;
	
	const int c = other->numerator;
	const int d = other->denominator;	
	
	*(int*)(&(*self_ptr)->numerator) = a*d + c*b;
	*(int*)(&(*self_ptr)->denominator) = d*b;
}

static void printq(quotient * q) {
	if(q->denominator == 1) {
		printf("%d", q->numerator);
	} else {
		printf("%d/%d", q->numerator, q->denominator);
	}
}

void qprint(quotient * q) {
	if(q->is_reductible(q)) {
		printf("quotient ");
		printq(q);
		printf(" is reducible\n");
		
		q->reduct(&q);
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

int get_max(int a, int b) {
	return a > b ? a : b;
}
