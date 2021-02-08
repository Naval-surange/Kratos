#include <bits/stdc++.h>
#include "..\Matrix_lib\matrix.cpp"

using namespace std;

class classifier
{

public:
    matrix X, Y;
    matrix *W_arr;
    matrix *b_arr;
    matrix *Z_arr;
    matrix *A_arr;
    matrix *dW_arr;
    matrix *db_arr;
    matrix *dZ_arr;
    matrix *dA_arr;
    int L, m;
    vector<int> layer_dims;
    vector<string> functions;
    classifier(vector<int> layerdims, vector<string> funs)
    {
        // assert(("size of functions must be 1 less than layer_dims ", layerdims.size() == (funs.size() - 1)));
        layer_dims = layerdims;
        functions = funs;
        L = layer_dims.size();

        W_arr = (matrix *)malloc(sizeof(matrix) * (L));
        W_arr[0] = randn(0, 0);
        for (int i = 1; i < L; i++)
        {
            W_arr[i] = randn(layer_dims[i], layer_dims[i - 1]);
        }

        b_arr = (matrix *)malloc(sizeof(matrix) * (L));
        b_arr[0] = randn(0, 0);
        for (int i = 1; i < L; i++)
        {
            b_arr[i] = zeros(layer_dims[i], 1);
        }
        Z_arr = (matrix *)malloc(sizeof(matrix) * (L));
        A_arr = (matrix *)malloc(sizeof(matrix) * (L + 1));
        dW_arr = (matrix *)malloc(sizeof(matrix) * (L));
        db_arr = (matrix *)malloc(sizeof(matrix) * (L));
        dZ_arr = (matrix *)malloc(sizeof(matrix) * (L));
        dA_arr = (matrix *)malloc(sizeof(matrix) * (L + 1));
    }

