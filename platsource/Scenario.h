#pragma once
#include <vector>

namespace smite {
    struct ScenarioFrame {
        int hp;
        int elapsedMs;
    };

    class Scenario {
    private:
        std::vector<ScenarioFrame> frames;
    public:
        Scenario();
        const std::vector<ScenarioFrame>& getFrames() const;
    };

}