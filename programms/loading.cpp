#include "..\sources\classifier_v2.cpp"
#include <bits/stdc++.h>

using namespace std;
int main()
{
    char x_path[] = "D:\\fun\\neural_net_cpp_lib\\x_breast.txt";
    classifier c = load_model("D:\\fun\\neural_net\\b.model");
    matrix x = take_matrix(x_path);
    matrix X = x.T();
    print(c.predict(X(3)));
}