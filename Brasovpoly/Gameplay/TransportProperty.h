#ifndef TRANSPORT_PROPERTY_H
#define TRANSPORT_PROPERTY_H

#include "Property.h"

class TransportProperty : public Property
{
public:
    std::string imageFileName;
    TransportProperty(std::string nameParam, int priceParam, std::string imageFileNameParam)
        : Property(nameParam, priceParam), imageFileName(imageFileNameParam)  {}
};

#endif