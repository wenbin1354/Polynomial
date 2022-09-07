#include "HunPolynomial.h"

HunPolynomial::HunPolynomial() : coefCount(1) {
	coefficients.push_back(0);
}

HunPolynomial::HunPolynomial(const std::vector<int>& coef) : coefCount(coef.size()), coefficients(coef) {}

void HunPolynomial::Set(const std::vector<int>& coef) {
	coefficients = coef;
	coefCount = coef.size();
}

HunPolynomial HunPolynomial::operator+(const HunPolynomial& other)
{
	HunPolynomial sum;
	int sizeSum = std::max(coefCount, other.coefCount);
	sum.coefCount = sizeSum;
	int sizeDifference = std::abs(coefCount - other.coefCount);
	sum.coefficients.clear();

	//have a vector for the operation
	std::vector<int> hold;
	for (int i{ 0 }; i < sizeDifference; i++) {
		hold.push_back(0);
	}

	if (coefCount > other.coefCount) {
		for (int i{ 0 }; i < other.coefCount; i++)
			hold.push_back(other.coefficients[i]);
		for (int i{ 0 }; i < sizeSum; i++) {
			sum.coefficients.push_back(coefficients[i] + hold[i]);
		}
	}

	else {
		for (int i{ 0 }; i < coefCount; i++)
			hold.push_back(coefficients[i]);
		for (int i{ 0 }; i < sizeSum; i++) {
			sum.coefficients.push_back(other.coefficients[i] + hold[i]);
		}
	}

	return sum;
}

HunPolynomial HunPolynomial::operator-(const HunPolynomial& other)
{
	HunPolynomial difference;
	int sizeDif = std::max(coefCount, other.coefCount);
	difference.coefCount = sizeDif;
	int sizeDifference = std::abs(coefCount - other.coefCount);
	difference.coefficients.clear();

	//have a vector for the operation
	std::vector<int> hold;
	for (int i{ 0 }; i < sizeDifference; i++) {
		hold.push_back(0);
	}

	if (coefCount > other.coefCount) {
		for (int i{ 0 }; i < other.coefCount; i++)
			hold.push_back(other.coefficients[i]);
		for (int i{ 0 }; i < sizeDif; i++) {
			difference.coefficients.push_back(coefficients[i] - hold[i]);
		}
	}

	else {
		for (int i{ 0 }; i < coefCount; i++)
			hold.push_back(coefficients[i]);
		for (int i{ 0 }; i < sizeDif; i++) {
			difference.coefficients.push_back(hold[i] - other.coefficients[i]);
		}
	}

	return difference;
}

HunPolynomial HunPolynomial::operator*(const HunPolynomial& other)
{
	HunPolynomial product;

	int sizeProduct = coefCount + other.coefCount - 1;
	product.coefCount = sizeProduct;

	for (int i{ 1 }; i < sizeProduct; i++) {
		product.coefficients.push_back(0);
	}

	for (int i{ 0 }; i < coefCount; i++) {
		for (int j{ 0 }; j < other.coefCount; j++) {
			product.coefficients[i + j] += coefficients[i] * other.coefficients[j];
		}
	}

	return product;
}

float HunPolynomial::operator()(const float& point) const
{
	float answer = 0;
	int degree = 1;
	if (coefCount == 0)
		return answer;
	else {
		answer = coefficients[coefCount - 1];
		for (int i = coefCount - 2; i >= 0; i--) {
			answer = answer + pow(point, degree) * coefficients[i];
			degree++;
		}
	}
	return answer;
}

std::ostream& operator<<(std::ostream& os, const HunPolynomial& output)
{
	int size = output.coefCount;
	int degree = size - 1;

	std::vector<int> coef = output.coefficients;
	if (degree != 0) {
		while (coef[0] == 0 && coef.size() != 0) {
			coef.erase(coef.begin());
			degree--;
		}
	}

	//first term
	if (degree == 0) {
		if (coef[0] < -1)
			os << "- " << -coef[0];
		else if (coef[0] > 0)
			os << coef[0];
		return os;
	}
	else if (degree == 1) {
		if (coef[0] > 1)
			os << coef[0] << "*x";
		else if (coef[0] < -1)
			os << "- " << -coef[0] << "*x";
		else if (coef[0] == 1)
			os << "x";
		else if (coef[0] == -1)
			os << "- x";
	}
	else {
		if (coef[0] == 1)
			os << "x^" << degree;
		else if (coef[0] == -1)
			os << "- x^" << degree;
		else if (coef[0] > 1)
			os << coef[0] << "*x^" << degree;
		else if (coef[0] < -1)
			os << "- " << -coef[0] << "*x^" << degree;
	}
	degree--;

	//rest of the terms
	for (int i{ 1 }; i < size; i++) {
		if (degree != 1 && degree != 0) {
			if (coef[i] > 1)
				os << " + " << coef[i] << "*x^" << degree;
			else if (coef[i] < -1)
				os << " - " << -coef[i] << "*x^" << degree;
			else if (coef[i] == 1)
				os << " + x^" << degree;
			else if (coef[i] == -1)
				os << " - x^" << degree;
		}

		else if (degree == 1) {
			if (coef[i] > 1)
				os << " + " << coef[i] << "*x";
			else if (coef[i] < -1)
				os << " - " << -coef[i] << "*x";
			else if (coef[i] == 1)
				os << " + x";
			else if (coef[i] == -1)
				os << " - x";
		}

		else if (degree == 0) {
			if (coef[i] > 1)
				os << " + " << coef[i];
			else if (coef[i] < -1)
				os << " - " << -coef[i];
			else if (coef[i] == 1)
				os << " + " << 1;
			else if (coef[i] == -1)
				os << " - " << 1;
		}
		degree--;
	}

	return os;
}