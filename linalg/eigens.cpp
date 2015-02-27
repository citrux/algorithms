#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef vector<double> vec;
typedef vector<vec> mat;
struct eigen { double l; vec v; };

double operator * (vec a, vec b)
{
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i)
        res += a[i] * b[i];
    return res;
}

vec & operator *= (vec & a, double b)
{
    for (auto & i : a)
        i *= b;
    return a;
}

vec operator * (vec a, double b) { return a *= b; }

vec & operator /= (vec & a, double b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] /= b;
    return a;
}

vec operator / (vec a, double b) { return a /= b; }

vec operator * (mat a, vec b)
{
    vec res(b.size());
    for (size_t i = 0; i < a.size(); ++i)
        res[i] = a[i] * b;
    return res;
}

mat operator * (mat a, double b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] *= b;
    return a;
}

vec & operator -= (vec & a, vec b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] -= b[i];
    return a;
}

vec operator - (vec a, vec b)
{
    return a -= b;
}

mat operator - (mat a, mat b)
{
    for (size_t i = 0; i < a.size(); ++i)
        a[i] -= b[i];
    return a;
}

ostream & operator << (ostream &os, const vec &v)
{
    for(auto i : v)
        os << i << " ";
    return os;
}
double norm(vec a) {return sqrt(a * a);}

void orthogonalize(vec & a, mat vs) { for (auto v : vs) a -= v * (v * a); }

eigen maxEigenValue(mat A, mat O)
{
    double l = 0, l1 = 1, eps = 1e-6;
    vec x(A.size());
    // перебираем базисные вектора в поисках некомпланарного
    for (int i = 0; norm(x) < 10 * eps; ++i)
    {
        if(i)
            x[i-1] = 0;
        x[i] = 1;
        orthogonalize(x, O);
    }
    // берём ортогональный заданным векторам вектор и начинаем искать
    // максимальное из оставшихся собственных значений
    auto x1 = A * x;
    while(l1 - l > eps)
    {
        l = norm(x1) / norm(x);
        // нормировка, ятобы числа быстро не росли и точность не падала:
        x = x1 / norm(x1);
        x1 = A * x;
        // поиск ортогональной компоненты
        orthogonalize(x1, O);
        l1 = norm(x1) / norm(x);
    }
    if (x1 * x < 0 && l > 0)
        l = -l;
    x = x1 / norm(x1);
    return {l, x};
}

vector<eigen> getEigens(mat A)
{
    mat ev;
    vector<eigen> res;
    for (size_t i = 0; i < A.size(); ++i)
    {
        auto e = maxEigenValue(A, ev);
        ev.push_back(e.v);
        res.push_back(e);
    }
    return res;
}

int main()
{
    size_t n = 20;
    mat A(n);
    for (size_t i = 0; i < n; ++i)
    {
        A[i].assign(n, 0);
        for (size_t j = 0; j < n; ++j)
        {
            if (i == j)
                A[i][j] = 2;
            if (abs((int)i-(int)j) == 1)
                A[i][j] = -1;
        }
    }
    for (auto i : getEigens(A))
        cout << "l = " << i.l << ", v = " << i.v << endl << endl;

    freopen("res.dat", "w", stdout);

    for (size_t k = 0; k < n; ++k)
    {
        for (auto i : getEigens(A))
            cout << i.v[k] << " ";
        cout << endl;
    }
}
