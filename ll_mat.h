#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class LLMat
{
private:
    int dim[2];         /* array dimension, the shape of matrix is dim[0]*dim[1] */
//    int issym;          /* non-zero, if obj represents a symmetric matrix */
//    int storeZeros;     /* whether to store zero values */
    int nnz;            /* number of stored items */
    int nalloc;         /* allocated size of value and index arrays */
    int free;           /* index to first element in free chain */
    vector<double> val;        /* all nonzero entry of matrix, the length of val is nnz */
    vector<int> col;           /* the column index of each entry, the length of val is nnz */
    vector<int> link;          /* the position of next nonzero entry in the same row, the length of link is nnz */
    vector<int> root;          /* the first nonzero entry of each row in the matrix, the length of root is n, and n is the number of rows in matrix */
	vector<int> last;		/* the last nonzero entry of each row in the matrix, the length of last is n, that is this->link[this->last[i]]=-1*/
public:
    void set_mat(int i, int j, double v);
	void set_mat_no_iteration(int i, int j, double v);
    LLMat(int row, int col, int preSize);
    LLMat(int preSize=10000);
    void output();
    void multiplication_xxT(bool sym=false, bool local=false);
    map<string, int> fileIndexMap;
    vector<string> fileOriginalID;
	void output_cerr();
};

