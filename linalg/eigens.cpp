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

eigen maxEigenValue(mat A, mat O = {})
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
    size_t m = 20;
    double a = 5, b = 4;
    double hx = a / m, hx2 = hx * hx, hy = b / n, hy2 = hy * hy;

    mat A((n-1) * (m-1));
    for (size_t i = 0; i < (n-1) * (m-1); ++i)
    {
        A[i].assign((m-1) * (n-1), 0);
        A[i][i] = 2. / hx2 + 2 / hy2;
        if (i % (n-1))
            A[i][i-1] = -1. / hx2;
        if (i % (n-1) < n - 2)
            A[i][i+1] = -1. / hx2;
        if (i / (n-1))
            A[i][i-(n-1)] = -1. / hy2;
        if (i / (n-1) < m - 2)
            A[i][i+(n-1)] = -1. / hy2;
    }
    auto x = maxEigenValue(A);
    for (size_t i = 0; i < A.size(); ++i)
        A[i][i] -= x.l;

    mat vs = {};
    vec lambdas = {};

    // ищем 3 нижних гармоники
    auto e1 = maxEigenValue(A, vs);
    vs.push_back(e1.v);
    lambdas.push_back(e1.l + x.l);

    auto e2 = maxEigenValue(A, vs);
    vs.push_back(e2.v);
    lambdas.push_back(e2.l + x.l);

    auto e3 = maxEigenValue(A, vs);
    vs.push_back(e3.v);
    lambdas.push_back(e3.l + x.l);


    // выводим их в файлы
    auto f = fopen("1.dat", "w");

    fprintf(f, "# g^2 = %.6f\n", lambdas[0]);
    for (size_t i = 0; i <= m; ++i)
    {
        for (size_t j = 0; j <= n; ++j)
        {
            if (i == 0 || i == m || j == 0 || j == n)
                fprintf(f, "%f %f 0\n", i * hx, j * hy);
            else
                fprintf(f, "%f %f %f\n", i * hx, j * hy, vs[0][(i-1) * (n-1) + (j-1)]);
        }
        fprintf(f, "\n");
    }
    fclose(f);


    f = fopen("2.dat", "w");

    fprintf(f, "# g^2 = %.6f\n", lambdas[1]);
    for (size_t i = 0; i <= m; ++i)
    {
        for (size_t j = 0; j <= n; ++j)
        {
            if (i == 0 || i == m || j == 0 || j == n)
                fprintf(f, "%f %f 0\n", i * hx, j * hy);
            else
                fprintf(f, "%f %f %f\n", i * hx, j * hy, vs[1][(i-1) * (n-1) + (j-1)]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    f = fopen("3.dat", "w");

    fprintf(f, "# g^2 = %.6f\n", lambdas[2]);
    for (size_t i = 0; i <= m; ++i)
    {
        for (size_t j = 0; j <= n; ++j)
        {
            if (i == 0 || i == m || j == 0 || j == n)
                fprintf(f, "%f %f 0\n", i * hx, j * hy);
            else
                fprintf(f, "%f %f %f\n", i * hx, j * hy, vs[2][(i-1) * (n-1) + (j-1)]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

}
