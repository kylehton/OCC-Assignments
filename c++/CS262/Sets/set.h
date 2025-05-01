#ifndef SET_H
#define SET_H

#include <vector>
#include <set>
#include <iostream>
#include <initializer_list>


template <typename T>
class Set
{
	template <typename S>
	friend std::ostream& operator<<(std::ostream& out, const Set<S>& s);
	
public:
	Set();
	Set(const std::vector<T>& v1);
	Set(const T a[], size_t size);
	Set(std::initializer_list<T> l);
	Set(const Set<T>& s1);

	size_t cardinality() const;
	void insertElement(T n);
	void removeElement(T n);
	bool isElement(T n) const;
	void clear();

	bool operator==(const Set<T>& s1) const;
	bool operator!=(const Set<T>& s1) const;
	bool operator<(const Set<T>& s1) const;
	T operator[](size_t i) const;

	Set<char> createSubset(const Set<char>& s, unsigned int len);

private:
	std::set<T> s;
};

#endif



