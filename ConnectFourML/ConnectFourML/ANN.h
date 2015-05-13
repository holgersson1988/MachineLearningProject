#pragma once
#include "floatfann.h"
#include "fann_cpp.h"

#include <iostream>


class ANN
{
private:
	FANN::neural_net net;
	//FANN_EXTERNAL struct fann *FANN_API fann_create_standard();
public:
	ANN();
	//ANN(unsigned int inputs, unsigned int layers, unsigned int hidden, unsigned int outputs, float learning);
	~ANN();
};

