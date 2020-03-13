//Inspired by the Internetand your lectures
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
        return -1;
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
    bool operator== (const Vector3D& v3) const
    {
        return x == v3.x && y == v3.y && z == v3.z;
    };
    bool operator!= (const Vector3D& v3) const
    {
        return x != v3.x || y != v3.y || z != v3.z;
    };
    Vector3D operator+ (const Vector3D& v3) const
    {
        return Vector3D(x + v3.x, y + v3.y, z + v3.z);
    };
    int operator* (const Vector3D& v3)
    {
        return (x * v3.getX() + y * v3.getY() + z * v3.getZ());
    };
    Vector3D operator- (const Vector3D& v3) const
    {
        return Vector3D(x - v3.x, y - v3.y, z - v3.z);
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
ostream& operator<<(ostream& os, const Vector3D& v)
{
    os << "(" << v.getX() << "; " << v.getY() << "; " << v.getZ() << ")";
    return os;
};
istream& operator>>(istream& is, Vector3D& v)
{
    int x;
    int y;
    int z;

    is >> x >> y >> z;
    v.setX(x);
    v.setY(y);
    v.setZ(z);
    return is;
};





class Matrix3D {
protected:
    double data[9];
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

Matrix3D::Matrix3D() {
    for (int i = 0; i < 9; i++) {
        data[i] = 0;
    }
}

double Matrix3D::get(int i, int j) const {
    if ((i < 0) || (j < 0) || (i > 2) || (j > 2)) {
        return 0;
    }
    return data[(i * 3) + j];
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
    double* res = new double[9];
    for (int i = 0; i < 9; i++) {
        res[i] = data[i] + m1.data[i];
    }
    return Matrix3D(res);
}

Matrix3D Matrix3D::operator-(const Matrix3D& m1) const {
    return Matrix3D(m1 * (-1.0) + *this);
}

Matrix3D Matrix3D::operator*(const double& scale) const {
    double* res = new double[9];
    for (int i = 0; i < 9; i++) {
        res[i] = scale * data[i];
    }
    return Matrix3D(res);
}

Matrix3D Matrix3D::operator*(const Matrix3D& m1) const {
    double* res = new double[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[(i * 3) + j] = 0;
            for (int k = 0; k < 3; k++) {
                res[(i * 3) + j] += get(i, k) * m1.get(k, j);
            }
        }
    }
    return Matrix3D(res);
}

ostream& operator<<(std::ostream& os, const Matrix3D& m) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << m.get(i, j) << ", ";
        }
        cout << endl;
    }
    return os;
}

Vector3D operator*(const Matrix3D& m, const Vector3D& v) {
    Vector3D res;
    for (int i = 0; i < 3; i++) {
        double temp = 0;
        for (int j = 0; j < 3; j++) {
            temp += m.get(i, j) * v.get(j);
        }
        res.set(temp, i);
    }
    return res;
}
istream& operator>>(std::istream& is, Matrix3D& m) {
    double* data = new double[9];
    for (int i = 0; i < 9; i++)
    {
        is >> data[i];
    }
    m = Matrix3D(data);
    return is;
}

Matrix3D operator*(const double& scale, const Matrix3D& m) {
    return m * scale;
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