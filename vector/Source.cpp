//Inspired by the Internet and your lectures
//Implementation Vector3D and Matrix3D




#include <iostream>
#include <string>

using namespace std;

class Vector3D
{
public:
    Vector3D(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {
    }
    Vector3D() : Vector3D(0, 0, 0) {
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    int getZ() const {
        return z;
    }
    double get(int i) const
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
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }
    void setZ(int z) {
        this->z = z;
    }
    void set(double value, int i)
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
    bool operator== (const Vector3D& v) const
    {
        return x == v.x && y == v.y && z == v.z;
    };
    bool operator!= (const Vector3D& v) const
    {
        return x != v.x || y != v.y || z != v.z;
    };
    Vector3D operator+ (const Vector3D& v) const
    {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    };
    int operator* (const Vector3D& v)
    {
        return (x * v.getX() + y * v.getY() + z * v.getZ());
    };
    Vector3D operator- (const Vector3D& v) const
    {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    };
    Vector3D operator* (const int a) const
    {
        return Vector3D(a * x, a * y, a * z);
    };
protected:
    int x;
    int y;
    int z;
};
Vector3D operator* (int a, const Vector3D& v)
{
    return Vector3D(a * v.getX(), a * v.getY(), a * v.getZ());
}
ostream& operator<<(ostream& wh, const Vector3D& v)
{
    wh << "(" << v.getX() << "; " << v.getY() << "; " << v.getZ() << ")";
    return wh;
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





class Matrix3D {
public:
    Matrix3D(double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8);
    Matrix3D(double* data);
    Matrix3D();
    double get(int i, int j) const;
    void set(double value, int i, int j);
    double determinant() const;
    Matrix3D operator+(const Matrix3D& m1) const;
    Matrix3D operator-(const Matrix3D& m1) const;
    Matrix3D operator*(const Matrix3D& m1) const;
    Matrix3D operator*(const double& scale) const;
protected:
    double data[9];
};


Matrix3D::Matrix3D(double a0, double a1, double a2,
    double a3, double a4, double a5,
    double a6, double a7, double a8) {
    data[0] = a0;
    data[1] = a1;
    data[2] = a2;
    data[3] = a3;
    data[4] = a4;
    data[5] = a5;
    data[6] = a6;
    data[7] = a7;
    data[8] = a8;
}

Matrix3D::Matrix3D(double* data) {
    for (int i = 0; i < 9; i++) {
        this->data[i] = data[i];
    }
    delete[] data;
}


double Matrix3D::get(int i, int j) const {
    if ((i < 0) || (j < 0) || (i > 2) || (j > 2)) {
        return 0;
    }
    return data[(i * 3) + j];
}

Matrix3D::Matrix3D() {
    for (int i = 0; i < 9; i++) {
        data[i] = 0;
    }
}

void Matrix3D::set(double value, int i, int j) {
    data[(i * 3) + j] = value;
}

double Matrix3D::determinant() const {
    return data[0] * (data[4] * data[8] - data[5] * data[7])
        - data[1] * (data[3] * data[8] - data[5] * data[6])
        + data[2] * (data[3] * data[7] - data[4] * data[6]);
}

Matrix3D Matrix3D::operator+(const Matrix3D& m1) const {
    double* s = new double[9];
    for (int i = 0; i < 9; i++) {
        s[i] = data[i] + m1.data[i];
    }
    return Matrix3D(s);
}

Matrix3D Matrix3D::operator-(const Matrix3D& m1) const {
    return Matrix3D(m1 * (-1.0) + *this);
}

Matrix3D Matrix3D::operator*(const double& scale) const {
    double* s = new double[9];
    for (int i = 0; i < 9; i++) {
        s[i] = scale * data[i];
    }
    return Matrix3D(s);
}

Matrix3D Matrix3D::operator*(const Matrix3D& m1) const {
    double* s = new double[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            s[(i * 3) + j] = 0;
            for (int k = 0; k < 3; k++) {
                s[(i * 3) + j] += get(i, k) * m1.get(k, j);
            }
        }
    }
    return Matrix3D(s);
}

ostream& operator<<(std::ostream& wh, const Matrix3D& m) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << m.get(i, j) << ", ";
        }
        cout << endl;
    }
    return wh;
}

Vector3D operator*(const Matrix3D& matrix, const Vector3D& vector) {
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
istream& operator>>(std::istream& wh, Matrix3D& matrix) {
    double* data = new double[9];
    for (int i = 0; i < 9; i++)
    {
        wh >> data[i];
    }
    matrix = Matrix3D(data);
    return wh;
}

Matrix3D operator*(const double& scale, const Matrix3D& matrix) {
    return matrix * scale;
}

int main()
{
    // Вектор задан в коде
    Vector3D A(1, 2, 3);
    // Вектор читается из cin
    Vector3D B;
    cin >> B;

    // Базовые операции с векторами
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "A * 3 = " << A * 3 << endl;
    cout << "2 * B = " << 2 * B << endl;
    cout << "A + B = " << A + B << endl;
    cout << "A - B = " << A - B << endl;
    cout << "A * B = " << A * B << endl;

    Matrix3D C(1, 0, 0, 0, 1, 0, 0, 0, 1);
    // Матрица читается из cin
    Matrix3D D;
    cin >> D;

    // Базовые операции с матрицами
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "C * 3 = " << C * 3 << endl;
    cout << "2 * D = " << 2 * D << endl;
    cout << "C + D = " << C + D << endl;
    cout << "C - D = " << C - D << endl;
    cout << "C * D = " << C * D << endl;

    // Детерминант матрицы
    cout << "det(D) = " << D.determinant() << endl;

    // Умножение матрицы на вектор
    cout << "D * B = " << D * B << endl;

    return 0;
}