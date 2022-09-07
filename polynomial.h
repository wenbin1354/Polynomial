#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h> 
#include <cmath> 
#include <stack>

class HunPolynomial {

private:

	std::vector<int> coefficients;
	int coefCount;

public:

	HunPolynomial();

	HunPolynomial(const std::vector<int>& coef);

	void Set(const std::vector<int>& coef);

	HunPolynomial operator+(const HunPolynomial& other);

	HunPolynomial operator-(const HunPolynomial& other);

	HunPolynomial operator*(const HunPolynomial& other);

	float operator()(const float& point) const;

	friend std::ostream& operator<<(std::ostream& os, const HunPolynomial& output);

};