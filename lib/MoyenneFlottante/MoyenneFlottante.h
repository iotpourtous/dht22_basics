#ifndef MoyenneFlottante_h
#define MoyenneFlottante_h

class MoyenneFlottante
{
private:
    int _elements;
    float *_readings;
    int _readIndex = 0;
    float _total = 0;
    bool _ready = false;

public:
    MoyenneFlottante(int elements = 10) : _elements(elements)
    {
        _readings = new float[_elements];
        for (int i = 0; i < _elements; i++)
        {
            _readings[i] = 0.0;
        }
    }
    void populate(float value)
    {
        _total = _total - _readings[_readIndex] + value;
        _readings[_readIndex] = value;
        _readIndex++;
        if (_readIndex >= _elements)
        {
            _ready = true;
            _readIndex = 0;
        }
    }

    float moyenne()
    {
        if(!_ready) {
            return std::numeric_limits<float>::quiet_NaN();;
        }
        return _total / _elements;
    }
};

#endif