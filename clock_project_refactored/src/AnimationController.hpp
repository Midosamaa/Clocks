#ifndef ANIMATIONCONTROLLER_HPP
#define ANIMATIONCONTROLLER_HPP

#include "Clock.hpp"
#include <vector>

class AnimationController {
private:
    std::vector<Clock*> animatingClocks;
    float animationDuration;

public:
    AnimationController(float duration = 1.5f);
    void addClock(Clock& clock);
    void update();
};

#endif
