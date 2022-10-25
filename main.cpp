#include <iostream>
#include <vector>
#include "./utility.hpp"

using namespace std;

// add
// subtract
// multiply
// determinant

/** Place-holder declarations **/

vector<vector<float>> add(vector<vector<float>>& m1, vector<vector<float>>& m2)
{
	vector<vector<float>> res;
	if (m1.size() != m2.size()) {cout << "Invalid input matrix" << endl; return res;}
	
	vector<float> foo;
	foo.reserve(m1[0].size());
	
	for (int i=0; i<m1.size(); i++)
	{
		for (int j=0; j<m1[0].size(); j++)
		{
			foo.push_back(m1[i][j] + m2[i][j]);
		}
		res.push_back(foo);
		foo.clear();
	}
	
	return res;
}

vector<vector<float>> subtract(const vector<vector<float>>& m1, const vector<vector<float>>& m2)
{
	vector<vector<float>> res;
	if (m1.size() != m2.size()) {cout << "Invalid input matrix" << endl; return res;}
	
	vector<float> foo;
	foo.reserve(m1[0].size());
	
	for (int i=0; i<m1.size(); i++)
	{
		for (int j=0; j<m1[0].size(); j++)
		{
			foo.push_back(m1[i][j] - m2[i][j]);
		}
		res.push_back(foo);
		foo.clear();
	}
	
	return res;
}

vector<vector<float>> multiply(const vector<vector<float>>& m1, const vector<vector<float>>& m2)
{
	vector<vector<float>> res;
	if (m1[0].size() != m2.size()) {cout << "Invalid input matrix" << endl; return res;}
	
	vector<float> foo;
	int sum = 0;
	
	
	
	for (int i=0; i<m1.size(); i++)
	{
		for (int y=0; y<m2[0].size(); y++)
		{
			for (int j=0; j<m2.size(); j++)
			{
				sum += (m1[i][j] * m2[j][y]);
			}
			foo.push_back(sum);
			sum = 0;
		}
		res.push_back(foo);
		foo.clear();
	}
	
	return res;
}

vector<vector<float>> scale(const float& scalar, const vector<vector<float>>& mat)
{
	vector<vector<float>> res;

	for (int i=0;i<mat.size(); i++)
	{
		vector<float> foo;
		for (int j=0; j<mat.size(); j++)
		{
			foo.push_back(mat[i][j] * scalar);
		}
		res.push_back(foo);
		foo.clear();
	}

	return res;
}

vector<vector<float>> transpose(const vector<vector<float>>& mat)
{
	vector<vector<float>> res;
	if (mat.size() != mat[0].size()) {cout << "Invalid input matrix" << endl; return res;}
	
	int memo[mat.size()][mat[0].size()];

	for (int i=0; i<mat.size(); i++)
	{
		for (int j=0; j<mat[0].size(); j++)
		{
			memo[i][j] = mat[j][i];	
		}
	}

	// convert traditional array to 2d vector
	for (int i=0; i<mat.size(); i++)
	{
		vector<float> foo;
		for (int j=0; j<mat[0].size(); j++)
		{
			foo.push_back(memo[i][j]);
		}
		res.push_back(foo);
		foo.clear();
	}

	return res;
}

void print(const vector<vector<float>>& mat)
{
	for (int i=0; i<mat.size(); i++)
	{
		cout << "{";
		for (int j=0; j<mat[i].size(); j++)
		{
			cout << mat[i][j];
			if (j == mat[i].size()-1) {cout << "}";}
			else {cout << ", ";}
		}
		if (i != mat.size()-1) {cout << ",";}
		cout << "\n";
	}
	
	cout << "\n";
}

float det(const vector<vector<float>>& mat);

int minor(const vector<vector<float>>& mat, const int& row, const int& col)
{
	if (mat.size() != mat[0].size()) {cout << "Invalid input matrix" << endl; return 0;}
	
	vector<vector<float>> foo = mat; // make a copy of the original matrix
	foo.erase(foo.begin()+(row-1)); // delete row
	for (int i=0; i<foo.size(); i++) //delete column
	{
		foo[i].erase(foo[i].begin() + (col-1));
	}
	
	return det(foo);
}

