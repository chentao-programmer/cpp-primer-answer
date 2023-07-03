#ifndef GRAPHIC_H
#define GRAPHIC_H

#define PI 3.14

class Graphic
{
public:
    virtual double get_area() const = 0;
};

class Graphic3D : public Graphic
{
public:
    virtual double get_volumn() const = 0;
};

class circle : public Graphic
{
public:
    double get_area() const override;
    double get_radius() const { return radius; }
protected:
    double radius;
};

class rectangle : public Graphic
{
public:
    double get_length() const { return length; }
    double get_width() const { return width; }
    double get_area() const override;
protected:
    double width;
    double length;
};

class sphere : public Graphic3D
{
public:
    double get_area() const override;
    double get_volumn() const override;
protected:
    double radius;
};

class cone : public Graphic3D
{
public: 
    double get_area() const override;
    double get_volumn() const override;
protected:
    double radius;
    double busbar;
};

#endif