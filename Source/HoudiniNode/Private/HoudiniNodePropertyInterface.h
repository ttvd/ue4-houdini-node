#pragma once


class OP_Node;
class PRM_Template;

class UHoudiniNodeComponent;


class IHoudiniNodePropertyInterface
{
public:

    //! Construct property from a given template.
    virtual bool Construct(OP_Node* Node, const PRM_Template* Template, UHoudiniNodeComponent* Component, float Time) = 0;
};

