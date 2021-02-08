#ifndef DEFINING_ELEMENT_X8346D3
#define DEFINING_ELEMENT_X8346D3
// #define e 2.71828
// #define pi 3.14159
#include <bits/stdc++.h>
// #include <Eigen/Eigen>

// using namespace Eigen;
using namespace std;

class matrix
{
public:
    float **data;
    int shape[2];

    matrix()
    {
        this->shape[0] = 0;
        this->shape[1] = 0;
    }

    matrix(int a, int b)
    {
        this->shape[0] = a;
        this->shape[1] = b;
        this->data = (float **)malloc(sizeof(float *) * a);
        for (int i = 0; i < a; i++)
        {
            this->data[i] = (float *)malloc(sizeof(float) * b);
        }
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < b; j++)
            {
                this->data[i][j] = 0;
            }
        }
    }

    void print()
    {
        printf("\n{ ");
        printf("Class : matrix , shape = [ %d , %d ] \n", this->shape[0], this->shape[1]);
        printf("  [ \n");
        for (int i = 0; i < this->shape[0]; i++)
        {
            printf("   [ ");
            for (int j = 0; j < this->shape[1]; j++)
            {
                if (j == this->shape[1] - 1)
                {
                    printf("%f ", data[i][j]);
                }
                else
                {
                    printf("%f , ", data[i][j]);
                }
            }
            if (i == this->shape[0] - 1)
                printf(" ]\n");
            else
            {
                printf(" ] ,\n");
            }
        }
        printf("  ] \n}\n", this->shape[0], this->shape[1]);
    }

    friend matrix operator>=(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                if (m.data[i][j] >= n)
                    res.data[i][j] = 1;
                else
                    res.data[i][j] = 0;
            }
        }
        return res;
    }

    friend matrix operator<=(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                if (m.data[i][j] <= n)
                    res.data[i][j] = 1;
                else
                    res.data[i][j] = 0;
            }
        }
        return res;
    }

    friend matrix operator>(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                if (m.data[i][j] > n)
                    res.data[i][j] = 1;
                else
                    res.data[i][j] = 0;
            }
        }
        return res;
    }

    friend matrix operator<(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                if (m.data[i][j] > n)
                    res.data[i][j] = 1;
                else
                    res.data[i][j] = 0;
            }
        }
        return res;
    }

    friend int operator==(matrix const m, matrix const &n)
    {
        if (m.shape[0] != n.shape[0] || m.shape[1] != n.shape[1])
        {
            return 0;
        }
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                if (m.data[i][j] != n.data[i][j])
                {
                    return 0;
                }
            }
        }
        return 1;
    }

    friend int operator!=(matrix const m, matrix const &n)
    {
        if (m.shape[0] != n.shape[0] || m.shape[1] != n.shape[1])
        {
            return 1;
        }

        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                if (m.data[i][j] != n.data[i][j])
                {
                    return 1;
                }
            }
        }
        return 0;
    }

    matrix operator()(int index)
    {
        matrix res(shape[0], 1);
        for (int i = 0; i < shape[0]; i++)
        {
            res.data[i][0] = this->data[i][index];
        }
        return res;
    }

    matrix operator()(int index1, int index2, int axis = 0)
    {
        if (axis == 0)
        {
            if (!((index1 >= 0 && index1 < shape[0]) && (index2 >= 0 && index2 < shape[0]) && index1 < index2))
            {
                fprintf(stderr, "enter correct indexing and axis , m.shape = [%d  %d ]", shape[0], shape[1]);
                exit(1);
            }
            matrix res(index2 - index1, shape[1]);
            for (int i = index1; i < index2; i++)
            {
                for (int j = 0; j < shape[1]; j++)
                {
                    res.data[i - index1][j] = data[i][j];
                }
            }

            return res;
        }
        else if (axis == 1)
        {
            if (!((index1 >= 0 && index1 < shape[1]) && (index2 >= 0 && index2 < shape[1]) && index1 < index2))
            {
                fprintf(stderr, "enter correct indexing and axis , m.shape = [%d  %d ]", shape[0], shape[1]);
                exit(1);
            }
            matrix res(shape[0], index2 - index1);

            for (int i = 0; i < shape[0]; i++)
            {
                for (int j = index1; j < index2; j++)
                {
                    res.data[i][j - index1] = data[i][j];
                }
            }

            return res;
        }
    }

    friend matrix operator/(matrix const m1, matrix const m2)
    {
        if (m1.shape[0] == m2.shape[0] && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m2.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] / m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][j] / m2.data[i][j];
                }
            }
            return res;
        }

        else if (m1.shape[0] != 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][0] / m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[0][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] == 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] / m2.data[i][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] == 1)
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] / m2.data[0][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1)
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][0] / m2.data[i][j];
                }
            }
            return res;
        }
        else
        {
            fprintf(stderr, "cannot divide element wise ,dimensions mismatched m1.shape = [%d , %d] and m2.shape = [%d , %d]", m1.shape[0], m1.shape[1], m2.shape[0], m2.shape[1]);
            exit(1);
        }
    }

    friend matrix operator/(float const &n, matrix const m)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = n / (m.data[i][j]);
            }
        }
        return res;
    }

    friend matrix operator/(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = (m.data[i][j]) / n;
            }
        }
        return res;
    }

    // friend matrix operator+(matrix const m1, matrix const m2)
    // {
    //     if (m1.shape[0] == m2.shape[0] && m1.shape[1] == m2.shape[1])
    //     {
    //         matrix res(m1.shape[0], m2.shape[1]);
    //         for (int i = 0; i < m1.shape[0]; i++)
    //         {
    //             for (int j = 0; j < m1.shape[1]; j++)
    //             {
    //                 res.data[i][j] = m1.data[i][j] + m2.data[i][j];
    //             }
    //         }
    //         return res;
    //     }
    // }

    friend matrix operator+(matrix const m1, matrix const m2)
    {
        if (m1.shape[0] == m2.shape[0] && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m2.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][j] + m2.data[i][j];
                }
            }
            return res;
        }

        else if (m1.shape[0] != 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][0] + m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[0][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] == 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[i][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] == 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[i][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] == 1)
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[0][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1)
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][0] + m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] == 1)
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[0][0];
                }
            }
            return res;
        }
        // else if (m1.shape[0] == 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] == 1)
        // {
        //     matrix res(m2.shape[0], m2.shape[1]);
        //     for (int i = 0; i < m2.shape[0]; i++)
        //     {
        //         for (int j = 0; j < m2.shape[1]; j++)
        //         {
        //             res.data[i][j] = m1.data[0][0] + m2.data[i][j];
        //         }
        //     }
        //     return res;
        // }

        else
        {
            fprintf(stderr, "cannot add dimensions mismatched m1.shape = [%d , %d] and m2.shape = [%d , %d]", m1.shape[0], m1.shape[1], m2.shape[0], m2.shape[1]);
            exit(1);
        }
    }

    friend matrix operator+(float const &n, matrix const m)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = m.data[i][j] + n;
            }
        }
        return res;
    }

    friend matrix operator+(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = m.data[i][j] + n;
            }
        }
        return res;
    }

    friend matrix operator-(matrix const m1, matrix const m2)
    {
        if (m1.shape[0] == m2.shape[0] && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m2.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] - m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][j] - m2.data[i][j];
                }
            }
            return res;
        }

        else if (m1.shape[0] != 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][0] - m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] - m2.data[0][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] == 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] - m2.data[i][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] == 1)
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] - m2.data[0][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1)
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][0] - m2.data[i][j];
                }
            }
            return res;
        }
        else
        {
            fprintf(stderr, "cannot subtract ,dimensions mismatched m1.shape = [%d , %d] and m2.shape = [%d , %d]", m1.shape[0], m1.shape[1], m2.shape[0], m2.shape[1]);
            exit(1);
        }
    }

    friend matrix operator-(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = m.data[i][j] - n;
            }
        }
        return res;
    }

    friend matrix operator-(float const &n, matrix const m)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = n - m.data[i][j];
            }
        }
        return res;
    }

    friend matrix operator*(matrix const m1, matrix const m2)
    {
        if (m1.shape[0] == m2.shape[0] && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m2.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] + m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][j] * m2.data[i][j];
                }
            }
            return res;
        }

        else if (m1.shape[0] != 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][0] * m2.data[i][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] != 1 && m1.shape[1] == m2.shape[1])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] * m2.data[0][j];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] != 1 && m2.shape[1] == 1 && m1.shape[0] == m2.shape[0])
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] * m2.data[i][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] != 1 && m1.shape[1] != 1 && m2.shape[0] == 1 && m2.shape[1] == 1)
        {
            matrix res(m1.shape[0], m1.shape[1]);
            for (int i = 0; i < m1.shape[0]; i++)
            {
                for (int j = 0; j < m1.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[i][j] * m2.data[0][0];
                }
            }
            return res;
        }
        else if (m1.shape[0] == 1 && m1.shape[1] == 1 && m2.shape[0] != 1 && m2.shape[1] != 1)
        {
            matrix res(m2.shape[0], m2.shape[1]);
            for (int i = 0; i < m2.shape[0]; i++)
            {
                for (int j = 0; j < m2.shape[1]; j++)
                {
                    res.data[i][j] = m1.data[0][0] * m2.data[i][j];
                }
            }
            return res;
        }
        else
        {
            fprintf(stderr, "cannot multiple element wise, dimensions mismatched m1.shape = [%d , %d] and m2.shape = [%d , %d]", m1.shape[0], m1.shape[1], m2.shape[0], m2.shape[1]);
            exit(1);
        }
    }

    friend matrix operator*(float const &n, matrix const m)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = m.data[i][j] * n;
            }
        }
        return res;
    }

    friend matrix operator*(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = m.data[i][j] * n;
            }
        }
        return res;
    }

    friend matrix operator^(matrix const m, float const &n)
    {
        matrix res(m.shape[0], m.shape[1]);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[i][j] = pow(m.data[i][j], n);
            }
        }
        return res;
    }
    matrix T()
    {
        matrix m1(this->shape[1], this->shape[0]);

        for (int i = 0; i < shape[0]; i++)
        {
            for (int j = 0; j < shape[1]; j++)
            {
                m1.data[j][i] = this->data[i][j];
            }
        }
        return m1;
    }
};

