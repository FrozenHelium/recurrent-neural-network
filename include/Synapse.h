#pragma once

#include "RandomNumber.h"

class Synapse
{
public:
    Synapse() :m_weight(RANDOM_VALUE), m_value(0){}
    Synapse(float* source) : m_weight(RANDOM_VALUE), m_value(source){}
    float Weight(){ return m_weight; }
    float Value()
    {
        if (!m_value) throw std::exception("no source has been set up for the value");
        return *m_value; 
    }
    void SetValueSource(float* source)
    {
        m_value = source;
    }
    void SetWeight(float weight){ m_weight = weight; }
private:
    float m_weight;
    float* m_value;
};