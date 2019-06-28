#pragma once

class IAnimator
{
public:
    virtual void Update() = 0;
    ~IAnimator() {}
};