    void forward()
    {
        // matrix A_prev = X;
        A_arr[0] = X;
        printf("A_arr[0].shape = [%d ,%d]\n", A_arr[0].shape[0], A_arr[0].shape[1]);
        for (int i = 1; i < L; i++)
        {

            if (functions[i - 1] == "relu")
            {
                printf("inside relu\n");
                printf("W_arr[%d].shape = [%d ,%d]\n", i, W_arr[i].shape[0], W_arr[i].shape[1]);
                matrix z = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];
                Z_arr[i] = z;
                printf("Z_arr[%d].shape = [%d ,%d]\n", i, Z_arr[i].shape[0], Z_arr[i].shape[1]);
                matrix a = relu(Z_arr[i]);
                A_arr[i] = a;
                printf("A_arr[%d].shape = [%d ,%d]\n", i, A_arr[i].shape[0], A_arr[i].shape[1]);
            }
            else if (functions[i - 1] == "sigmoid")
            {
                printf("inside sigmoid\n");
                printf("W_arr[%d].shape = [%d ,%d]\n", i, W_arr[i].shape[0], W_arr[i].shape[1]);
                matrix z = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];
                Z_arr[i] = z;
                printf("z_arr[%d].shape = [%d ,%d]\n", i, Z_arr[i].shape[0], Z_arr[i].shape[1]);
                matrix a = sigmoid(Z_arr[i]);
                A_arr[i] = a;
                printf("A_arr[%d].shape = [%d ,%d]\n", i, A_arr[i].shape[0], A_arr[i].shape[1]);
            }
            else
            {
                assert(("Please provide correct activation functions", 0));
            }
        }
        printf("forward complete\n");
    }

    float cost()
    {

        printf("Cost statred...\n");
        // float m = Y.shape[1];
        float cost = -1 * sum(Y * log(A_arr[L - 1]) + (1 - Y) * log(1 - A_arr[L - 1])) / m;
        printf("cost complete\n");
        return cost;
    }

    void backward()
    {
        printf("back started \n");
        dA_arr[L - 1] = -1 * (Y / A_arr[L - 1]) - ((1 - Y) / (1 - A_arr[L - 1]));
        printf("dA_arr[%d].shape = [%d ,%d]\n", L - 1, dA_arr[L - 1].shape[0], dA_arr[L - 1].shape[1]);

        for (int i = L - 1; i > 0; i--)
        {
            if (functions[i - 1] == "relu")
            {
                printf("inside relu\n");
                dZ_arr[i] = dA_arr[i] * (1 * (Z_arr[i] > 0));
                printf("dZ_arr[%d].shape = [%d ,%d]\n", i, dZ_arr[i].shape[0], dZ_arr[i].shape[1]);
                dW_arr[i] = dot(dZ_arr[i], dA_arr[i].T()) / m;
                printf("dW_arr[%d].shape = [%d ,%d]\n", i, dW_arr[i].shape[0], dW_arr[i].shape[1]);
                db_arr[i] = m_sum(dZ_arr[i], 1) / m;
                printf("db_arr[%d].shape = [%d ,%d]\n", i, db_arr[i].shape[0], db_arr[i].shape[1]);
                dA_arr[i - 1] = dot(W_arr[i].T(), dZ_arr[i]);
                printf("dA_arr[%d].shape = [%d ,%d]\n", i - 1, dA_arr[i - 1].shape[0], dA_arr[i - 1].shape[1]);
            }
            else if (functions[i - 1] == "sigmoid")
            {
                printf("inside sigmoid\n");
                dZ_arr[i] = dA_arr[i] * ((Z_arr[i]) * (1 - Z_arr[i]));
                printf("dZ_arr[%d].shape = [%d ,%d]\n", i, dZ_arr[i].shape[0], dZ_arr[i].shape[1]);
                dW_arr[i] = dot(dZ_arr[i], dA_arr[i].T()) / m;
                printf("dW_arr[%d].shape = [%d ,%d]\n", i, dW_arr[i].shape[0], dW_arr[i].shape[1]);
                db_arr[i] = m_sum(dZ_arr[i], 1) / m;
                printf("db_arr[%d].shape = [%d ,%d]\n", i, db_arr[i].shape[0], db_arr[i].shape[1]);
                dA_arr[i - 1] = dot(W_arr[i].T(), dZ_arr[i]);
                printf("dA_arr[%d].shape = [%d ,%d]\n", i - 1, dA_arr[i - 1].shape[0], dA_arr[i - 1].shape[1]);
            }
        }
        printf("back_completed\n");
    }

    void update_parameter(float learning_rate = 0.01)
    {
        printf("updating_started\n");
        for (int i = 1; i < L; i++)
        {
            printf("%d\n", i);
            printf("a\n");
            W_arr[i] = W_arr[i] - learning_rate * dW_arr[i];
            printf("b\n");
            b_arr[i] = b_arr[i] - learning_rate * db_arr[i];
        }
        printf("update complete\n");
    }

    void pass_data(matrix X1, matrix Y1)
    {
        this->X = X1;
        this->Y = Y1;
    }

    void train(int epochs, float learning_rate)
    {
        printf("Training .....\n");
        for (int i = 0; i < epochs; i++)
        {
            forward();
            float cst = cost();
            printf("cost in iterartion %d : %f\n", i + 1, cst);
            backward();
            update_parameter(learning_rate);
        }
        printf("train complete\n");
    }
};

// int main()
// {
//     char x_path[] = "x_breast.txt";
//     char y_path[] = "y_breast.txt";
//     matrix X = take_matrix(x_path);
//     matrix Y = take_matrix(y_path);
//     vector<int> layer_dims = {30, 5, 4, 1};
//     vector<string> act_funs = {"relu", "relu", "sigmoid"};
//     classifier c1(layer_dims, act_funs);
//     X = X.T();
//     Y = Y.T();
//     printf("X.shape = [%d ,%d]\n", X.shape[0], X.shape[1]);
//     printf("Y.shape = [%d ,%d]\n", Y.shape[0], Y.shape[1]);
//     c1.pass_data(X, Y);
//     c1.train(3, 0.01);
// }