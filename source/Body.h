#ifndef BODY_H
#define BODY_H

#include "Collider.h"
#include "Rigidbody.h"

struct Body {
	Rigidbody* rigidbody;
	Collider* collider;

	Body(Rigidbody* _rigidbody, Collider* _collider) :
		rigidbody(_rigidbody), collider(_collider) {

	}
};

#endif //BODY_H