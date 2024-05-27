#include "units/Pose.hpp"

namespace units {
Pose::Pose() : V2Position(), theta(0.0) {}

Pose::Pose(V2Position v) : V2Position(v), theta(0.0) {}

Pose::Pose(V2Position v, Angle h) : V2Position(v), theta(0.0) {}

Pose::Pose(Length nx, Length ny, Angle nh) : V2Position(nx, ny), theta(nh) {}

Angle Pose::getTheta() { return theta; }
} // namespace units