#include "Transform.h"
#include <rttr/registration>

using namespace rttr;
using namespace  rttr::detail;


RTTR_REGISTRATION//×¢²á·´Éä
{
    registration::class_<Transform>("Transform")
            .constructor<>()(policy::ctor::as_raw_ptr)
            .property("position", &Transform::position, &Transform::set_position)
            .property("rotation", &Transform::rotation, &Transform::set_rotation)
            .property("scale", &Transform::scale, &Transform::set_scale);
}

Transform::Transform() {

}

Transform::~Transform() {

}