#include "StringAlgorithms.h"

int Find(const std::string& str, const std::string& in)
{
    int result = -1;
    for (unsigned i = 0; i < in.length(); ++i)
    {
        if (in[i] == str[0])
        {
            result = i++;
            for (unsigned j = 1; j < str.length(); ++j, ++i)
            {
                if (in[i] != str[j])
                {
                    result = -1;
                    --i;
                    break;
                }
            }
            if (result != -1)
            {
                break;
            }
        }
    }
    return result;
}

void Replace(std::string& in, const Formula& F)
{
    unsigned start = Find(F.GetLeft(), in);
    std::string result;
    while (start != -1)
    {
        for (unsigned i = 0; i < start; ++i)
        {
            result += in[i];
        }
        for (unsigned i = 0; i < F.GetRight().length(); ++i)
        {
            result += F.GetRight()[i];
        }
        for (unsigned i = start + F.GetLeft().length(); i < in.length(); ++i)
        {
            result += in[i];
        }
        in = result;
        result = "";
        start = Find(F.GetLeft(), in);
    }
}

void MarkovAlgorithm(std::string& in, const Formula* formulas, unsigned n)
{
    for (unsigned i = 0; i < n; ++i)
    {
        std::string before = in;
        Replace(in, formulas[i]);
        std::cout << in << std::endl;
        if (before != in)
        {
            i = -1;
            continue;
        }
    }
}