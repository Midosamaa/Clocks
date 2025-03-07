#include "AnimationController.hpp"

AnimationController::AnimationController(float duration) : animationDuration(duration) {}

void AnimationController::addClock(Clock& clock) {
    clock.startAnimation(animationDuration);
    animatingClocks.push_back(&clock);
}

void AnimationController::update() {
    for (auto it = animatingClocks.begin(); it != animatingClocks.end();) {
        if ((*it)->isAnimating()) {
            (*it)->update();
            ++it;
        } else {
            it = animatingClocks.erase(it);
        }
    }
}
