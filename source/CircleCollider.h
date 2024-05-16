#pragma once

#include "Collider.h"

class CircleCollider : public Collider 
{
public:
    float radius;

    CircleCollider(GameObject* gameObject, float _radius = 1, Transform offset = Transform());

private:
};
