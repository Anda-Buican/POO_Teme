#include <iostream>
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;

class Numar_Complex {
private:
	int real;
	int imaginar;
public:
	Numar_Complex(int, int);                     ///constructor initializare
	Numar_Complex(const Numar_Complex&);                     ///constructor copiere
	~Numar_Complex();                            ///destructor
	void set_real(int);                     ///set
	void set_imaginar(int);                 ///set
	int get_real() { return real; };           ///get
	int get_imag() { return imaginar; };       ///get
	void afisare(ostream& out);
	void citire(istream& in);
	friend istream& operator>>(istream& in, Numar_Complex& z);  ///supraincarcare pe >>
	friend ostream& operator<<(ostream& out, Numar_Complex& z); ///supraincarcare pe <<
	double modul(); ///functia modul

	Numar_Complex& operator=(Numar_Complex& z); ///supraincarcarea operatorului de atribuire (doar ca metoda nu ca functie friend)
	friend Numar_Complex& operator+(Numar_Complex& z1, Numar_Complex& z2); ///supraincarcare operator +
	friend Numar_Complex& operator*(Numar_Complex& z1, Numar_Complex& z2); ///supraincarcare operator *
	friend Numar_Complex& operator/(Numar_Complex& z1, Numar_Complex& z2); ///supraincarcare operator /

