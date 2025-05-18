#include "Joint.hpp"
#include <iostream>

// config
const double minQLimit = -10.0;
const double maxQLimit = 10.0;
const double minQdotLimit = -10.0;
const double maxQdotLimit = 10.0;

int main() {
    // Create a revolute joint
    // RevoluteJoint revolute(-M_PI, M_PI);
    // revolute.setQ(M_PI / 4);
    // std::cout << "Revolute Joint Q: " << revolute.getQ() << std::endl;
    // std::cout << "Revolute Joint Transformation:\n" << revolute.getTransform() << std::endl;

    // // Create a prismatic joint
    // PrismaticJoint prismatic(0.0, 2.0);
    // prismatic.setQ(1.5);
    // std::cout << "Prismatic Joint Q: " << prismatic.getQ() << std::endl;
    // std::cout << "Prismatic Joint Transformation:\n" << prismatic.getTransform() << std::endl;

    return 0;
}