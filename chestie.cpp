#include <math.h>

class Vector2 {

protected:

double x;

double y;

//...
public:
Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}
double norma() const {
    return sqrt(x * x + y * y); // norma euclidiana
}

double operator*(Vector2& other) {
    return this->x * other.x + this->y + other.y;
}

Vector2 operator*(double& other) {
    return Vector2(this->x * other, this->y * other);
}

};

class Vector3 : public Vector2 {
protected: 
    double z;
public:
    double norma() const {
        return sqrt(x * x + y * y + z * z);
    }
};

class Vector2_5 : public Vector2 {
protected:
    double w;
public:
    double operator*(Vector2_5& other) {
        return this->x * other.x + this->y + other.y + this->w * other.w;
    }
};

class Vector4 : public Vector3, public Vector2_5 {
public:
    double operator*(Vector4& other) {
        return this->Vector3::x * other.Vector3::x + this->Vector3::y + other.Vector3::y + this->w * other.w + this->z * other.z;
    }
};