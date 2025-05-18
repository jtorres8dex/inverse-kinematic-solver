#ifndef JOINT_HPP
#define JOINT_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <Eigen/Dense>

// Forward declaration to avoid circular dependency
class Link;

enum class JointType {
    Revolute,
    Prismatic
};

struct JointConfig
{
    JointType type;
    double minQ;
    double maxQ;
    double minQdot;
    double maxQdot;
    double initialPosition;

    // Use pointers to avoid incomplete type error
    Link* parentLink;
    Link* childLink;
};

class Joint {
public:
    Joint(JointConfig cfg);

    virtual ~Joint() = default;

    // Accessors
    JointType getType() const;
    double getQ() const;
    double getQdot() const;
    double getMinQLimit() const;
    double getMaxQLimit() const;

    // Mutators
    virtual void setQ(double pos);
    virtual void setQdot(double vel);

    // Kinematic transformation
    virtual Eigen::Matrix4d getTransform() = 0;

protected:
    JointType type;
    double Q;
    double Qdot;
    double minQLimit;
    double maxQLimit;
    double minQdotLimit;
    double maxQdotLimit;
};

class RevoluteJoint : public Joint {
public:
    RevoluteJoint(JointConfig cfg);

    Eigen::Matrix4d getTransform();
};

class PrismaticJoint : public Joint {
public:
    PrismaticJoint(JointConfig cfg);

    Eigen::Matrix4d getTransform();
};

#endif // JOINT_HPP