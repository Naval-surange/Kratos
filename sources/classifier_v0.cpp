#include <bits/stdc++.h>
#include "..\Matrix_lib\matrix.cpp"

/*
    cache - Z,dZ,A
            0  1 2 
*/

using namespace std;

class neural_net
{
private:
    vector<int> layers_dims;
    matrix X, Y;
    matrix *_W;
    matrix *_b;
    matrix *_db;
    matrix *_dW;
    matrix *_Z;
    matrix *_dZ;
    matrix *_A;
    matrix *_dA;

public:
    neural_net(vector<int> layer_dims)
    {
        this->layers_dims = layer_dims;

        this->_dA = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); //dA

        this->_W = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); //W
        this->_W[0] = zeros(layer_dims[0], 1);
        for (int i = 1; i < layer_dims.size(); i++) //Initilization
        {
            this->_W[i] = randn(layer_dims[i], layer_dims[i - 1]) * 0.01;
        }

        this->_dW = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); //dW
        // this->_dW[0] = zeros(layer_dims[0], 1);
        // for (int i = 1; i < layer_dims.size(); i++) //Initilization
        // {
        //     this->_dW[i] = randn(layer_dims[i], layer_dims[i - 1]) * 0.01;
        // }

        this->_b = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); //b
        this->_b[0] = randn(layer_dims[0], 1);
        for (int i = 1; i < layer_dims.size(); i++) //Initilozation
        {
            this->_b[i] = zeros(layer_dims[i], 1);
        }

        this->_db = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); //db
        // this->_db[0] = randn(layer_dims[0], 1);
        // for (int i = 1; i < layer_dims.size(); i++) //Initilozation
        // {
        //     this->_db[i] = zeros(layer_dims[i], 1);
        // }

        this->_Z = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); // Z
        // this->_Z[0] = zeros(layer_dims[0], layer_dims[0]);
        // for (int i = 1; i < layer_dims.size(); i++) //Initilization
        // {
        //     this->_Z[i] = zeros(layer_dims[i], layers_dims[0]);
        // }

        this->_dZ = (matrix *)malloc(sizeof(matrix) * layer_dims.size()); //dZ
        // this->_dZ[0] = zeros(layer_dims[0], layer_dims[0]);
        // for (int i = 1; i < layer_dims.size(); i++) //Initilization
        // {
        //     this->_dZ[i] = zeros(layer_dims[i], layers_dims[0]);
        // }

        this->_A = (matrix *)malloc(sizeof(matrix) * (layer_dims.size() + 1)); //A
        // this->_A[0] = zeros(layer_dims[0], layer_dims[0]);
        // for (int i = 1; i < layer_dims.size(); i++) //Initilization
        // {
        //     this->_A[i] = zeros(layer_dims[i], layers_dims[0]);
        // }
        // _A[layers_dims.size()] = zeros();
    }

    void pass_data(matrix X1, matrix Y1)
    {
        this->X = X1;
        this->Y = Y1;
    }

    matrix lin_forward()
    {
        printf("Lin forward started ....\n");
        matrix A_prev = X;
        for (int i = 1; i < layers_dims.size() - 1; i++)
        {
            matrix Z = dot(this->_W[i], A_prev) + this->_b[i];
            _Z[i] = Z;
            matrix A = relu(Z);
            _A[i] = A;
            A_prev = A;
        }

        matrix Z_L = dot(this->_W[this->layers_dims.size() - 1], A_prev);
        _Z[this->layers_dims.size() - 1] = Z_L;
        matrix A_L = sigmoid(Z_L); //----> if last layer is sigmoid
        // matrix A_L = Z_L;
        _A[this->layers_dims.size() - 1] = A_L;

        printf("Forward complete\n");
        return A_L;
    }

    float cost(matrix A_L)
    {
        printf("Cost statred...\n");
        float m = Y.shape[1];
        float cost = -1 * sum(Y * log(A_L) + (1 - Y) * log(1 - A_L)) / m;
        printf("cost complete\n");
        return cost;
    }

    void lin_backward()
    {
        printf("backward started...\n");
        int L = layers_dims.size();
        int m = Y.shape[1];

        matrix A_L = _A[L - 1];
        // printf("1\n");
        matrix dA_L = -1 * (Y / A_L) - ((1 - Y) / (1 - A_L)); // --> if last layer is sigmoid
        // matrix dA_L = -1 * (Y / A_L);
        _dA[L - 1] = dA_L;
        // printf("2\n");
        _dZ[L - 1] = dA_L * ((1 - _Z[L - 1]) * (_Z[L - 1]));
        // printf("3\n");
        _dW[L - 1] = (_Z[L - 1] * _A[L - 1]) / m;
        // printf("4\n");
        _db[L - 1] = m_sum(_dZ[L - 1], 1) / m;
        // printf("5\n");
        matrix dA_before = dot(_W[L - 1].T(), _dZ[L - 1]);
        _dA[L - 2] = dA_before;
        // printf("6\n");
        for (int i = L - 2; i > 0; i--)
        {
            // printf("7-i +L-2\n");
            printf("1\n");
            _dZ[i] = _dA[i + 1] * (1 * (_Z[i] > 0));
            printf("2\n");
            _dW[i] = (_dZ[i] * dA_before.T()) / m;
            printf("3\n");
            dA_before = dot(_W[i].T(), _dZ[i]);
        }
        printf("backward complete\n");
    }

    void update_parameter(float learning_rate = 0.01)
    {

        for (int i = 1; i < layers_dims.size() + 1; i++)
        {
            _W[i] = _W[i] - learning_rate * _dW[i];
            _b[i] = _b[i] - learning_rate * _db[i];
        }
        printf("update complete\n");
    }

    void train(int epochs, int learning_rate)
    {
        printf("Training .....\n");
        for (int i = 0; i < epochs; i++)
        {
            matrix A_L = lin_forward();
            float cst = cost(A_L);
            printf("cost in iterartion %d : %f\n", i + 1, cst);
            lin_backward();
            update_parameter(learning_rate);
        }
        printf("train complete\n");
    }

    void predict()
    {
    }
};

// int main()
// {
//     vector<int> dims{13, 4, 1};
//     neural_net n1(dims);
//     char x_path[] = "bosten_x.txt";
//     char y_path[] = "bosten_y.txt";
//     matrix X = take_matrix(x_path);
//     matrix Y = take_matrix(y_path);
//     n1.pass_data(X.T(), Y.T());
//     n1.train(5, 0.01);
// }