	friend class Vector_Complex;

};
Numar_Complex::Numar_Complex(int real = 0, int imaginar = 0) {
	this->real = real;
	this->imaginar = imaginar;
}
Numar_Complex::Numar_Complex(const Numar_Complex& z) {
	this->real = z.real;
	this->imaginar = z.imaginar;
}
Numar_Complex::~Numar_Complex() {
	this->real = 0;
	this->imaginar = 0;
}
void Numar_Complex::set_real(int x) {
	real = x;
}
void Numar_Complex::set_imaginar(int y) {
	imaginar = y;
}
void Numar_Complex::citire(istream& in) {
	cout << "Cititi partea reala: ";
	in >> real;
	cout << "Cititi partea imaginara: ";
	in >> imaginar;
}
istream& operator>>(istream& in, Numar_Complex& z) {
	z.citire(in);
	return in;
}
void Numar_Complex::afisare(ostream& out) {
	if (imaginar == 0) {
		out << real;
	}
	else {
		if (imaginar < 0) {
			out << real << imaginar << "*i";
		}
		else {
			out << real << "+" << imaginar << "*i";
		}
	}
}
ostream& operator<<(ostream& out, Numar_Complex& z) {
	z.afisare(out);
	return out;
}
double Numar_Complex::modul() {
	return sqrt(real * real + imaginar * imaginar);
}
Numar_Complex& Numar_Complex::operator=(Numar_Complex& z) {
	real = z.real;
	imaginar = z.imaginar;
	return *this;
}
inline Numar_Complex& operator+(Numar_Complex& z1, Numar_Complex& z2) {
	Numar_Complex* z = new Numar_Complex;
	z->real = z1.real + z2.real;
	z->imaginar = z1.imaginar + z2.imaginar;
	return *z;
}
inline Numar_Complex& operator*(Numar_Complex& z1, Numar_Complex& z2) {
	Numar_Complex* z = new Numar_Complex;
	z->real = z1.real * z2.real - z1.imaginar * z2.imaginar;
	z->imaginar = z1.real * z2.imaginar + z2.real * z1.imaginar;
	return *z;
}
Numar_Complex& operator/(Numar_Complex& z1, Numar_Complex& z2) {
	Numar_Complex* z = new Numar_Complex;
	z->real = (z1.real * z2.real + z1.imaginar * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
	z->imaginar = (z2.real * z1.imaginar - z1.real * z2.imaginar) / (z2.real * z2.real + z2.imaginar * z2.imaginar);
	return *z;
}

class Vector_Complex
{
private:
	int n;
	Numar_Complex* v; //vectorul de numere complexe
public:
	Vector_Complex(Numar_Complex, int);  //constructor cu un nr dat de componente de aceeasi valoare
	Vector_Complex(int);				// constructor pentru initializare
	Vector_Complex(); //constructor gol		
	Vector_Complex(Vector_Complex&);		//constructor de copiere
	~Vector_Complex();					//destructor
	friend istream& operator>>(istream& in, Vector_Complex& z);  ///supraincarcare pe >>
	friend ostream& operator<<(ostream& out, Vector_Complex& z); ///supraincarcare pe <<
	double* vect_mod(int&);			//metoda de creare vector de module
	void sort();						//metoda de sortare a vectorului
	Numar_Complex sum();				//metoda de adunare
};

//constructori
Vector_Complex::Vector_Complex()
{
	n = 0;
	v = NULL;
}

Vector_Complex::Vector_Complex(Numar_Complex x, int nr)
{
	n = nr;
	v = new Numar_Complex[nr];
	for (int i = 0; i < nr; i++)
		v[i] = x;
}

Vector_Complex::Vector_Complex(int x)
{
	v = new Numar_Complex[x];
	n = x;
}

// constructor de copiere
Vector_Complex::Vector_Complex(Vector_Complex& y)
{
	this->n = y.n;
	if (this->n == 0)
	{
		this->v = NULL;
		return;
	}
	this->v = new Numar_Complex[n];
	for (int i = 0; i < n; i++)
		this->v[i] = y.v[i];
}

//destructor
Vector_Complex::~Vector_Complex()
{
	if (v != NULL)
	{
		delete[] v;
	}
}


//citirea

istream& operator>>(istream& in, Vector_Complex& z)
{
	for (int i = 0; i < z.n; i++)
		in >> z.v[i];
	return in;
}

//afisarea
ostream& operator<<(ostream& out, Vector_Complex& z)
{
	out << "[";
	for (int i = 0; i < z.n - 1; i++)
		out << z.v[i] << ", ";
	out << z.v[z.n - 1];
	out << "]";
	return out;
}
//functia modul
double* Vector_Complex::vect_mod(int& nr)
{
	nr = n;
	double* vmodul = new double[n];
	for (int i = 0; i < n; i++)
		vmodul[i] = v[i].modul();
	return vmodul;
}
//functia de comparare
int compNC(const void* a, const void* b)
{
	Numar_Complex c = *(Numar_Complex*)a;
	Numar_Complex d = *(Numar_Complex*)b;
	if (c.modul() < d.modul())
		return -1;
	else
		return 1;
}
//functia de sortare
void Vector_Complex::sort()
{
	qsort(v, n, sizeof(Numar_Complex), compNC);
}
//suma tuturor elementelor vectorului
Numar_Complex Vector_Complex::sum()
{
	Numar_Complex suma;
	for (int i = 0; i < n; i++)
		suma = suma + v[i];
	return suma;

}

int main()
{
	Vector_Complex vec_comp(3);
	cin >> vec_comp;			//citeste elementele complexe ale vectorului vec_comp
	Vector_Complex vec_comp2(vec_comp);    //copiaza vectorul vec_comp

	cout << "Vectorul complex: " << vec_comp << endl;				//afiseaza vectorul vec_comp
	cout << "Copie a vectorului complex: " << vec_comp2 << endl;			//afiseaza vectorul vec_comp2
	int nr;
	double* vec_modul = vec_comp2.vect_mod(nr);
	cout << "Vectorul de module: [";
	for (int i = 0; i < nr - 1; i++)
		cout << vec_modul[i] << " , ";		//afiseaza vectorul de module
	cout << vec_modul[nr - 1] << "]";
	cout << endl;
	vec_comp.sort();			//sorteaza vectorul vec_comp dupa module
	cout << "Vectorul de module sortat: " << vec_comp << endl;
	Numar_Complex s = vec_comp.sum(); //s este suma tuturor elementelor vectorului
	cout << "Suma elementelor vectorului: " << s;
	return 0;
}