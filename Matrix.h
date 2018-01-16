#include <math.h>
#include <fstream>
#include <iostream>

class OutOfMem{};
class IndexOutOfRange{};
class WrongDim{};

class matrix{
	private:
		struct rcmatrix;
		rcmatrix* block;
	public:
		class Cref;

		matrix();
		matrix(const matrix& cm);
		matrix(std::fstream& fs);
		matrix(unsigned int nrows, unsigned int ncols, double var);
		matrix(unsigned int nrows, unsigned int ncols, double var1, double var2);
		void write(unsigned int i, double* c);
		double* read(unsigned int i) const;
		double* operator[](unsigned int i )const;
		matrix& operator=(const matrix& asOp);
		friend matrix operator +(const matrix&, const matrix&);
		matrix& operator +=(matrix&);
		friend matrix operator -(const matrix&, const matrix&);
		matrix& operator -=(matrix&);
		/*matrix operator *=;
		matrix operator *=;*/
		~matrix();
		friend std::ostream & operator << (std::ostream & s, const matrix & matrix);
		friend std::ostream & operator << (std::ostream & s, const matrix::Cref& s1);
		friend matrix operator* (const matrix&, const matrix&);
		void check(unsigned int i);
		Cref operator[](unsigned int i);

};



struct matrix::rcmatrix{
    double** data;
    unsigned int rows;
    unsigned int cols;
    unsigned int n;

    rcmatrix(){
        this->data=NULL;
        this->cols=0;
        this->rows=0;
        this->n=0;
    }

	rcmatrix(std::fstream& fs){
		fs >> this->rows;
		fs >> this->cols;

		try{
			this->data = new double*[this->rows];
			for(unsigned int i=0;i<this->rows;i++)
			this->data[i]=new double[this->cols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<this->rows;i++){
			for(unsigned int j=0;j<this->cols;j++){
				fs >> this->data[i][j];
			}
		}
		this->n=1;
	}

	rcmatrix(unsigned int nrows, unsigned int ncols, double var){
		try{
			this->data = new double*[nrows];
			for(unsigned int i=0;i<nrows;i++)
				this->data[i]=new double[ncols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<nrows;i++)
			for(unsigned int j=0;j<ncols;j++)
				data[i][j]=var;

		this->rows=nrows;
		this->cols=ncols;
		this->n=1;
	}

	rcmatrix(unsigned int nrows, unsigned int ncols, double var1, double var2){
		try{
			this->data = new double*[nrows];
			for(unsigned int i=0;i<nrows;i++)
				this->data[i]=new double[ncols];
			}
			catch(...){
				throw OutOfMem();
			}

			for(unsigned int i=0;i<nrows;i++)
				for(unsigned int j=0;j<ncols;j++)
					if(i==j)this->data[i][j]=var1;
					else this->data[i][j]=var2;

			this->rows=nrows;
			this->cols=ncols;
			this->n=1;
			};

	rcmatrix(unsigned int nrows, unsigned int ncols,double** lol){
		this->rows=nrows;
		this->cols=ncols;
		this->n=1;
		this->data = lol;
		}

	rcmatrix(const rcmatrix& lol){
		try{
			this->data = new double*[lol.rows];
			for(unsigned int i=0;i<lol.rows;i++)
				this->data[i]=new double[lol.cols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<lol.rows;i++)
			for(unsigned int j=0;j<lol.cols;j++)
				this->data[i][j]=lol.data[i][j];


		this->rows=lol.rows;
		this->cols=lol.cols;
		this->n=1;

	}

    ~rcmatrix(){
    for(unsigned int i=0;i<this->rows;i++)
    	delete[] data[i];
    delete[] data;
    }

    rcmatrix* detach(){
		if(n==1)
			return this;
        rcmatrix* t=new rcmatrix(*this);
        n--;
        return t;
    }
};

class matrix::Cref{
	friend class matrix;
	matrix& s;
	unsigned int i;

	Cref (matrix& ss, unsigned int ii): s(ss), i(ii){
		std::cout << "cref contructor CALLED\\n"<<std::endl;
	};

	public:
		operator double*() const{
			std::cout << "operator double* CALLED\\n"<<std::endl;
			return s.read(i);
		};

		matrix::Cref& operator = (double* c){
			std::cout << "operator = (double* c) CALLED\\n" << std::endl;
			s.write(i,c);
			return *this;
		};

		matrix::Cref& operator = (const Cref& ref){
			std::cout << "operator = (const Cref& ref) CALLED\\n" << std::endl;
			return operator = ((double*)ref);
		};

		friend std::ostream& operator<<(std::ostream&, const matrix::Cref&);
};


