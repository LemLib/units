#include "units/Vector2D.hpp"

namespace units {
class Pose : public V2Position {
    protected:
        Angle theta;
    public:
        Pose() : V2Position(), theta(0.0) {}

        Pose(V2Position v) : V2Position(v), theta(0.0) {}

        Pose(V2Position v, Angle h) : V2Position(v), theta(0.0) {}

        Pose(Length nx, Length ny, Angle nh) : V2Position(nx, ny), theta(nh) {}

        Angle getTheta() { return theta; }
};
} // namespace units