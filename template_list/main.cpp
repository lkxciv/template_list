#include <iostream>

template<class T> 
class sllist_elem
{
public:
	T value;
	sllist_elem<T> *next;

	sllist_elem(sllist_elem<T> *next = NULL);
	//mit value initialisieren
	sllist_elem(T value, sllist_elem<T> *next = NULL);
};

template<class T>
sllist_elem<T>::sllist_elem(sllist_elem<T>* next) : next(next){}

template<class T>
sllist_elem<T>::sllist_elem(T value, sllist_elem<T>* next) : value(value), next(next){}

template<class T>
class sllist
{
private:
	sllist_elem<T> *head;
	//! Verhindert duplikation zw. copy konstr und assignment
	void deepCopy(const sllist<T> & orig);
	//gibt pointer auf stelle in liste zur�ck
	sllist_elem<T> *ptr_pos(unsigned int pos);
public:
	//Standardkonstr. mit optionalem Head
	sllist(sllist_elem<T> *head = NULL);
	//Konstr. zum angeben der ben�tigtem elemente
	sllist(unsigned int elems);
	//Copykonstr
	sllist(const sllist<T> & orig);
	//Movekonstr
	sllist(sllist<T> && move);
	//Destr
	~sllist();

	//Copy zuweisungsoperator
	sllist<T> & operator=(const sllist<T> & orig);
	//Move zuweisungsoperator
	sllist<T> & operator=(sllist<T> && move);

	//returnt value an stelle(ab 0)
	T get(unsigned int pos);
	//wert an Stelle setzten
	void set(unsigned int pos, T value);
	//gibt gr��e zur�ck
	unsigned int length();

};

template<class T>
void sllist<T>::deepCopy(const sllist<T> & orig)
{
	if (orig.head == NULL)
	{
		head = NULL;
		return;
	}
	//erstes elem zuweisen und auch head geben
	sllist_elem<T> *origwalker = orig.head;
	sllist_elem<T> *copywalker = new sllist_elem<T>(origwalker->value);
	head = copywalker;
	//solang next vorhanden weitermachen
	while (origwalker->next != NULL)
	{
		copywalker->next = new sllist_elem<T>();
		copywalker = copywalker->next;
		origwalker = origwalker->next;
		copywalker->value = origwalker->value;
	}
}

template<class T>
sllist_elem<T> *sllist<T>::ptr_pos(unsigned int pos)
{
	sllist_elem<T> *walker = head;
	//bei null garnicht
	for (unsigned int i = 0; i < pos && walker != NULL; i++)
	{
		walker = walker->next;
	}
	return walker;
}

template<class T>
sllist<T>::sllist(sllist_elem<T>* head) : head(head){}

//elems ab 1
template<class T>
sllist<T>::sllist(unsigned int elems)
{
	if (elems == 0)
	{
		head = NULL;
		return;
	}
	head = new sllist_elem<T>();
	sllist_elem<T> *walker = head;
	//weiter elems dazu machen, bevor man auf
	//next geht erst next g�ltige adresse geben
	for (unsigned int i = 1; i < elems; i++)
	{
		walker->next = new sllist_elem<T>();
		walker = walker->next;
	}
}

template<class T>
sllist<T>::sllist(const sllist<T> & orig)
{
	deepCopy(orig);
}

template<class T>
sllist<T>::sllist(sllist<T> && move)
{
	//head wird �bergeben
	this->head = move.head;
	move.head = NULL;
}

//!
template<class T>
sllist<T>::~sllist()
{
	sllist_elem<T> *last = head;
	sllist_elem<T> *walker = head;
	head = NULL;
	//walker geht weiter, last l�scht das alte
	while (last != NULL)
	{
		walker = walker->next;
		delete last;
		last = walker;
	}
}

//! Muss immer *this returnen
template<class T>
sllist<T> & sllist<T>::operator=(const sllist<T> & orig)
{
	//! so destruktor auf this callen
	//! delete this nicht bei stack alloc m�glich
	this->~sllist();
	this->deepCopy(orig);
	return *this;
}

//! return *this
template<class T>
sllist<T> & sllist<T>::operator=(sllist<T> && move)
{
	this->~sllist();
	this->head = move.head;
	move.head = NULL;
	return *this;
}

template<class T>
T sllist<T>::get(unsigned int pos)
{
	return ptr_pos(pos)->value;
}

template<class T>
void sllist<T>::set(unsigned int pos, T value)
{
	ptr_pos(pos)->value = value;
}

template<class T>
unsigned int sllist<T>::length()
{
	unsigned int len = 0;
	sllist_elem<T> *walker = head;
	for ( ; walker != NULL; len++)
	{
		walker = walker->next;
	}
	return len;
}

int main()
{
	sllist<int> test1(3);
	sllist<int> test2(2);
	test2 = test1;
	
	return 0;
}