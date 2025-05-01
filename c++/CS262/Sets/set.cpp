#include "set.h"
#include <exception>
#include <string>
#include <sstream>


using namespace std;

template <typename T>
Set<T>::Set() : s() {}

template <typename T>
Set<T>::Set(const vector<T>& v1) :s{v1.begin(), v1.end()} {}

template <typename T>
Set<T>::Set(const T a[], size_t size) : s{ a, a + size }  {}

template <typename T>
Set<T>::Set(std::initializer_list<T> l) : s{ l.begin(), l.end() } {}

template <typename T>
Set<T>::Set(const Set<T>& s1) : s(s1.s.begin(), s1.s.end()) {}

template <typename T>
size_t Set<T>::cardinality() const { return s.size(); }

template <typename T>
void Set<T>::insertElement(T n)
{
	s.insert(n);
}

template <typename T>
void Set<T>::removeElement(T n)
{
	s.erase(n);
}

template <typename T>
bool Set<T>::isElement(T n) const
{
	for (T elem : s)
	{
		if (elem == n)
		{
			return true;
		}
	}
	return false;
}

template <typename T>
void Set<T>::clear()
{
	s.clear();
}

template <typename T>
bool Set<T>::operator==(const Set& s1) const
{
	return this->s == s1.s;
}

template <typename T>
bool Set<T>::operator!=(const Set& s1) const
{
	return !(*this == s1);
}

template <typename T>
bool Set<T>::operator<(const Set<T>& s1) const
{
	if (this->cardinality() == s1.cardinality())
	{
		for (size_t i = 0; i < s1.cardinality(); ++i)
		{
			if ((*this)[i] < s1[i])
			{
				return true;
			}
			else if ( (*this)[i] > s1[i] )
			{
				return false;
			}
		}
	}
	else if (this->cardinality() < s1.cardinality())
		return true;
	return false;
}

template <typename T>
T Set<T>::operator[](size_t i) const
{
	typename set<T>::iterator beg;

	if (i < s.size() && i >= 0)
	{
		beg = s.begin();
		advance(beg, i);
	}
	else
		throw out_of_range("Index out of Range");

	return *beg;
}

template <typename S>
ostream& operator<<(std::ostream& out, const Set<S>& s1)
{
	vector<S> v{ s1.s.begin(), s1.s.end() };
	
	out << '{';
	for (size_t i = 0; i < v.size(); ++i)
	{
		if ( i != 0 )
			out << ", " << v[i];
		else
			out << v[i];
	}
	out << '}';
	return out;
}




