#ifndef BINARYINPUTNODE_H
#define BINARYINPUTNODE_H
#include "binarynode.h"

class BinaryInputHandler
{
public:
    BinaryInputHandler(int _paramIndex, double _activeFrom, double _activeTo);

    void setConnectedNode(BinaryNode* node);

    void execute(int index, double value);
    void reset();

private:
   inline bool convertToBinary(double in); //assumes input in range [0-1]

   BinaryNode* connectedNode;
   //range
   double activeLowerLimit;
   double activeUpperLimit;
   int paramIndex;
};

#endif // BINARYINPUTNODE_H
