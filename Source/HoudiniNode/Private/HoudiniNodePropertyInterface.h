#pragma once


class PRM_Template;

class UHoudiniNodeClass;
class UHoudiniNodeComponent;


class IHoudiniNodePropertyInterface
{
public:

    //! Construct property from a given template.
    virtual bool Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component) = 0;

    //! Update property.
    virtual bool Update() = 0;

    //! Upload property value.
    virtual bool Upload() = 0;
};

