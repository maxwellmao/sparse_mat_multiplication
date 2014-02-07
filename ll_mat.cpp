#include "ll_mat.h"
#include <time.h>
#include <assert.h>
#include <getopt.h>

LLMat::LLMat(int row, int col, int preSize)
{
    this->dim[0]=row;
    this->dim[1]=col;
    this->val.reserve(preSize);
    this->col.reserve(preSize);
    this->link.reserve(preSize);
    this->root.resize(row, -1);
}

LLMat::LLMat(int preSize)
{
    this->val.reserve(preSize);
    this->col.reserve(preSize);
    this->link.reserve(preSize);
    this->root.reserve(1000);
}
//template <class T>
void output_vector(vector<int> v, string name)
{
	cout << name << endl;
	for(vector<int>::iterator it=v.begin(); it!=v.end(); it++)
	{
		cout << *it << " " ;
	}
	cout << endl;
}

void LLMat::set_mat_no_iteration(int i, int j, double v)
{
    if(i>=this->root.size())
    {
        this->root.push_back(this->val.size());
		this->last.push_back(this->link.size());
        this->val.push_back(v);
        this->col.push_back(j);
        this->link.push_back(-1);
        assert(i==this->root.size()-1);
		assert(this->root.size()==this->last.size());
    }
    else
    {
		this->link[this->last[i]]=this->val.size();
		this->last[i]=this->link.size();
		this->val.push_back(v);
		this->col.push_back(j);
		this->link.push_back(-1);
		assert(this->root.size()==this->last.size());
    }
    assert(this->val.size()==this->col.size());
    assert(this->col.size()==this->link.size());
}

void LLMat::set_mat(int i, int j, double v)
{
    if(i>=this->root.size())
    {
        this->root.push_back(this->val.size());
        this->val.push_back(v);
        this->col.push_back(j);
        this->link.push_back(-1);
        assert(i==this->root.size()-1);
    }
    else
    {
        if(this->root[i]==-1)
        {
            this->root[i]=this->val.size();
            this->val.push_back(v);
            this->col.push_back(j);
            this->link.push_back(-1);
        }
        else
        {
            int next=this->root[i];
            while(this->link[next]!=-1 and this->col[next]!=j)
            {
                next=this->link[next];
            }
            if(this->link[next]==-1)
            {
                this->link[next]=this->val.size();
                this->val.push_back(v);
                this->col.push_back(j);
                this->link.push_back(-1);
            }
            else
            {
                this->val[next]=v;
            }
        }
    }
    assert(this->val.size()==this->col.size());
    assert(this->col.size()==this->link.size());
}

void LLMat::output()
{
   for(int r=0; r<this->root.size(); r++)
   {
	   cout << "------" << r << "-------" << endl;
       for(int c=this->root[r]; c!=-1; c=this->link[c])
       {
           cout << this->fileOriginalID[r] << " " << this->col[c] << " " << this->val[c] << endl;
       }
   }
   cout << "col size:" << this->col.size() << endl;
   output_vector(this->col, "col");
   cout << "val size:" << this->val.size() << endl;
//   output_vector(this->val, "val");
   cout << "link size:" << this->link.size() << endl;
   output_vector(this->link, "link");
   cout << "root size:" << this->root.size() << endl;
   output_vector(this->root, "root");
}

void LLMat::multiplication_xxT(bool sym, bool local)
{
//	cout << "Multiplication x*x^T" << endl;
    for(int i=0; i<this->root.size(); i++)
    {
        vector<int> i_nonzero;//the column of non zero entry for row i
        for(int c=this->root[i]; c!=-1; c=this->link[c])
        {
            i_nonzero.push_back(this->col[c]);
//			cout << "F:" << this->fileOriginalID[i] << "-> M:" << this->col[c] << endl;
        }
        for(int j=i+1; j<this->root.size(); j++)
        {
            double sum=0.0;
            int i_index=0;
            for(int j_c=this->root[j]; j_c!=-1; j_c=this->link[j_c])
            {
//				cout << "F:" << this->fileOriginalID[j] << "-> M:" << this->col[j_c] << endl;
                while(i_index<i_nonzero.size() and i_nonzero[i_index]<this->col[j_c])
                {
                    i_index++;
                }
				if(i_index>=i_nonzero.size())
					break;
                if(i_nonzero[i_index]==this->col[j_c])
                {
                    sum+=this->val[j_c]*this->val[j_c];
                }
            }
			if(sum>0)
			{
				if(local){
    	        	cout << this->fileOriginalID[i] << "\t" << this->fileOriginalID[j] << "\t" << sum << endl;
        	    	cout << this->fileOriginalID[j] << "\t" << this->fileOriginalID[i] << "\t" << sum << endl;
				}
				else
				{
					if(sym)
					{
	    	        	cout << this->fileOriginalID[i] << ":" << this->fileOriginalID[j] << "\t" << sum << endl;
	        	    	cout << this->fileOriginalID[j] << ":" << this->fileOriginalID[i] << "\t" << sum << endl;
					}
					else
		        	    cout << this->fileOriginalID[i] << "\t" << this->fileOriginalID[j] << "\t" << sum << endl;
				}
			}
        }
    }
}

