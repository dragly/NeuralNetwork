#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <QList>

class BinaryNode
{
public:
    BinaryNode(); 
    virtual void set();

    virtual void reset(); //Reset the state of all nodes..

    bool removeConnection(int index);
    bool addConnection(BinaryNode* node);

    bool state();
    int getNumChildren();
    void Copy(BinaryNode* node);

    QList<BinaryNode *> children();
private:
    bool _state; //Needed to avoid recursive loops
    QList<BinaryNode*> _children;
    int numChildren;
};

#endif // BINARYNODE_H
