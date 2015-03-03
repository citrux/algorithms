#include "eigens.hpp"

int main()
{
    size_t n = 30;
    size_t m = 30;
    double a = 5, b = 4;
    double hx = a / m, hx2 = hx * hx, hy = b / n, hy2 = hy * hy;

    smat A((n+1) * (m+1));
    for (size_t i = 0; i <= m; ++i)
        for (size_t j = 0; j <= n; ++j)
        {
            auto ind = i * (n+1) + j;
            A[ind].emplace_back(ind, 2. / hx2 + 2 / hy2);
            if (j > 0 && j < n)
            {
                A[ind].emplace_back(ind-1, -1. / hy2);
                A[ind].emplace_back(ind+1, -1. / hy2);
            }
            if (j == 0)
                A[ind].emplace_back(ind+1, -2. / hy2);
            if (j == n)
                A[ind].emplace_back(ind-1, -2. / hy2);

            if (i > 0 && i < m)
            {
                A[ind].emplace_back(ind-n-1, -1. / hx2);
                A[ind].emplace_back(ind+n+1, -1. / hx2);
            }
            if (i == 0)
                A[ind].emplace_back(ind+n+1, -2. / hx2);
            if (i == m)
                A[ind].emplace_back(ind-n-1, -2. / hx2);
        }

    auto x = maxEigenValue(A, {});
    for (size_t i = 0; i < A.size(); ++i)
        A[i][0].second -= x.l; // непереносимая штука, зависиот от реализации

    mat vs = {};

    // ищем 3 нижних гармоники
    auto z = maxEigenValue(A, vs);
    vs.push_back(z.v);

    auto e1 = maxEigenValue(A, vs);
    vs.push_back(e1.v);

    auto e2 = maxEigenValue(A, vs);
    vs.push_back(e2.v);

    auto e3 = maxEigenValue(A, vs);
    vs.push_back(e3.v);

    // выводим их в файлы
    auto f = fopen("1.dat", "w");

    fprintf(f, "# g^2 = %.6f\n", e1.l + x.l);
    for (size_t i = 0; i <= m; ++i)
    {
        for (size_t j = 0; j <= n; ++j)
        {
            //if (i == 0 || i == m || j == 0 || j == n)
                //fprintf(f, "%f %f 0\n", i * hx, j * hy);
            //else
                //fprintf(f, "%f %f %f\n", i * hx, j * hy, vs[0][(i-1) * (n-1) + (j-1)]);
            fprintf(f, "%f %f %f\n", i * hx, j * hy, e1.v[i * (n+1) + j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);


    f = fopen("2.dat", "w");

    fprintf(f, "# g^2 = %.6f\n", e2.l + x.l);
    for (size_t i = 0; i <= m; ++i)
    {
        for (size_t j = 0; j <= n; ++j)
        {
            //if (i == 0 || i == m || j == 0 || j == n)
                //fprintf(f, "%f %f 0\n", i * hx, j * hy);
            //else
                //fprintf(f, "%f %f %f\n", i * hx, j * hy, vs[1][(i-1) * (n-1) + (j-1)]);
            fprintf(f, "%f %f %f\n", i * hx, j * hy, e2.v[i * (n+1) + j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    f = fopen("3.dat", "w");

    fprintf(f, "# g^2 = %.6f\n", e3.l + x.l);
    for (size_t i = 0; i <= m; ++i)
    {
        for (size_t j = 0; j <= n; ++j)
        {
            //if (i == 0 || i == m || j == 0 || j == n)
                //fprintf(f, "%f %f 0\n", i * hx, j * hy);
            //else
                //fprintf(f, "%f %f %f\n", i * hx, j * hy, vs[2][(i-1) * (n-1) + (j-1)]);
            fprintf(f, "%f %f %f\n", i * hx, j * hy, e3.v[i * (n+1) + j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}
