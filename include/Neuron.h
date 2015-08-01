#pragma once

#include "Synapse.h"
#include "RandomNumber.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <ostream>

class Neuron
{
public:
    Neuron()
    {
        m_outputBuffer = 0.0f;
        m_uid = Neuron::count++;
    }
    unsigned long UID(){ return m_uid; }

    void AddInput(Neuron& server, float connectionWeight = 0.0f, bool setWeight = false)
    {
        Synapse* opSynapse = server.RequestOutput();
        if (setWeight) opSynapse->SetWeight(connectionWeight);
        m_inputConnections.push_back(opSynapse);
        m_inputNeurons.push_back(&server);
    }

    void Operate()
    {
        float weighedSum = 0.0f;
        for (auto input : m_inputConnections)
        {
            weighedSum += input->Weight()*input->Value();
        }
        m_outputBuffer = Activate(weighedSum);
    }

    void Update()
    {
        m_output = m_outputBuffer;
    }
    void ShowStatus()
    {
        for (auto input : m_inputConnections)
        {
            std::cout << "["<< input->Weight() << ", " << input->Value() <<"] ";
        }
        std::cout << " : ";

        std::cout << m_output;
        std::cout << std::endl;
    }
    void WriteState(std::ostream& opStream)
    {
        unsigned long i = 0;
        for (auto neuron : m_inputNeurons)
        {
            opStream << m_uid << " " << neuron->UID() << " " << m_inputConnections[i++]->Weight() << std::endl;
        }
    }
protected:
    // Activation function (continious log sigmoid)
    float Activate(float x)
    {
        return 1.0f / (1.0f + exp(-x));
    }

    // Output of the neuron is provided through the returned synapse.
    // Returns a new synapse for each request.
    Synapse* RequestOutput()
    {
        Synapse* newOutput = new Synapse(&m_output);
        m_outputConnections.push_back(newOutput);
        return newOutput;
    }
    std::vector<Synapse*> m_inputConnections;
    std::vector<Synapse*> m_outputConnections;

    // just for tracking the connected neurons
    std::vector<Neuron*> m_inputNeurons;

    
    float m_output;         // holds output for current state (i.e. for time t)
    float m_outputBuffer;   // holds output for next state (i.e. for time t+1)
    unsigned long m_uid;    // unique identifier
    static unsigned long count; // total neuron count (used for uid)
};

unsigned long Neuron::count = 0;

class InputNeuron:public Neuron
{
public:
    InputNeuron()
    {
        m_inputConnections.push_back(new Synapse(&m_output));
        m_output = 0;
    }
    void Set(float value)
    {
        m_output = value;
    }
private:
};

class InternalNeuron : public Neuron
{

};

class OutputNeuron :public Neuron
{
    float Get()
    {
        return m_output;
    }
};