matrix randn(int a, int b)
{
    matrix m(a, b);
    srand(time(0));
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            m.data[i][j] = 2 * (rand() / (float)RAND_MAX) - 1;
        }
    }
    return m;
}

void print(matrix m)
{
    printf("\n{ ");
    printf("Class : matrix , shape = [ %d , %d ] \n", m.shape[0], m.shape[1]);
    printf("  [ \n");
    for (int i = 0; i < m.shape[0]; i++)
    {
        printf("   [ ");
        for (int j = 0; j < m.shape[1]; j++)
        {
            if (j == m.shape[1] - 1)
            {
                printf("%f ", m.data[i][j]);
            }
            else
            {
                printf("%f , ", m.data[i][j]);
            }
        }
        if (i == m.shape[0] - 1)
            printf(" ]\n");
        else
        {
            printf(" ] ,\n");
        }
    }
    printf("  ] \n}", m.shape[0], m.shape[1]);
}

matrix take_matrix(char *path)
{
    FILE *fp;
    fp = fopen(path, "r");
    int dim1, dim2;
    fscanf(fp, "%d %d", &dim1, &dim2);
    matrix X(dim1, dim2);
    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
        {
            fscanf(fp, "%f", &X.data[i][j]);
        }
    }

    return X;
}

matrix zeros(int a, int b)
{
    matrix m(a, b);
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            m.data[i][j] = 0;
        }
    }
    return m;
}

