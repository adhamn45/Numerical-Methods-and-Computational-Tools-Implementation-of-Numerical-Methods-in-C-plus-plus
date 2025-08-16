#include <iostream>
using namespace std;

int main()
{
    int n = 3;
    double x[n], y[n], b[n];
    double a[n][n], L[n][n], U[n][n];
    float sum;

    cout<<"Enter the elements of matrix a: "<<endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << "Give the number at position (" << i << "," << j << "): " << endl;
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        y[i] = 0;
        x[i] = 0;
        for (int j = 1; j <= n; j++)
        {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            sum = 0;
            for (int k = 1; k <= n; k++)
            {
                // if (i < k)
                // {
                //     L[i][k] = 0;
                // }

                // if (k > j)
                // {
                //     U[k][j] = 0;
                // }
                if (k == j)
                {
                    U[k][j] = 1;
                }

                sum = sum + L[i][k] * U[k][j];
            }
            if (i >= j)
            {
                L[i][j] = a[i][j] - sum;
            }
            else
            {
                U[i][j] = (a[i][j] - sum) / L[i][i];
            }
        }
    }

    cout << endl
         << "Input matrix:" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl
         << "Enter the elements of b matrix" << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }

    cout << endl
         << "Matrix L:" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl
         << "Matrix U:" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= n; i++)
    {
        sum = 0;
        for (int j = 1; j <= n; j++)
        {
            sum = sum + L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
    cout << endl
         << "Matrix y: " << endl;
    for (int j = 1; j <= n; j++)
    {
        cout << "y" << j << " = " << y[j] << endl;
    }

    for (int i = n; i >= 1; i--)
    {
        sum = 0;
        for (int j = 1; j <= n; j++)
        {
            sum = sum + U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    cout << endl
         << "Solution: " << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "x" << i << " = " << x[i] << endl;
    }

    return 0;
}