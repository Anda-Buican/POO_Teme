#include <iostream>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;



class Nod {
public:
	int info;
	Nod* prev;
	Nod* next;

	Nod();
	Nod(int, Nod*, Nod*);
	~Nod();
};

//constructori

Nod::Nod()
{
	this->info = 0;
	this->prev = NULL;
	this->next = NULL;
}

Nod::Nod(int info, Nod* prev, Nod* next)
{
	this-> info = info;
	this->prev = prev;
	this->next = next;
}

//destructor

Nod::~Nod()
{
}



class Lista_dublu_inlantuita {
private:
	Nod* prim;
	Nod* ultim;
public:
	Lista_dublu_inlantuita();
	~Lista_dublu_inlantuita();
	void add(int val, int poz);	    //adaugarea unui element pe o pozitie
	void add_prim(int val);			//adaugarea unui element in fata listei
	void add_ultim(int val);		//adaugarea unui element in spatele listei
	void del(int poz);				//stergerea unui element de pe o pozitie
	friend ostream& operator <<(ostream& out, Lista_dublu_inlantuita&);  //supraincarcarea operatorului <<
	friend istream& operator >>(istream& in, Lista_dublu_inlantuita&);	//supraincarcarea operatorului >>
	friend Lista_dublu_inlantuita& operator +(Lista_dublu_inlantuita& stg, Lista_dublu_inlantuita& dr);	//supraincarcarea operatorului +
};

//constructori

Lista_dublu_inlantuita::Lista_dublu_inlantuita()
{
	this->prim = NULL;
	this->ultim = NULL;
}

//destructor

Lista_dublu_inlantuita::~Lista_dublu_inlantuita()
{
	Nod* it = prim;
	Nod* del;
	while (it!= NULL)
	{
		del = it;
		it = it->next;
		delete del;
	}

}

//metoda de adaugare a unui element pe o pozitie

void Lista_dublu_inlantuita::add(int val, int poz)
{
	if (prim == NULL && poz>0)
		return;
	if (poz < 0)
		return;
	if (poz == 0)
	{
		add_prim(val);
		return;
	}
	Nod* it = prim;
	for (int i = 1; i <= poz - 1; i++)
	{
		if (it->next == NULL)  //daca pozitia nu exista, il adauga ultimul 
		{
			add_ultim(val);
			return;
		}
		it = it->next;

	}
	Nod* nou = new Nod(val, it, it->next);
	it->next = nou;
	nou->next->prev = nou;
}

void Lista_dublu_inlantuita::add_prim(int val)
{
	if (prim == NULL)
	{
		prim = new Nod(val, NULL, NULL);
		ultim = prim;
	}
	else
	{
		Nod* next = new Nod(val, NULL, prim);
		prim->prev = next;
		prim = next;
	}
}
void Lista_dublu_inlantuita::add_ultim(int val)
{
	if (prim == NULL)
	{
		prim = new Nod(val, NULL, NULL);
		ultim = prim;
	}
	else
	{
		Nod* next = new Nod(val, ultim, NULL);
		ultim->next = next;
		ultim = next;
	}
}

void Lista_dublu_inlantuita::del(int poz)
{
	Nod* it = prim;
	if (it == NULL && poz > 0)
		return;
	if (poz < 0)
		return;
	if (poz == 0 && prim == ultim)
	{
		delete prim;
		prim = ultim = NULL;
	}
	else if (poz == 0)
	{
		prim = it->next;
		prim->prev = NULL;
		delete it;
	}
	else
	{
		for (int i = 1; i < poz; i++)
		{
			if (it == NULL)
				return;
			it = it->next;
		}
		Nod* deleted = it->next;
		if (deleted == NULL)
			return;
		it->next = it->next->next;
		if (it->next != NULL)
		{
			it->next->prev = it;
		}
	}

}

ostream& operator<<(ostream& out, Lista_dublu_inlantuita& l)
{
	Nod* it = l.prim;
	while(it!=NULL)
	{
		cout << it->info<<" ";
		it = it->next;
	}
	return out;
}

istream& operator>>(istream& in, Lista_dublu_inlantuita& l)
{
	int x;
	cin >> x;
	do
	{
		
		l.add_ultim(x);
		cin >> x;
	} while (x);
	return in;
}
Lista_dublu_inlantuita& operator+(Lista_dublu_inlantuita& stg, Lista_dublu_inlantuita& dr)
{
	Nod* it = stg.prim;
	Lista_dublu_inlantuita* nou= new Lista_dublu_inlantuita;
	while (it != NULL)
	{
		nou->add_ultim(it->info);
		it = it->next;
	}
	it = dr.prim;
	while (it != NULL)
	{
		nou->add_ultim(it->info);
		it = it->next;
	}
	return*nou;

}
int main()
{
	Lista_dublu_inlantuita lista;
	cin >> lista;
	lista.add(5,0);
	lista.add(4,0);
	lista.add(3,0);
	lista.add_prim(2);
	lista.add_ultim(9);
	cout << lista<<endl;
	lista.add(7, 3);
	cout << lista<<endl;
	lista.del(1);
	cout << lista;
	Lista_dublu_inlantuita lista2;
	cin >> lista2;
	cout << lista + lista2;
	return 0;
}
