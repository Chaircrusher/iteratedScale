// iteratedScale
// Copyright 2022 Kent Williams chaircrusher@gmail.com
//
// This code is public domain.
//
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
// type for storing values
typedef std::vector<double> VecType;

// simple polynomial calculation based on history
double polynomialFunc(const VecType &coefficients,
						const VecType &history) {
   double result(0);
   for(unsigned i = 0; i < coefficients.size(); ++i)
      result += coefficients[i] * history[i];
   return result;
}

// simple polynomial calculation based on history
double polynomialFunc2(const VecType &coefficients,
						const VecType &history) {
   double result(0);
   for(unsigned i = 0; i < coefficients.size(); ++i)
      result += coefficients[i] * std::pow(history[i],
														 static_cast<double>(i));
   return result;
}

// shift in history. 
void shift(VecType &vec, double current) {
	// go through history backwards to move every value
   for(unsigned int i = vec.size() - 1; i > 0; --i)
      vec[i] = vec[i-1];
	// add history value
   vec[0] = current;
}
// the program
int main(int argc, char **argv) {
	if(argc < 3) {
		std::cerr << "iteratedScale: Usage: " << std::endl
					 << "iteratedScale scaleName coeff1 coeff2 ... "
					 << std::endl;
		return 1;
	}
	// save scale name
	std::string scaleName(argv[1]);
   VecType coefficients;
	//
	// get coefficients from command line
   for(int i = 2; i < argc; ++i) {
      double cur(std::strtod(argv[i],nullptr));
      coefficients.push_back(cur);
   }

	//
	// history matches coefficients
   VecType history = VecType(coefficients.size(),0.0);

	// start with 1.0 -- unison
   double current = 1.0;
   VecType outVec;
	// compute the scale values
	// compute f(x) = coeff1*current + coeff2*history[t-1] +
	//                coeff3 * history[t-2] etc
   for(unsigned i = 0; current <= 2.0; i++) {
		// don't include unison note
      if(current > 1.0)
         outVec.push_back(current);
		// shift history
      shift(history,current);
      current = polynomialFunc2(coefficients, history);
   }
	// sort the results. You hope for a monotonically increasing
	// scale but it's easy make one that wanders.
	std::sort(outVec.begin(),outVec.end());
	// minimal scala file has one line of description
	std::cout << "! Coefficients:";
	for(const auto &coeff : coefficients) {
		std::cout << " " << coeff;
	}
	std::cout << std::endl;
   std::cout << scaleName << std::endl;
	// and one line that gives the size of the scale
   std::cout << outVec.size()+1 << std::endl;
   for(const auto &curval : outVec) {
		// compute the frequency value in cents
		double scaledVal = ((curval - 1.0) * 1200.00); // + 100.0;
		// output the raw value
		std::cout << "! " << curval << std::endl;
		// output the scaled value
		// if it is very close to an integral value
		// output the floor of the value, and tack on ".00"
		// so it doesn't look like an implicit ratio
		if(std::fabs(scaledVal - std::floor(scaledVal)) < 0.00001)
			std::cout << std::floor(scaledVal) << ".00";
		else
			std::cout << scaledVal;
		std::cout << std::endl;
   }
	// put in the octave value
	std::cout << "! octave"
				 << std::endl
				 << "1200.00" << std::endl;
}
