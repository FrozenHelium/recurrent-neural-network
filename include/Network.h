#pragma once

#include "Neuron.h"
#include <string>
#include <iostream>


class Network
{
public:
    void Test()
    {
        InputNeuron* x = new InputNeuron[2];
        InternalNeuron* u = new InternalNeuron[3];
        OutputNeuron* y = new OutputNeuron[1];
        m_neurons.push_back(&x[0]);
        m_neurons.push_back(&x[1]);
        m_neurons.push_back(&u[0]);
        m_neurons.push_back(&u[1]);
        m_neurons.push_back(&u[2]);
        m_neurons.push_back(&y[0]);
        u[0].AddInput(x[0]);
        u[2].AddInput(x[1]);
        u[0].AddInput(y[0]);
        u[2].AddInput(y[0]);
        u[0].AddInput(u[1]);
        u[2].AddInput(u[1]);
        u[1].AddInput(u[0]);
        u[1].AddInput(u[2]);
        y[0].AddInput(u[1]);
        m_nipNeurons = 2;
        m_ninNeurons = 3;
        m_nopNeurons = 1;
    }

    // Writes the current state data to the given stream
    // (connections & weights)
    void WriteState(std::ostream& opStream)
    {
        opStream << m_nipNeurons << std::endl;
        opStream << m_ninNeurons << std::endl;
        opStream << m_nopNeurons << std::endl;
        for (auto neuron : m_neurons)
        {
            neuron->WriteState(opStream);
        }
    }

    // Reads and loads the state data from the given stream
    // (connections & weights)
    void ReadState(std::istream& ipStream)
    {
        ipStream >> m_nipNeurons;
        ipStream >> m_ninNeurons;
        ipStream >> m_nopNeurons;

        for (unsigned long i = 0; i < m_nipNeurons; i++)
        {
            m_neurons.push_back(new InputNeuron());
        }
        for (unsigned long i = 0; i < m_ninNeurons; i++)
        {
            m_neurons.push_back(new InternalNeuron());
        }
        for (unsigned long i = 0; i < m_nopNeurons; i++)
        {
            m_neurons.push_back(new OutputNeuron());
        }
        unsigned long dest = 0, src = 0;
        float weight = 0.0f;
        while (ipStream >> dest >> src >> weight)
        {
            m_neurons[dest]->AddInput(*m_neurons[src], weight, true);
        }
    }
protected:
    std::vector<Neuron*> m_neurons;
    unsigned long m_nipNeurons; // number of input neurons
    unsigned long m_ninNeurons; // number of internal neurons
    unsigned long m_nopNeurons; // number of output neurons
};