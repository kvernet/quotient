#ifndef QUOTIENT_H
#define QUOTIENT_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct quotient quotient;

struct quotient {
	const int numerator;
	const int denominator;
	
	bool (*is_reductible)(quotient * self_ptr);
	
	void (*reduct)(quotient ** self_ptr);
	
	void (*add)(quotient ** self_ptr, quotient * other);
	
	void (*print)(quotient * self_ptr);
		
	void (*free)(quotient ** self_ptr);
};

quotient * quotient_create(
	int numerator,
	int denominator
);

#ifdef __cplusplus
}
#endif

#endif
