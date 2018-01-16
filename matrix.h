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
		void write(unsigned int i, unsigned int j, double c);
		double read(unsigned int i, unsigned int j) const;
		double operator()(unsigned int i, unsigned int j) const;
		matrix& operator=(const matrix& asOp);
		friend matrix operator +(const matrix&, const matrix&);
		matrix& operator +=(matrix&);
		friend matrix operator -(const matrix&, const matrix&);
		matrix& operator -=(matrix&);
		friend matrix operator *(const matrix&, const matrix&);
		matrix& operator *=(const matrix&);
		bool operator ==(const matrix&);
		~matrix();
		friend std::ostream & operator << (std::ostream & s, const matrix & matrix);
		friend std::ostream & operator << (std::ostream & s, const matrix::Cref& s1);
		friend matrix operator* (const matrix&, const matrix&);
		void check(unsigned int i);
		Cref operator()(unsigned int i, unsigned int j);

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

	rcmatrix(unsigned int nrows, unsigned int ncols,double** l){
		this->rows=nrows;
		this->cols=ncols;
		this->n=1;
		this->data = l;
		}

	rcmatrix(const rcmatrix& l){
		try{
			this->data = new double*[l.rows];
			for(unsigned int i=0;i<l.rows;i++)
				this->data[i]=new double[l.cols];
		}
		catch(...){
			throw OutOfMem();
		}

		for(unsigned int i=0;i<l.rows;i++)
			for(unsigned int j=0;j<l.cols;j++)
				this->data[i][j]=l.data[i][j];


		this->rows=l.rows;
		this->cols=l.cols;
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
	unsigned int j;

	Cref (matrix& ss, unsigned int ii, unsigned int jj): s(ss), i(ii), j(jj){
		std::cout << "cref contructor CALLED"<<std::endl;
	};

	public:
		operator double() const{
			std::cout << "operator double CALLED"<<std::endl;
			return s.read(i, j);
		};

		matrix::Cref& operator = (double c){
			std::cout << "operator = (double c) CALLED" << std::endl;
			s.write(i, j, c);
			return *this;
		};

		matrix::Cref& operator = (const Cref& ref){
			std::cout << "operator = (const Cref& ref) CALLED" << std::endl;
			return operator = (ref);
		};

		friend std::ostream& operator<<(std::ostream&, const matrix::Cref&);
};


