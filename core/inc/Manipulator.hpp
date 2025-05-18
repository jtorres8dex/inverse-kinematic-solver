#ifndef MANIPULATOR_HPP 
#define MANIPULATOR_HPP

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <memory>


#include "Joint.hpp"
#include "Link.hpp"

/* */


struct Composition
{
    std::vector<Joint*> joints;
    std::vector<Link*> links;
};
struct ManipulatorConfig
{
    Composition composition;
    Eigen::Matrix4d baseFrame;

};

#endif // MANIPULATOR_HPP

