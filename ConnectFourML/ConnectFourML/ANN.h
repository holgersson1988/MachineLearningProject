#pragma once
#include "floatfann.h"
#include "fann_cpp.h"

#include <iostream>


class ANN
{
private:
	FANN::neural_net* net = new FANN::neural_net();
public:
	ANN();
	ANN(unsigned int layers, unsigned int inputs, 
		unsigned int hidden, unsigned int outputs, 
									float learning);
	~ANN();

	FANN::neural_net* getANN();
};

