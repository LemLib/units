#include "units/Vector2D.hpp"

namespace units {
class Pose : public V2Position {
    protected:
        Angle theta;
    public:
        Pose();

        Pose(V2Position v);

        Pose(V2Position v, Angle h);

        Pose(Length nx, Length ny, Angle nh);

        Angle getTheta();
};
} // namespace units