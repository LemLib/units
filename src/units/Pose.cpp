#include "units/Pose.hpp"

namespace units {
Pose::Pose() : V2Position(), orientation(0.0) {}

Pose::Pose(V2Position v) : V2Position(v), orientation(0.0) {}

Pose::Pose(V2Position v, Angle orientation) : V2Position(v), orientation(orientation) {}

Pose::Pose(Length x, Length y, Angle orientation) : V2Position(x, y), orientation(orientation) {}

Angle Pose::getOrientation() { return orientation; }

void Pose::setOrientation(Angle orientation) { this->orientation = orientation; }

VelocityPose::VelocityPose() : V2Velocity(), angularVelocity(0.0) {}

VelocityPose::VelocityPose(V2Velocity v) : V2Velocity(v), angularVelocity(0.0) {}

VelocityPose::VelocityPose(V2Velocity v, AngularVelocity angularVelocity)
    : V2Velocity(v), angularVelocity(angularVelocity) {}

AngularVelocity VelocityPose::getAngularVelocity() { return angularVelocity; }

void VelocityPose::setAngularVelocity(AngularVelocity angularVelocity) { this->angularVelocity = angularVelocity; }

AccelerationPose::AccelerationPose() : V2Acceleration(), angularAcceleration(0.0) {}

AccelerationPose::AccelerationPose(V2Acceleration v) : V2Acceleration(v), angularAcceleration(0.0) {}

AccelerationPose::AccelerationPose(V2Acceleration v, AngularAcceleration angularAcceleration)
    : V2Acceleration(v), angularAcceleration(angularAcceleration) {}

AngularAcceleration AccelerationPose::getAngularAcceleration() { return angularAcceleration; }

void AccelerationPose::setAngularAcceleration(AngularAcceleration angularAcceleration) {
    this->angularAcceleration = angularAcceleration;
}
} // namespace units