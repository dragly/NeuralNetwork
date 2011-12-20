#ifndef BINARYNODE_H
#define BINARYNODE_H

class BinaryNode
{
public:
    BinaryNode(); 
    virtual void set();

    virtual void reset(); //Reset the state of all nodes..

    bool removeConnection(int index);
    void addConnection(BinaryNode* node);

    bool state();

private:
    bool _state; //Needed to avoid recursive loops
    BinaryNode** children;
    int numChildren;
};

#endif // BINARYNODE_H
