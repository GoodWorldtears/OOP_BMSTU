#pragma once

struct DrawPoint
{
    double x {0.0};
    double y {0.0};
};

class BaseDrawer
{
public:
    virtual ~BaseDrawer() = default;
    virtual void clear() = 0;
    virtual void drawLine(const DrawPoint &start, const DrawPoint &end) = 0;
};
