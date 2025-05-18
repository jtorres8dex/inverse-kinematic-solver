#include "Link.hpp"

// Constructor definition
Link::Link(const LinkConfig& cfg)
    : length(cfg.length), parentJoint(cfg.parentJoint), childJoint(cfg.childJoint) {}

// Accessor method definitions
double Link::getLength() const {
    return length;
}

void Link::setLength(double len) {
    length = len;
}

Joint* Link::getParentJoint() const {
    return parentJoint;
}

Joint* Link::getChildJoint() const {
    return childJoint;
}