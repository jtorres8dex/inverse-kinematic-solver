#include "Joint.hpp"



Joint::Joint(JointConfig cfg)
{
    type = cfg.type;
    minQLimit = cfg.minQ;
    maxQLimit = cfg.maxQ;
    minQdotLimit = cfg.minQdot;
    maxQdotLimit = cfg.maxQdot;
    Q = cfg.initialPosition;
    Qdot = 0.0;

}

JointType Joint::getType() const { return type; }

double Joint::getQ() const { return Q; }
double Joint::getQdot() const { return Qdot; }
double Joint::getMinQLimit() const { return minQLimit; }
double Joint::getMaxQLimit() const { return maxQLimit; }
// double Joint::getTransform() const { return Eigen::Matrix4d  } // Placeholder for transformation
void Joint::setQ(double pos) {
    if (pos < minQLimit || pos > maxQLimit) {
        std::cerr << "Q out of bounds!" << std::endl;
        return;
    }
    Q = pos;
}

void Joint::setQdot(double vel) {
    if (vel < minQdotLimit || vel > maxQdotLimit)
    {
        std::cerr << "Qdot out of bounds" << std::endl;
        return;
    }
    Qdot = vel;
}



// Revolute Joint
RevoluteJoint::RevoluteJoint(JointConfig cfg)
    : Joint(cfg)
{

}

Eigen::Matrix4d RevoluteJoint::getTransform(){
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
    double theta = Q;  // Assuming Q is the joint angle

    transform(0, 0) = cos(theta);
    transform(0, 1) = -sin(theta);
    transform(1, 0) = sin(theta);
    transform(1, 1) = cos(theta);
    return transform;
}

// Prismatic Joint
PrismaticJoint::PrismaticJoint(JointConfig cfg)
    : Joint(cfg)
{}

Eigen::Matrix4d PrismaticJoint::getTransform(){
    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
    double d = Q;  // Assuming Q is the joint displacement

    transform(0, 3) = d;
    return transform;
}