vector<vector<float>> signChart(const vector<vector<float>>& mat)
{
	// sign chart tells you the co-factor of each element in the original matrix
	vector<vector<float>> res;
	if (mat.size() != mat[0].size()) {cout << "Invalid input matrix" << endl; return res;}
	
	vector<float> foo;
	for (int i=0; i<mat.size(); i++)
	{
		for (int j=0; j<mat[0].size(); j++)
		{
			foo.push_back((i+j)%2==0 ? minor(mat, i+1, j+1) : -minor(mat, i+1, j+1));
		}
		res.push_back(foo);
		foo.clear();
	}
	
	return res;
}

float det(const vector<vector<float>>& mat)
{
	if (mat.size() != mat[0].size()) {cout << "Invalid input matrix" << endl; return 0;} //ONLY SQUARE MATRIX HAS DETERMINANT
	if (mat.size() == 2) {return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];}
	
	// if matrix is larger than 2x2
	vector<vector<float>> sc = signChart(mat);
	float sum = 0;
	for (int i=0; i<sc.size(); i++)
	{
		sum += (sc[i][1] * mat[i][1]);
	}
	
	return sum;
}

vector<vector<float>> GaussianElimination(vector<vector<float>>& mat)
{
	vector<vector<float>> res = mat; // make a copy
	
	for (int diagonal=0; diagonal<res.size()-1; diagonal++)
	{
		for (int row=diagonal+1; row<res.size(); row++)
		{
			float x = (-res[row][diagonal] / res[diagonal][diagonal]);

			for (int col=diagonal; col<res[0].size(); col++)
			{
				res[row][col] += (x*res[diagonal][col]);
			}
		}
	}

	return res;
}

float det2(vector<vector<float>>& mat)
{
	vector<vector<float>> foo = GaussianElimination(mat);
	float product = 1;
	
	for (int i=0; i<foo.size(); i++)
	{
		product *= foo[i][i];
	}

	return product;
}

float matRank(vector<vector<float>>& mat)
{
	vector<vector<float>> foo = GaussianElimination(mat);
	int r = 0;

	for (int i=0; i<foo.size(); i++)
	{
		bool isNonZero = 0;
		for (int j=0; j<foo[0].size(); j++)
		{
			if (foo[i][j] != 0) {
				isNonZero = 1;
				break;
			}
		}
		if (isNonZero) {r++;}
	}

	return r;
}

vector<vector<float>> inverse(const vector<vector<float>>& mat)
{
	return scale(1/det(mat), transpose(signChart(mat)));  
	// return transpose(signChart(mat));
	// return (det(mat));
	
}

vector<vector<float>> identity(vector<vector<float>>& mat)
{
	vector<vector<float>> res;
	res.reserve(mat.size());
	if (mat.size() != mat[0].size()) {cout << "Invalid input matrix"; return res;}
	
	vector<float> foo(mat[0].size(), 0);
	for (int i=0; i<mat.size(); i++)
	{
		res.push_back(foo);
		for (int j=0; j<mat[0].size(); j++)
		{
			if (i == j) {res[i][j] = 1;}
		}
	}
	return res;
}

int exist(const vector<vector<vector<float>>>& list, const int& index)
{
	if (index > list.size()-1)
	{
		cout << "No such matrix exists!\n";
		return 0;
	}
	
	return 1;
}

void save(vector<vector<float>>& mat, vector<vector<vector<float>>>& list)
{
	if (mat.size() == 0) {return;}
	cout << "Do you want to save matAns to the matrix list? (1) / (0): ";
	int yes;
	cin >> yes;
	
	if (!yes) {return;}
	
	list.push_back(mat);
	mat.clear();
}

