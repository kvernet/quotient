#include "quotient.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	quotient * q1 = quotient_create(2, 6);	
	quotient * q2 = quotient_create(5, 3);
	quotient * q3 = quotient_create(-1, 2);
	
	// print q1, q2 and q3
	q1->print(q1);
	q2->print(q2);
	q3->print(q3);
	
	// add q2 to q1 and print q1
	q1->add(&q1, q2);
	q1->print(q1);
	
	// add q1 to q3 and print q3
	q3->add(&q3, q1);
	q3->print(q3);
	
	/* free allocated memory */
	q1->free(&q1);
	q2->free(&q2);
	q3->free(&q3);
	
	return EXIT_SUCCESS;
}
