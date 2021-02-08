#include <bits/stdc++.h>

using namespace std;
int main()
{
    FILE *fp;
    fp = fopen64("test.txt", "r");
    for (int i = 0; i < 4; i++)
    {
        char temp[100];
        fscanf(fp, "%s ", &temp[0]);
        printf("%s\n", temp);
    }
}