#pragma once
#include <functional>
#include <vector>

class InputEvent {
public:
    using Callback = std::function<void()>;

    void subscribe(Callback callback) {
        callbacks.push_back(callback);
    }

    void trigger() {
        for (auto& callback : callbacks) {
            callback();
        }
    }

private:
    std::vector<Callback> callbacks;
};
