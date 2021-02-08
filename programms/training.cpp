#include "..\sources\classifier_v2.cpp"
#include <bits/stdc++.h>

using namespace std;
int main()
{
    char x_path[] = "D:\\fun\\Kratos\\datasets\\breast_cancer\\x_breast.txt";
    char y_path[] = "D:\\fun\\Kratos\\datasets\\breast_cancer\\y_breast.txt";
    matrix X = take_matrix(x_path);
    matrix Y = take_matrix(y_path);
    vector<int> layer_dims = {30, 10, 10, 10, 1};
    vector<string> act_funs = {"sigmoid", "sigmoid", "tanh", "sigmoid"};
    classifier c1(layer_dims, act_funs);
    X = X.T();
    Y = Y.T();

    X = normalize(X);
    c1.pass_data(X, Y);
    c1.train(1500, 0.000001);
    c1.save_model("b.model");
}