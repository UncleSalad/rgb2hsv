#pragma once
    extern struct ColorRGB
    {
        double r;
        double g;
        double b;
        double h;
        double s;
        double v;
    }ColorBuffer;
    void HSVtoRGB();
    void RGBtoHSV();