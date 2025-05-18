#ifndef LINK_HPP
#define LINK_HPP

// Forward declaration to avoid circular dependency
class Joint;

struct LinkConfig
{
    double length;
    Joint* parentJoint;
    Joint* childJoint;
};

class Link
{
public:
    // Constructor
    Link(const LinkConfig& cfg);

    // Accessors
    double getLength() const;
    void setLength(double len);

    Joint* getParentJoint() const;
    Joint* getChildJoint() const;

private:
    double length;
    Joint* parentJoint;
    Joint* childJoint;
};

#endif // LINK_HPP