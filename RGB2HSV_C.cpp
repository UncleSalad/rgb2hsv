#include "RGB2HSV_C.h"
 namespace RGB_HSV_C {
    double mod (double input, double y)
    {
        double _input = input;
        while (_input > y) _input -= y;
        if (_input < y) return _input;
        else return 0;
    }
    double map(double val, double inStart, double inEnd, double outStart, double outEnd)
    {
        double coef = (outEnd - outStart)/(inEnd - inStart);
        return val *  coef;
    }
    double casb (double x) 
    {
        if (x < 0) return x * (-1);
        else return x;
    }
    double cconstrain (double x, double min, double max) 
    {
        if (x < min) return min;
        if (x > max) return max;
        if ((x > min) && (x < max)) return x;
    }
}
ColorRGB ColorBuffer;
void HSVtoRGB()
{
    RGB_HSV_C::cconstrain(ColorBuffer.h, 0, 360);
    RGB_HSV_C::cconstrain(ColorBuffer.s, 0, 100);
    RGB_HSV_C::cconstrain(ColorBuffer.v, 0, 100);
    double r1, g1, b1;
    double C = RGB_HSV_C::map(ColorBuffer.v, 0, 100, 0, 1) * RGB_HSV_C::map(ColorBuffer.s, 0, 100, 0, 1);
    double X = C *(1 - RGB_HSV_C::casb(RGB_HSV_C::mod((ColorBuffer.h/60.0), 2.0) - 1));
    double m = RGB_HSV_C::map(ColorBuffer.v, 0, 100, 0, 1) - C;
    if ((0 <= ColorBuffer.h) && (ColorBuffer.h < 60)) 
    {
        r1 = C;
        g1 = X;
        b1 = 0;
    }
    if ((60 <= ColorBuffer.h) && (ColorBuffer.h < 120)) 
    {
        r1 = X;
        g1 = C;
        b1 = 0;
    }
    if ((120 <= ColorBuffer.h) && (ColorBuffer.h < 180)) 
    {
        r1 = 0;
        g1 = C;
        b1 = X;
    }
    if ((180 <= ColorBuffer.h) && (ColorBuffer.h < 240)) 
    {
        r1 = 0;
        g1 = X;
        b1 = C;
    }
    if ((240 <= ColorBuffer.h) && (ColorBuffer.h < 300)) 
    {
        r1 = X;
        g1 = 0;
        b1 = C;
    }
    if ((300 <= ColorBuffer.h) && (ColorBuffer.h <= 360)) 
    {
        r1 = C;
        g1 = 0;
        b1 = X;
    }
    ColorBuffer.r = (r1 + m) * 255;
    ColorBuffer.g = (g1 + m) * 255;
    ColorBuffer.b = (b1 + m) * 255;
}
void RGBtoHSV() 
{
    double R = RGB_HSV_C::map(ColorBuffer.r, 0, 255, 0, 1);
    double G = RGB_HSV_C::map(ColorBuffer.g, 0, 255, 0, 1);
    double B = RGB_HSV_C::map(ColorBuffer.b, 0, 255, 0, 1);
    double Cmax = ((G) >= (B) ? \
                         ((R) >= (G) ? (R) : (G)) \
                     : \
                         ((R) >= (B) ? (R) : (B)));
    double Cmin = ((G) <= (B) ? \
                          ((R) <= (G) ? (R) : (G)) \
                      : \
                          ((R) <= (B) ? (R) : (B)));
    if (Cmax == Cmin) ColorBuffer.h = 360.0;
    if ((Cmax == R) && (G == B)) ColorBuffer.h == 0.0;
    if ((Cmax == R) && (G > B)) ColorBuffer.h = (60 * ((G - B)/(Cmax - Cmin))) + 0.0;
    if ((Cmax == R) && (G < B)) ColorBuffer.h = 60 * ((G - B)/(Cmax - Cmin)) + 360.0;
    if ((Cmax == G)) ColorBuffer.h = 60.0 * ((B - R)/(Cmax - Cmin)) + 120.0;
    if ((Cmax == B)) ColorBuffer.h = 60.0 * ((R - G)/(Cmax - Cmin)) + 240.0;

    if (Cmax == 0) ColorBuffer.s = 0;
    else ColorBuffer.s = 1 - (Cmin/Cmax);
    ColorBuffer.s = RGB_HSV_C::cconstrain(RGB_HSV_C::map(ColorBuffer.s, 0, 1, 0, 100), 0, 100);
    ColorBuffer.v = RGB_HSV_C::cconstrain(RGB_HSV_C::map(Cmax, 0, 1, 0, 100), 0, 100);
}