matrix dot(matrix m1, matrix m2)
{
    if (m1.shape[1] != m2.shape[0])
    {
        fprintf(stderr, "ERROR : Dimensions Mismatch in performing dot product m1.shape = [%d ,%d]  and  m2.shape = [%d ,%d]\n", m1.shape[0], m1.shape[1], m2.shape[0], m2.shape[1]);
        exit(1);
    }
    matrix multi(m1.shape[0], m2.shape[1]);

    for (int i = 0; i < m1.shape[0]; ++i)
    {
        for (int j = 0; j < m2.shape[1]; ++j)
        {
            for (int k = 0; k < m1.shape[1]; ++k)
            {
                multi.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return multi;
}

matrix abs(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            if (m.data[i][j] > 0)
                res.data[i][j] = m.data[i][j];
            else
                res.data[i][j] = -1 * m.data[i][j];
        }
    }
    return res;
}

matrix exp(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            res.data[i][j] = pow(2.71828, m.data[i][j]);
        }
    }
    return res;
}

matrix log(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            if (m.data[i][j] < 0)
            {
                fprintf(stderr, "Domain error in log");
                exit(1);
            }
            else if (m.data[i][j] == 0)
                res.data[i][j] = 0;
            else
                res.data[i][j] = log(m.data[i][j]);
        }
    }
    return res;
}

float sum(matrix m)
{

    float sum = 0;
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            sum += m.data[i][j];
        }
    }
    return sum;
}

