//veronica242001
#include <iostream>
#include <cstring>
using namespace std;
class Nod
{
private:
	char info;
	Nod* next;

public:
	Nod(char a, Nod* urm);
	~Nod();
	char get_val();
	friend class Stiva_de_caractere;
};
Nod::Nod(char a, Nod* urm)
{

	this->info = a;
	this->next = urm;
}
Nod::~Nod()
{
	next = NULL;

}

char Nod::get_val()
{
	return info;
}

class Stiva_de_caractere
{
	Nod* varf;
public:
	Stiva_de_caractere();
	~Stiva_de_caractere();
	void push(char x);
	void pop();
	char top();
	int isempty();
	friend ostream& operator <<(ostream& out, Stiva_de_caractere&);  //supraincarcarea operatorului <<
	friend istream& operator >>(istream& in, Stiva_de_caractere&);	//supraincarcarea operatorului >>
	void inversare(char*);
	friend Stiva_de_caractere& operator-(Stiva_de_caractere& ob1, Stiva_de_caractere& ob2);  //supraincarcarea operatorului -
	static void citire_afisare();

};
Stiva_de_caractere::Stiva_de_caractere()
{
	varf = NULL;
}
Stiva_de_caractere::~Stiva_de_caractere()
{
	Nod* elem = varf;
	while (elem != NULL)
	{
		varf = varf->next;
		delete elem;
		elem = varf;
	}
}
void Stiva_de_caractere::push(char x)
{
	Nod* aux = new Nod(x,varf);
	varf = aux;
}
void Stiva_de_caractere::pop()
{
	Nod* elem = varf;
	if (varf != NULL)
	{
		varf = varf->next;
		delete elem;
	}
	
}
char Stiva_de_caractere::top()
{
	return varf->info;
}

int Stiva_de_caractere::isempty()
{
	if (varf == NULL)
		return 1;
	return 0;
}
ostream& operator<<(ostream& out, Stiva_de_caractere& s )
{
	while (!s.isempty())
	{
		out << s.top() << " ";
		s.pop();
	}
	return out;

}
istream& operator>>(istream& in, Stiva_de_caractere& s)
{
	char x;
	in >> x;
	while (x != '*')
	{
		s.push(x);
		in >> x;
	}
	return in;
}
void Stiva_de_caractere::inversare(char* sir)
{
	for (int i = 0; i < strlen(sir); i++)
		push(sir[i]);
	for (int i = 0; i < strlen(sir); i++)
	{		
		sir[i] = top();
		pop();
	}
		
}
void Stiva_de_caractere::citire_afisare()
{
	int n;
	cout << "Introduceti numarul de stive: ";
	cin >> n;
	cout << "introduceti caracterele din stiva separate printr-un spatiu, finalizate de *";
	Stiva_de_caractere* v = new Stiva_de_caractere[n];
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << v[i] << endl;
	}
	delete[] v;
}
Stiva_de_caractere& operator-(Stiva_de_caractere& ob1, Stiva_de_caractere& ob2)
{
	Stiva_de_caractere* s3= new Stiva_de_caractere;
	Nod* v1 = ob1.varf;
	Nod* v2 =ob2.varf;
	while (v1 != NULL and v2 != NULL)
	{
		if (v1->get_val() > v2->get_val())
			s3->push(v1->get_val());
		else
			s3->push(v2->get_val());
		ob1.pop();
		ob2.pop();
		v1 = ob1.varf;
		v2 =ob2.varf;
	}
	return *s3;

}

//char sir[256];
int main()
{
	Stiva_de_caractere st;
	st.push('5');
	st.push('4');
	st.push('3');
	st.push('2');
	st.push('1');
	st.push('0');
	cout << st<<endl;
	st.push('5');
	st.push('4');
	st.push('3');
	st.push('2');
	st.push('1');
	st.push('0');
	Stiva_de_caractere st2;
	cin >> st2;
	cout << st2.isempty()<<endl;
	char c[] = "ana are mere";
	st.inversare(c);
	cout << c<<endl;
	cout << st - st2;
	Stiva_de_caractere::citire_afisare();
	return 0;
}