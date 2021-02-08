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
        // printf("A_arr[0].shape = [%d ,%d]\n", A_arr[0].shape[0], A_arr[0].shape[1]);
        for (int i = 1; i < L; i++)
        {

            if (functions[i - 1] == "relu")
            {
                // printf("inside relu\n");
                // printf("W_arr[%d].shape = [%d ,%d]\n", i, W_arr[i].shape[0], W_arr[i].shape[1]);
                Z_arr[i] = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];

                // printf("Z_arr[%d].shape = [%d ,%d]\n", i, Z_arr[i].shape[0], Z_arr[i].shape[1]);
                A_arr[i] = relu(Z_arr[i]);

                // printf("A_arr[%d].shape = [%d ,%d]\n", i, A_arr[i].shape[0], A_arr[i].shape[1]);
            }
            else if (functions[i - 1] == "sigmoid")
            {
                // printf("inside sigmoid\n");
                // printf("W_arr[%d].shape = [%d ,%d]\n", i, W_arr[i].shape[0], W_arr[i].shape[1]);
                Z_arr[i] = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];
                // printf("z_arr[%d].shape = [%d ,%d]\n", i, Z_arr[i].shape[0], Z_arr[i].shape[1]);
                A_arr[i] = sigmoid(Z_arr[i]);

                // printf("A_arr[%d].shape = [%d ,%d]\n", i, A_arr[i].shape[0], A_arr[i].shape[1]);
            }
            else if (functions[i - 1] == "tanh")
            {
                Z_arr[i] = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];
                A_arr[i] = tanh(Z_arr[i]);
            }
            else
            {
                assert(("Please provide correct activation functions", 0));
            }
        }
        // printf("forward complete\n");
    }

    float cost()
    {

        float cost = (-1 * (sum(Y * log(A_arr[L - 1]) + (1 - Y) * log(1 - A_arr[L - 1])))) / m;

        return cost;
    }

    void backward()
    {
        // printf("back started \n");
        dA_arr[L - 1] = -1 * (Y / A_arr[L - 1]) - ((1 - Y) / (1 - A_arr[L - 1]));
        // printf("dA_arr[%d].shape = [%d ,%d]\n", L - 1, dA_arr[L - 1].shape[0], dA_arr[L - 1].shape[1]);

        for (int i = L - 1; i > 0; i--)
        {
            if (functions[i - 1] == "relu")
            {
                // printf("inside relu\n");
                dZ_arr[i] = dA_arr[i] * (1 * (Z_arr[i] > 0));
                // printf("dZ_arr[%d].shape = [%d ,%d]\n", i, dZ_arr[i].shape[0], dZ_arr[i].shape[1]);
                dW_arr[i] = dot(dZ_arr[i], A_arr[i - 1].T()) / m;
                // printf("dW_arr[%d].shape = [%d ,%d]\n", i, dW_arr[i].shape[0], dW_arr[i].shape[1]);
                db_arr[i] = m_sum(dZ_arr[i], 1) / m;
                // printf("db_arr[%d].shape = [%d ,%d]\n", i, db_arr[i].shape[0], db_arr[i].shape[1]);
                dA_arr[i - 1] = dot(W_arr[i].T(), dZ_arr[i]);
                // printf("dA_arr[%d].shape = [%d ,%d]\n", i - 1, dA_arr[i - 1].shape[0], dA_arr[i - 1].shape[1]);
            }
            else if (functions[i - 1] == "sigmoid")
            {
                // printf("inside sigmoid\n");
                dZ_arr[i] = dA_arr[i] * ((Z_arr[i]) * (1 - Z_arr[i]));
                // printf("dZ_arr[%d].shape = [%d ,%d]\n", i, dZ_arr[i].shape[0], dZ_arr[i].shape[1]);
                dW_arr[i] = dot(dZ_arr[i], A_arr[i - 1].T()) / m;
                // printf("dW_arr[%d].shape = [%d ,%d]\n", i, dW_arr[i].shape[0], dW_arr[i].shape[1]);
                db_arr[i] = m_sum(dZ_arr[i], 1) / m;
                // printf("db_arr[%d].shape = [%d ,%d]\n", i, db_arr[i].shape[0], db_arr[i].shape[1]);
                dA_arr[i - 1] = dot(W_arr[i].T(), dZ_arr[i]);
                // printf("dA_arr[%d].shape = [%d ,%d]\n", i - 1, dA_arr[i - 1].shape[0], dA_arr[i - 1].shape[1]);
            }
            else if (functions[i - 1] == "tanh")
            {

                // printf("inside tanh\n");
                dZ_arr[i] = dA_arr[i] * ((Z_arr[i]) * (1 / (1 + (Z_arr[i] ^ 2))));
                // printf("dZ_arr[%d].shape = [%d ,%d]\n", i, dZ_arr[i].shape[0], dZ_arr[i].shape[1]);
                dW_arr[i] = dot(dZ_arr[i], A_arr[i - 1].T()) / m;
                // printf("dW_arr[%d].shape = [%d ,%d]\n", i, dW_arr[i].shape[0], dW_arr[i].shape[1]);
                db_arr[i] = m_sum(dZ_arr[i], 1) / m;
                // printf("db_arr[%d].shape = [%d ,%d]\n", i, db_arr[i].shape[0], db_arr[i].shape[1]);
                dA_arr[i - 1] = dot(W_arr[i].T(), dZ_arr[i]);
                // printf("dA_arr[%d].shape = [%d ,%d]\n", i - 1, dA_arr[i - 1].shape[0], dA_arr[i - 1].shape[1]);
            }
        }
        // printf("back_completed\n");
    }

    void update_parameter(double learning_rate)
    {
        // printf("updating_started\n");
        for (int i = 1; i < L; i++)
        {
            // printf("%d\n", i);
            // printf("a\n");
            W_arr[i] = W_arr[i] - learning_rate * dW_arr[i];
            // printf("b\n");
            b_arr[i] = b_arr[i] - learning_rate * db_arr[i];
        }
        // printf("update complete\n");
    }

    void pass_data(matrix X1, matrix Y1)
    {
        this->X = X1;
        this->m = X1.shape[1];
        this->Y = Y1;
    }

    void train(int epochs, double learning_rate = 0.01)
    {
        printf("Training .....\n");
        int interval = epochs / 30;
        float min_cost = INT_MAX;
        for (int i = 0; i < epochs; i++)
        {
            forward();
            float cst = cost();
            if (cst < min_cost)
            {
                min_cost = cst;
            }
            if ((i + 1) % interval == 0)
            {
                for (int j = 0; j < ((i + 1) / interval); j++)
                {
                    printf("=");
                }
                for (int j = 35 - ((i + 1) / interval); j > 0; j--)
                {
                    printf(" ");
                }

                printf("cost in iteration %d : %f\n", i + 1, cst);
            }

            //  fprintf(fp, " %f\n", cst);
            backward();
            update_parameter(learning_rate);
        }

        printf("min_cost = %f\n", min_cost);
        printf("train complete\n");
    }

    matrix predict(matrix inp)
    {
        A_arr[0] = inp;
        // printf("A_arr[0].shape = [%d ,%d]\n", A_arr[0].shape[0], A_arr[0].shape[1]);
        for (int i = 1; i < L; i++)
        {

            if (functions[i - 1] == "relu")
            {
                // printf("inside relu\n");
                // printf("W_arr[%d].shape = [%d ,%d]\n", i, W_arr[i].shape[0], W_arr[i].shape[1]);
                Z_arr[i] = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];

                // printf("Z_arr[%d].shape = [%d ,%d]\n", i, Z_arr[i].shape[0], Z_arr[i].shape[1]);
                A_arr[i] = relu(Z_arr[i]);

                // printf("A_arr[%d].shape = [%d ,%d]\n", i, A_arr[i].shape[0], A_arr[i].shape[1]);
            }
            else if (functions[i - 1] == "sigmoid")
            {
                // printf("inside sigmoid\n");
                // printf("W_arr[%d].shape = [%d ,%d]\n", i, W_arr[i].shape[0], W_arr[i].shape[1]);
                Z_arr[i] = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];
                // printf("z_arr[%d].shape = [%d ,%d]\n", i, Z_arr[i].shape[0], Z_arr[i].shape[1]);
                A_arr[i] = sigmoid(Z_arr[i]);

                // printf("A_arr[%d].shape = [%d ,%d]\n", i, A_arr[i].shape[0], A_arr[i].shape[1]);
            }
            else if (functions[i - 1] == "tanh")
            {
                Z_arr[i] = dot(W_arr[i], A_arr[i - 1]) + b_arr[i];
                A_arr[i] = tanh(Z_arr[i]);
            }
            else
            {
                assert(("Please provide correct activation functions", 0));
            }
        }

        // printf("prediction complete\n");
        return A_arr[L - 1];
    }

    void save_model(string path)
    {
        char *pathing = &path[0];
        FILE *fp;

        fp = fopen(pathing, "w");

        fprintf(fp, "%d\n", L);

        for (int i = 0; i < L; i++)
        {
            fprintf(fp, "%d ", layer_dims[i]);
        }
        fprintf(fp, "\n");

        for (int i = 1; i < L; i++)
        {
            char *temp = &functions[i - 1][0];
            fprintf(fp, "%s ", temp);
        }
        fprintf(fp, "\n");

        for (int ind = 1; ind < L; ind++)
        {
            for (int i = 0; i < W_arr[ind].shape[0]; i++)
            {
                for (int j = 0; j < W_arr[ind].shape[1]; j++)
                {
                    fprintf(fp, "%f ", W_arr[ind].data[i][j]);
                }
                fprintf(fp, "\n\n");
            }
        }
        fprintf(fp, "\n\n");
        for (int ind = 1; ind < L; ind++)
        {
            for (int i = 0; i < b_arr[ind].shape[0]; i++)
            {
                for (int j = 0; j < b_arr[ind].shape[1]; j++)
                {
                    fprintf(fp, "%f ", b_arr[ind].data[i][j]);
                }
                fprintf(fp, "\n\n");
            }
        }

        printf("saving complete");
    }
};