int main()
{
	vector<vector<float>> mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, matAns, tmpMat;
	vector<float> tmpRow;
	int flag = 1, foo, foo2;
	char option;
	
	mat1 = {
			{1, 1, 1, 1},
			{1, 1, 1, 1},
			{1, 1, 1, 1},
			{1, 1, 1, 1}
	};
	
	mat2 = {
			{2, 2, 2, 2},
			{2, 2, 2, 2},
			{2, 2, 2, 2},
			{2, 2, 2, 2}
	};
	
	mat3 = {
			{1, 1},
			{1, 1}
	};
	
	mat4 = {
			{1, 0},
			{0, 1}
	};
	
	mat5 = {
			{1,  2, 3},
			{-2, 1, 4},
			{-3,-4, 1}
	};
	
	mat6 = {
			{1,  2, 3, 4},
			{-2, 1, 4, 3},
			{-3,-4, 1, 2},
			{-4,-3,-2, 1}
	};
	
	mat7 = {
			{1, 1, 1},
			{1, 1, 1},
			{1, 1, 1}
	};
	vector<vector<vector<float>>> M_list = {mat1, mat2, mat3, mat4, mat5, mat6, mat7};
	
	while (flag) {
		cout << "Matrices operations: (n)ew matrix, (a)dd, (s)ubtract, (m)ultiply, (t)ranpose, (d)eterminant, (D)et2, (r)ank, (i)dentity, in(v)erse, (p)rint, sign (c)hart, row Ech(e)lon form" << endl << ">>> ";
		scanf(" %c", & option);
		
		switch (option) {
			case 'n':
				int rows, cols;
				cout << "How many rows:\n>>> ";
				scanf(" %d", & rows);
				cout << "How many columns:\n>>> ";
				scanf(" %d", & cols);
				cout << "\nInput matrix:\n";
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						cin >> foo;
						tmpRow.push_back(foo);
					}
					tmpMat.push_back(tmpRow);
					tmpRow.clear();
				}
				M_list.push_back(tmpMat);
				tmpMat.clear();
				cout << " --> Matrix input successful\n";
				print(M_list[M_list.size() - 1]);
				break;
			
			case 'p':
				cout << "Which matrix to print:\n>>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				print(M_list[foo - 1]);
				break;
			
			case 'q':
				flag = 0;
				break;
			
			case 'a':
				cout << "Add matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				foo2 = foo;
				cout << "to matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo2 - 1)) {
					continue;
				}
				matAns = (add(M_list[foo2 - 1], M_list[foo - 1]));
				print(matAns);
				save(matAns, M_list);
				break;
			
			case 's':
				cout << "Add matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				foo2 = foo;
				cout << "to matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo2 - 1)) {
					continue;
				}
				matAns = (subtract(M_list[foo2 - 1], M_list[foo - 1]));
				print(matAns);
				save(matAns, M_list);
				break;
			
			case 't':
				cout << "Which matrix to transpose\n >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				matAns = transpose(M_list[foo-1]);
				print(matAns);
				save(matAns, M_list);
				break;
			
			case 'm':
				cout << "Multiply matrix >>>";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				foo2 = foo;
				cout << "with matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo2 - 1)) {
					continue;
				};
				matAns = (multiply(M_list[foo2 - 1], M_list[foo - 1]));
				print(matAns);
				save(matAns, M_list);
				break;
			
			case 'd':
				cout << "Find the determinant of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				cout << "det(mat" << foo << ") = " << det(M_list[foo - 1]) << endl;
				break;
			
			case 'D':
				cout << "Find the determinant2 of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				cout << "det2(mat" << foo << ") = " << det2(M_list[foo - 1]) << endl;
				break;

			case 'r':
				cout << "Find the rank of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				cout << "rank(mat" << foo << ") = " << matRank(M_list[foo - 1]) << endl;
				break;

			case 'i':
				cout << "Find identity matrix of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo - 1)) {
					continue;
				}
				matAns = identity(M_list[foo-1]);
				print(matAns);
				save(matAns, M_list);
				break;
			
			case 'v':
			    cout << "Find the inversion of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo-1)) {
					continue;
				}
				matAns = inverse(M_list[foo-1]);
				print(matAns);
				save(matAns, M_list);
				break;

			case 'c':
				cout << "Find the signchart of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo-1)) {
					continue;
				}
				matAns = signChart(M_list[foo-1]);
				print(matAns);
				save(matAns, M_list);
				break;

			case 'e':
				cout << "Find the row Echelon form of matrix >>> ";
				scanf(" %d", & foo);
				if (!exist(M_list, foo-1)) {
					continue;
				}
				matAns = GaussianElimination(M_list[foo-1]);
				print(matAns);
				save(matAns, M_list);
				break;

			default:
				cout << "\n --> Inavlid option : " << option << endl;
				break;
		}
	}
	
	return 0;
}