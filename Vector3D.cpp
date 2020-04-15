#include "Vector3D.h"





Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {
}
Vector3D::Vector3D()
{
    x = 0;
    y = 0;
    z = 0;
}
double Vector3D::getX() {
    return x;
}
double Vector3D::getY()  {
    return y;
}
double Vector3D::getZ()  {
    return z;
}
double Vector3D::get(int i) 
{
    switch (i) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
    return 0;
}
void Vector3D::setX(double x) {
    this->x = x;
}
void Vector3D::setY(double y) {
    this->y = y;
}
void Vector3D::setZ(double z) {
    this->z = z;
}
void Vector3D::set(double value, int i)
{
    switch (i) {
    case 0:
        x = value;
    case 1:
        y = value;
    case 2:
        z = value;
    }
}





bool Vector3D::operator== (const Vector3D& v) const
{
    return x == v.x && y == v.y && z == v.z;
};
bool Vector3D::operator!= (const Vector3D& v) const
{
    return x != v.x || y != v.y || z != v.z;
};
Vector3D Vector3D::operator+ (const Vector3D& v) const
{
    return Vector3D(x + v.x, y + v.y, z + v.z);
};

Vector3D Vector3D::operator- (const Vector3D& v) const
{
    return Vector3D(x - v.x, y - v.y, z - v.z);
};
Vector3D Vector3D::operator* (const int a) const
{
    return Vector3D(a * x, a * y, a * z);
};
int Vector3D::operator* ( Vector3D& v)
{
    return (x * v.getX() + y * v.getY() + z * v.getZ());
};


istream& operator>>(istream& mean, Vector3D& v)
{
    int x;
    int y;
    int z;

    mean >> x >> y >> z;
    v.setX(x);
    v.setY(y);
    v.setZ(z);
    return mean;
};


std::ostream& operator<<(ostream& wh,  Vector3D& v)
{
    wh << "(" << v.getX() << "; " << v.getY() << "; " << v.getZ() << ")";
    return wh;
};

Vector3D operator*(const Matrix3D& matrix,  Vector3D& vector) {
    Vector3D s;
    for (int i = 0; i < 3; i++) {
        double p = 0;
        for (int j = 0; j < 3; j++) {
            p += matrix.get(i, j) * vector.get(j);
        }
        s.set(p, i);
    }
    return s;
}

Vector3D operator*(const Matrix3D& m, const Vector3D& v);
std::istream& operator>>(istream& mean, Vector3D& v)
{
    int x;
    int y;
    int z;

    mean >> x >> y >> z;
    v.setX(x);
    v.setY(y);
    v.setZ(z);
    return mean;
};

Vector3D operator* (double a,  Vector3D& v)
{
    return Vector3D(a * v.getX(), a * v.getY(), a * v.getZ());
}