classifier load_model(string path)
{
    char *pathing = &path[0];
    FILE *fp;
    fp = fopen(pathing, "r");
    int L;

    vector<int> lay_dim;

    fscanf(fp, "%d", &L);
    // printf("1\n");
    for (int i = 0; i < L; i++)
    {
        int temp;
        fscanf(fp, "%d ", &temp);
        lay_dim.push_back(temp);
    }

    // for (int i = 0; i < L; i++)
    // {
    //     cout << lay_dim[i] << endl;
    // }

    // printf("2\n");
    vector<string> funs;
    // printf("3\n");
    for (int i = 0; i < L - 1; i++)
    {
        char temp_str[100];
        fscanf(fp, "%s ", &temp_str[0]);
        // printf("%s\n",temp_str);
        funs.push_back(temp_str);
    }
    // printf("4\n");
    // printf("2\n");
    classifier obj(lay_dim, funs);
    // printf("3\n");
    obj.W_arr[0] = randn(0, 0);
    for (int ind = 1; ind < L; ind++)
    {
        for (int i = 0; i < lay_dim[ind]; i++)
        {
            for (int j = 0; j < lay_dim[ind - 1]; j++)
            {
                float temp2;
                fscanf(fp, "%f", &temp2);
                obj.W_arr[ind].data[i][j] = temp2;
            }
        }
    }
    // printf("4\n");

    obj.b_arr[0] = randn(0, 0);
    for (int ind = 1; ind < L; ind++)
    {
        for (int i = 0; i < lay_dim[ind]; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                float temp2;
                fscanf(fp, "%f", &temp2);
                obj.b_arr[ind].data[i][1] = temp2;
            }
        }
    }

    printf("loading completed\n");
    return obj;
}

// int main()
// {
//     char x_path[] = "x_breast.txt";
//     char y_path[] = "y_breast.txt";
//     matrix X = take_data(x_path);
//     matrix Y = take_data(y_path);
//     vector<int> layer_dims = {30, 10, 10, 10, 1};
//     vector<string> act_funs = {"sigmoid", "sigmoid", "tanh", "sigmoid"};
//     classifier c1(layer_dims, act_funs);
//     X = X.T();
//     Y = Y.T();
//     // printf("X.shape = [%d ,%d]\n", X.shape[0], X.shape[1]);
//     // printf("Y.shape = [%d ,%d]\n", Y.shape[0], Y.shape[1]);
//     X = normalize(X);
//     c1.pass_data(X, Y);
//     c1.train(1000, 0.00001);
//     char *saving_path = (char *)"a.modle";
//     c1.save_modle(saving_path);
//     print(c1.predict(X(26)));
// }