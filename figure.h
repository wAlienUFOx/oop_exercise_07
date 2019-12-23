#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>
#include "point.h"

namespace figures{

    enum FigureType {
        rhombus,
        rectangle,
        trapeze
    };

    class Figure {
    public:
    virtual std::ostream& print(std::ostream& out) const = 0;
    virtual void Serialize(std::ofstream& os) const = 0;
    virtual void Deserialize(std::ifstream& is) = 0;
    ~Figure() = default;
    };


    class Rectangle : public Figure {
    public:
    point A , B, C, D;

    Rectangle(): A{0, 0}, B{0, 0}, C{0, 0}, D{0,0} {}

    explicit Rectangle(std::istream& is) {
        is >> A >> B >> C >> D;
        double a, b, c, d, d1, d2, ABC, BCD, CDA, DAB;
        a = sqrt((B.x- A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
        b = sqrt((C.x- B.x) * (C.x - B.x) + (C.y - B.y) * (C.y - B.y));
        c = sqrt((C.x- D.x) * (C.x - D.x) + (C.y - D.y) * (C.y - D.y));
        d = sqrt((D.x- A.x) * (D.x - A.x) + (D.y - A.y) * (D.y - A.y));
        d1 = sqrt((B.x- D.x) * (B.x - D.x) + (B.y - D.y) * (B.y - D.y));
        d2 = sqrt((C.x- A.x) * (C.x - A.x) + (C.y - A.y) * (C.y - A.y));
        ABC = (a * a + b * b - d2 * d2) / 2 * a * b;
        BCD = (b * b + c * c - d1 * d1) / 2 * b * c;
        CDA = (d * d + c * c - d2 * d2) / 2 * d * c;
        DAB = (a * a + d * d - d1 * d1) / 2 * a * d;
        if(ABC != BCD || ABC != CDA || ABC != DAB)
            throw std::logic_error("It`s not a rectangle");
        }
   
    std::ostream& print(std::ostream& os) const override {
        os << "rectangle: " <<  A << " " << B << " " << C << " " << D << std::endl;
        return os;
    }

    void Serialize(std::ofstream& os) const override {
        FigureType type = rectangle;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os << A.x << " " << A.y << " " << B.x << " " << B.y << " " << C.x << " " << C.y << " " << D.x << " " << A.y;
    }

    void Deserialize(std::ifstream& is) override {

        is >> A >> B >> C >> D;
    }

    };


    class Trapeze : public Figure {
    public:
    point A, B, C, D;

    Trapeze(): A{0, 0}, B{0, 0}, C{0, 0}, D{0,0} {}

    explicit Trapeze(std::istream& is){
        is >> A >> B >> C >> D;
        if((C.y - B.y) / (C.x - B.x) != (D.y - A.y) / (D.x - A.x))
            throw std::logic_error("It`s not a trapeze");
    }

    std::ostream& print(std::ostream& os) const override {
        os << "trapeze: " << A << " " << B << " " << C << " " << D << std::endl;
        return os;
    }

    void Serialize(std::ofstream& os) const override {
        FigureType type = trapeze;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os << A.x << " " << A.y << " " << B.x << " " << B.y << " " << C.x << " " << C.y << " " << D.x << " " << A.y;
    }

    void Deserialize(std::ifstream& is) override {
        is >> A >> B >> C >> D;
    }


    };


    class Rhombus : public Figure {
    public:
    point A, B, C, D;


    Rhombus(): A{0, 0}, B{0, 0}, C{0, 0}, D{0,0} {}

    explicit Rhombus(std::istream& is){
        is >> A >> B >> C >> D;
        double a, b, c, d;
        a = sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
        b = sqrt((C.x - B.x) * (C.x - B.x) + (C.y - B.y) * (C.y - B.y));
        c = sqrt((C.x - D.x) * (C.x - D.x) + (C.y - D.y) * (C.y - D.y));
        d = sqrt((D.x - A.x) * (D.x - A.x) + (D.y - A.y) * (D.y - A.y));
        if(a != b || a != c || a != d)
            throw std::logic_error("It`s not a rhombus");
    }

    std::ostream& print(std::ostream& os) const override {
         os << "rhombus: " << A << " " << B << " " << C << " " << D << std::endl;
        return os;
    }

    void Serialize(std::ofstream& os) const override {
        FigureType type = rhombus;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os << A.x << " " << A.y << " " << B.x << " " << B.y << " " << C.x << " " << C.y << " " << D.x << " " << A.y;
    }

    void Deserialize(std::ifstream& is) override {
        is >> A >> B >> C >> D;
    }

};

}

#endif
