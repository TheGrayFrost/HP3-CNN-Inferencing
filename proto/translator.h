#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <cuda.h>
#include <cudnn.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cublas_v2.h>
#include "../forward/operations.h"
#include "network.pb.h"

using namespace std;

class Translator
{
public:
/*
TODO: Add wrapper class here which calls the private classes.
*/

private:
    Conv2D translateConv2D_layer(DeepNet::Layer &layer, cudnnHandle_t cudnn);
    Pool translatePool_layer(DeepNet::Layer &layer, cudnnHandle_t cudnn);
    Activation translateActivation_layer(DeepNet::Layer& layer, cudnnHandle_t cudnn);
    Linear translateLinear_layer(DeepNet::Layer& layer, cudnnHandle_t cudnn);
}

#endif