void LLMat::output_cerr()
{
	cerr << "col size:" << this->col.size() << endl;
	cerr << "val size:" << this->val.size() << endl;
	cerr << "link size:" << this->link.size() << endl;
	cerr << "root size:" << this->root.size() << endl;
}

void construct_mat_from_stream(int preSize, bool sym, bool local)
{
    string mStr, fStr;
    LLMat llMat=LLMat(preSize);
    int mID=-1;
    string lastM="";
	clock_t start, end;
	start=clock();
    while(cin>>mStr)
    {
        cin>>fStr;
        if(lastM!=mStr)
        {
            mID++;
			lastM=mStr;
        }
        map<string, int>::iterator fIt=llMat.fileIndexMap.find(fStr);
        if(fIt==llMat.fileIndexMap.end())
        {
            llMat.fileIndexMap.insert(make_pair(fStr, llMat.fileIndexMap.size()));
            llMat.fileOriginalID.push_back(fStr);
			llMat.set_mat_no_iteration(llMat.fileOriginalID.size()-1, mID, 1.0);
//            llMat.set_mat(llMat.fileOriginalID.size()-1, mID, 1.0);
//			cout << "seting " << llMat.fileOriginalID.size()-1 << "\t" << mID << endl;
        }
        else
        {
			llMat.set_mat_no_iteration(fIt->second, mID, 1.0);
//            llMat.set_mat(fIt->second, mID, 1.0);
//			cout << "seting " << fIt->second << "\t" << mID << endl;
        }
    }
	end=clock();
	cerr << "Constructing matrix time consuming:" << (double)(end-start)/CLOCKS_PER_SEC << "s" << endl;
//	cout << "File no.:" << llMat.fileOriginalID.size() << endl;
//	cout << "Machine no.:" << mID+1 << endl;
//	cout << "Output matrix:" << endl;
//	llMat.output();
	llMat.output_cerr();
	cerr << "Machine No.:" << mID << endl;
	start=clock();
	llMat.multiplication_xxT(sym, local);
	end=clock();
	cerr << "Multiplying matrix time consuming:" << (double)(end-start)/CLOCKS_PER_SEC << "s"<< endl;
	cerr << "Finished!" << endl;
}


char* const short_options="ms:l";
struct option long_options[]={
	{"preSize", 0, NULL, 's'},
	{"sym", 0, NULL, 'm'},
	{"local", 0, NULL, 'l'},
	{0,0,0,0},
};
void usage(char *prog_name, const char *more){
	cerr << more;
	cerr << "Usage: " << prog_name << "[-s] [-m] [-l]" << endl;
	cerr << "-s pre-allocate for file-node vector" << endl;
	cerr << "-m set this flag if in map stage" << endl;
	cerr << "-l set this flag if run in local" << endl;
	exit(0);
}

int main(int argc, char* argv[])
{
	int result;
	int preSize=3000000;
	bool sym=false;
	bool local=false;
	while( (result = getopt_long(argc, argv, short_options, long_options, NULL)) != -1 )
	{
		switch(result)
		{
		case 's':
			preSize=atoi(optarg);
			break;
		case 'm':
			sym=true;
			break;
		case 'l':
			local=true;
			break;
		default:
			usage(argv[0], "Unknown parameters\n");
			break;
		}
	}
	cerr << "PreSize:" << preSize << endl;
	cerr << "Sym:" << sym << endl;
    construct_mat_from_stream(preSize, sym, local);
    return 0;
}
