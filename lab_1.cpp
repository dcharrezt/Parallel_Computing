#include <iostream>
#include <ctime>

#define MAX 500

using namespace std;

void fill_matrix(int matrix[][MAX], int rows, int columns);
void loop_1(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
					int rows_1, int columns_1, int rows_2, int columns_2);
void loop_2(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
					int rows_1, int columns_1, int rows_2, int columns_2);
void matrix_multiplication(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
					int rows_1, int columns_1, int rows_2, int columns_2);
void matrix_block_multiplication(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
					int rows_1, int columns_1, int rows_2, int columns_2);
void print_matrix(int matrix[][MAX], int rows, int columns);

int main()
{
	int m_1[MAX][MAX], m_2[MAX][MAX], rows_1, columns_1, rows_2, columns_2;
	int m_3[MAX][MAX] = {0};

	cout << "Enter rows and column for matrix 1: ";
	cin >> rows_1 >> columns_1;

	cout << "Enter rows and column for matrix 2: ";
	cin >> rows_2 >> columns_2;

	while (columns_1 != rows_2)
	{
		cout << "Error!" << endl;
		cout << "Enter rows and column for first matrix: ";
		cin >> rows_1 >> columns_1;
		cout << "Enter rows and column for second matrix: ";
		cin >> rows_2 >> columns_2;
	}

    fill_matrix(m_1, rows_1, columns_1);
    fill_matrix(m_2, rows_2, columns_2);

    clock_t begin = clock();

	// matrix_block_multiplication(m_1, m_2, m_3, rows_1, columns_1,
	// 									 rows_2, columns_2);

    loop_1(m_1, m_2, m_3, rows_1, columns_1, rows_2, columns_2);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "TIME LOOP 1: " << time_spent << endl;

	int m_4[MAX][MAX] = {0};

    begin = clock();
    loop_2(m_1, m_2, m_4, rows_1, columns_1, rows_2, columns_2);
	end = clock();
	double time_spent_2 = (double)(end - begin) / CLOCKS_PER_SEC;

	cout << "TIME LOOP 2: " << time_spent_2 << endl;
    
    // print_matrix(m_3, rows_1, columns_2);

	return 0;
}

void fill_matrix(int m_1[][MAX], int rows, int columns)
{
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < columns; ++j)
		{
			m_1[i][j] = MAX * i + j;
		}
	}
}

void matrix_multiplication(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
						int rows_1, int columns_1, int rows_2, int columns_2)
{

	for(int i = 0; i < rows_1; ++i)
	{
		for(int j = 0; j < columns_2; ++j)
		{
			for(int k=0; k<columns_1; ++k)
			{
				m_3[i][j] += m_1[i][k] * m_2[k][j];
			}
		}
	}
}


void matrix_block_multiplication(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
						int rows_1, int columns_1, int rows_2, int columns_2)
{
	#define TILE 10

    for ( int i=0; i<MAX; i+=TILE )
        for ( int j=0; j<MAX; j+=TILE )
            for ( int k=0; k<MAX; k+=TILE )
                /* Regular multiply inside the tiles */
                for ( int y=i; y<i+TILE; y++ )
                    for ( int x=j; x<j+TILE; x++ )
                        for ( int z=k; z<k+TILE; z++ )
                            m_3[y][x] += m_1[y][z]*m_2[z][x];
}

void print_matrix(int m_3[][MAX], int rows, int columns)
{
	cout << "Output Matrix:" << endl;
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < columns; ++j)
		{
			cout << m_3[i][j] << " ";
			if(j == columns - 1)
				cout << endl << endl;
		}
	}
}

void loop_1(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
					int rows_1, int columns_1, int rows_2, int columns_2)
{
	for(int i = 0; i < rows_1; ++i)
	{
		for(int j = 0; j < columns_2; ++j)
		{
			for(int k=0; k<columns_1; ++k)
			{
				m_3[i][j] += m_1[i][k] * m_2[k][j];
			}
		}
	}

}
void loop_2(int m_1[][MAX], int m_2[][MAX], int m_3[][MAX], 
					int rows_1, int columns_1, int rows_2, int columns_2)
{
	for(int j = 0; j < rows_1; ++j)
	{
		for(int i = 0; i < columns_2; ++i)
		{
			for(int k=0; k<columns_1; ++k)
			{
				m_3[i][j] += m_1[i][k] * m_2[k][j];
			}
		}
	}
}