
#include <iostream>

#include "gnuplot.hpp"

#define _USE_MATH_DEFINES // for sin/log
#include <cmath>
#include <math.h>
#include <iostream>
#include <fstream>

#include "MetropolisEvolver.hpp"

template <class T>
std::ostream& operator<<(std::ostream& ostream, const std::vector<T>& v)
{
	ostream << "(";
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		ostream << *it;
		if (it != v.end())
			ostream << ", ";
	}
	ostream << ")";
	return ostream;
}


int main(int argc, char** argv)
{
	std::cout << "Hello There!" << std::endl;

	GnuplotPipe gp;
	//gp.sendLine("plot [-pi/2:pi] cos(x),-(sin(x) > sin(x+1) ? sin(x) : sin(x+1))");

	MetropolisEvolver evolver;

	std::ofstream file("tmp.txt");
	file << "# iterazione    valore" << std::endl;

	for (int i = 0; i < 15000; i++)
		file << i << "\t" << evolver.step() << std::endl;

	file.close();
	gp.sendLine("plot \"tmp.txt\" using 1:2 title 'step'");
	//gp.sendLine("set grid");

	auto sequence = evolver.multiStep(100000);
	sequence.computeParams();
	//std::cout << sequence << std::endl;

	file.open("tmp2.txt");
	for (size_t i = 0; i < sequence.N(); i++)
		file << i << "\t" << sequence.Ck(i) << std::endl;
	file.close();
	gp.sendLine("replot \"tmp2.txt\" using 1:2 title 'Ck'");

	return 0;
}