matrix m_sum(matrix m, int axis = -1)
{
    if (axis == 0)
    {
        matrix res(1, m.shape[1]);
        for (int i = 0; i < m.shape[1]; i++)
        {
            float sum = 0;
            for (int j = 0; j < m.shape[0]; j++)
            {
                sum = sum + m.data[j][i];
            }
            res.data[0][i] = sum;
        }
        return res;
    }
    else if (axis == 1)
    {
        matrix res(m.shape[0], 1);
        for (int i = 0; i < m.shape[0]; i++)
        {
            float sum = 0;
            for (int j = 0; j < m.shape[1]; j++)
            {
                sum = sum + m.data[i][j];
            }
            res.data[i][0] = sum;
        }
        return res;
    }
    else
    {
        matrix res = zeros(1, 1);
        for (int i = 0; i < m.shape[0]; i++)
        {
            for (int j = 0; j < m.shape[1]; j++)
            {
                res.data[0][0] += m.data[i][j];
            }
        }
        return res;
    }
}

matrix sigmoid(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            res.data[i][j] = 1.0 / (1.0 + pow(2.71828, -1 * m.data[i][j]));
        }
    }
    return res;
}

matrix tanh(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            res.data[i][j] = tanh(m.data[i][j]);
        }
    }
    return res;
}
matrix relu(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        for (int j = 0; j < m.shape[1]; j++)
        {
            if (m.data[i][j] >= 0)
            {
                res.data[i][j] = m.data[i][j];
            }
            else
            {
                res.data[i][j] = 0;
            }
        }
    }
    return res;
}

matrix normalize(matrix m)
{
    matrix res(m.shape[0], m.shape[1]);
    for (int i = 0; i < m.shape[0]; i++)
    {
        float max = m.data[i][0];
        float min = m.data[i][0];
        for (int j = 0; j < m.shape[1]; j++)
        {
            if (max < m.data[i][j])
            {
                max = m.data[i][j];
            }
            if (min > m.data[i][j])
            {
                min = m.data[i][j];
            }
        }

        for (int j = 0; j < m.shape[1]; j++)
        {
            res.data[i][j] = (m.data[i][j] - min) / (max - min);
        }
    }
    return res;
}
#endif

// matrix cost(matrix Y, matrix A_L)
// {
//     float m = Y.shape[1];
//     matrix cost = -1 * m_sum(Y * log(A_L) + (1 - Y) * log(1 - A_L), 1) / m;
//     return cost;
// }

// int main()
// {
//     matrix m1 = randn(3, 5);
//     print(m1);
//     matrix m2 = sigmoid(m1);
//     print(m2);
//     print(1 - m2);
//     print(log(m2));
// }

// int main()
// {
//     clock_t start, end;
//     float time;
//     printf("Matrix : Computing....\n");
//     for (int i = 10; i <= 1000; i += 20)
//     {
//         start = clock();
//         matrix m1 = randn(i, i), m2 = randn(i, i);
//         matrix m3 = dot(m1, m2.T());
//         end = clock();
//         float time = (float)(end - start) / CLOCKS_PER_SEC;
//         printf("%f\n", time);

//         //     start = clock();
//         //     MatrixXf m4 = MatrixXf::Random(i, i), m5 = MatrixXf::Random(i, i);
//         //     MatrixXf temp = m4 * m5;
//         //     end = clock();
//         //     time = (float)(end - start) / CLOCKS_PER_SEC;
//         //     printf("%f", time);
//         // }
//     }
// }

// class test
// {
// private:
//     matrix A = zeros(0, 0), B = zeros(0, 0);

// public:
//     void get_data(matrix X, matrix Y)
//     {
//         this->A = X;
//         this->B = Y;
//     }

//     void print_a_b()
//     {
//         this->A.print();
//         this->B.print();
//     }
// };

// int main()
// {
//     test t;
//     matrix m1=zeros(10 ,4),m2=randn(10,3);
//     t.get_data(m1,m2);
//     t.print_a_b();
//}

// int main()
// {
// matrix m = randn(100, 100);
// matrix m1 = sigmoid(m);
// matrix m2 = log(m1);
// for (int i = 0; i < 100; i++)
// {
//     for (int j = 0; j < 100; j++)
//     {
//         if (!(m1.data[i][j] < 1 && m1.data[i][j] > 0))
//         {
//             printf("Error");
//         }
//     }
// }

// float ans;
// ans = 1 / (1 + pow(2.71828, 14));
// printf("%f",ans );

// printf("%f",log(0.001));
// }

// int main()
// {
//     matrix m = randn(10, 6);
//     matrix m2 = m(2, 4, 1);
//     m.print();
//     m2.print();
// }