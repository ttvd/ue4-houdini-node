#include "HoudiniNodePropertyCommon.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodeClass.h"
#include "HoudiniNodePrivatePCH.h"


FHoudiniNodePropertyCommon::FHoudiniNodePropertyCommon() :
    Property(nullptr),
    Component(nullptr),
    Template(nullptr)
{

}


FHoudiniNodePropertyCommon::~FHoudiniNodePropertyCommon()
{

}


void
FHoudiniNodePropertyCommon::InitializeProperty(UProperty* InProperty, UHoudiniNodeComponent* InComponent,
    const PRM_Template* InTemplate, EHoudiniNodePropertyType::Enum InPropertyType)
{
    Property = InProperty;
    Component = InComponent;
    Template = const_cast<PRM_Template*>(InTemplate);

    PropertyType = InPropertyType;

    if(Property)
    {
        Property->PropertyFlags = UINT64_C(69793219077);
        Property->PropertyLinkNext = nullptr;
    }

    /*
    UClass* Class = Cast<UClass>(Property->GetOuter());
    Class->AddCppProperty(Property);
    */
}


void
FHoudiniNodePropertyCommon::AssignClass()
{
    if(!Property)
    {
        return;
    }

    UClass* Class = Cast<UClass>(Property->GetOuter());
    if(!Class)
    {
        return;
    }

    Property->Next = nullptr;
    Class->AddCppProperty(Property);
}


void
FHoudiniNodePropertyCommon::AssignPropertyOffset(uint32 Offset) const
{
    if(!Property)
    {
        return;
    }

    *(int32*)((char*) &Property->RepNotifyFunc - sizeof(int32)) = (int32) Offset;
}


uint32
FHoudiniNodePropertyCommon::GetPropertyOffset() const
{
    return *(int32*)((char*) &Property->RepNotifyFunc - sizeof(int32));
}


uint32
FHoudiniNodePropertyCommon::GetPropertyDim() const
{
    check(Property);
    return Property->ArrayDim;
}


EHoudiniNodePropertyType::Enum
FHoudiniNodePropertyCommon::GetPropertyType() const
{
    return PropertyType;
}


void
FHoudiniNodePropertyCommon::AssignPropertyMeta() const
{
    if(!Property || !Template)
    {
        return;
    }

    const PRM_Name* TemplateName = Template->getNamePtr();
    if(!TemplateName)
    {
        return;
    }

    const UT_String& Name = TemplateName->getToken();
    FString PropertyName = UTF8_TO_TCHAR(Name.c_str());

    const UT_String& Label = TemplateName->getLabel();
    FString PropertyLabel = UTF8_TO_TCHAR(Label.c_str());

    Property->SetMetaData(TEXT("DisplayName"), *PropertyLabel);
    Property->SetMetaData(TEXT("HoudiniName"), *PropertyName);
    Property->SetMetaData(TEXT("EditAnywhere"), TEXT("1"));
    Property->SetMetaData(TEXT("BlueprintReadOnly"), TEXT("1"));
    Property->SetMetaData(TEXT("Category"), TEXT("HoudiniProperties"));
}


void
FHoudiniNodePropertyCommon::AssignPropertyRanges() const
{
    if(!Property || !Template)
    {
        return;
    }

    const PRM_Range* Range = Template->getRangePtr();
    if(Range)
    {
        if(Range->hasParmMin())
        {
            const float ParmMin = (float) Range->getParmMin();
            Property->SetMetaData(TEXT("ClampMin"), *FString::SanitizeFloat(ParmMin));
        }

        if(Range->hasParmMax())
        {
            const float ParmMax = (float) Range->getParmMax();
            Property->SetMetaData(TEXT("ClampMax"), *FString::SanitizeFloat(ParmMax));
        }

        if(Range->hasUIMin())
        {
            const float UIMin = (float) Range->getUIMin();
            Property->SetMetaData(TEXT("UIMin"), *FString::SanitizeFloat(UIMin));
        }

        if(Range->hasUIMax())
        {
            const float UIMax = (float)Range->getUIMax();
            Property->SetMetaData(TEXT("UIMax"), *FString::SanitizeFloat(UIMax));
        }
    }
}


bool
FHoudiniNodePropertyCommon::GetValues(OP_Node* Node, UHoudiniNodeComponent* Component, float Time, bool bAssign,
    bool bComputeOffset, TArray<float>& Values) const
{
    Values.Empty();

    if(!Node || !Template || !Property || !Component)
    {
        return false;
    }

    const PRM_Name* TemplateName = Template->getNamePtr();
    if(!TemplateName)
    {
        return false;
    }

    const UT_String& Name = TemplateName->getToken();

    const int32 VectorSize = Template->getVectorSize();
    if(!VectorSize)
    {
        return false;
    }

    Values.SetNumZeroed(VectorSize);
    for(int32 Idx = 0; Idx < VectorSize; ++Idx)
    {
        const float Value = Node->evalFloat(Name.c_str(), Idx, Time);
        Values[Idx] = Value;
    }

    if(bAssign)
    {
        Property->ArrayDim = Values.Num();

        if(bComputeOffset)
        {
            const uint32 PropertyValueOffset = Component->SetScratchSpaceValues(Values);
            AssignPropertyOffset(PropertyValueOffset);
        }
        else
        {
            const uint32 PropertyValueOffset = GetPropertyOffset();
            Component->SetScratchSpaceValuesAtOffset(Values, PropertyValueOffset);
        }
    }

    return true;
}


bool
FHoudiniNodePropertyCommon::GetValues(OP_Node* Node, UHoudiniNodeComponent* Component, float Time, bool bAssign,
    bool bComputeOffset, TArray<int32>& Values) const
{
    Values.Empty();

    if(!Node || !Template || !Property || !Component)
    {
        return false;
    }

    const PRM_Name* TemplateName = Template->getNamePtr();
    if(!TemplateName)
    {
        return false;
    }

    const UT_String& Name = TemplateName->getToken();

    const int32 VectorSize = Template->getVectorSize();
    if(!VectorSize)
    {
        return false;
    }

    Values.SetNumZeroed(VectorSize);
    for(int32 Idx = 0; Idx < VectorSize; ++Idx)
    {
        const int32 Value = Node->evalInt(Name.c_str(), Idx, Time);
        Values[Idx] = Value;
    }

    if(bAssign)
    {
        Property->ArrayDim = Values.Num();

        if(bComputeOffset)
        {
            const uint32 PropertyValueOffset = Component->SetScratchSpaceValues(Values);
            AssignPropertyOffset(PropertyValueOffset);
        }
        else
        {
            const uint32 PropertyValueOffset = GetPropertyOffset();
            Component->SetScratchSpaceValuesAtOffset(Values, PropertyValueOffset);
        }
    }

    return true;
}


bool
FHoudiniNodePropertyCommon::GetValues(OP_Node* Node, UHoudiniNodeComponent* Component, float Time, bool bAssign,
    bool bComputeOffset, TArray<FString>& Values) const
{
    Values.Empty();

    if(!Node || !Template || !Property || !Component)
    {
        return false;
    }

    const PRM_Name* TemplateName = Template->getNamePtr();
    if(!TemplateName)
    {
        return false;
    }

    const UT_String& Name = TemplateName->getToken();

    const int32 VectorSize = Template->getVectorSize();
    if(!VectorSize)
    {
        return false;
    }

    Values.SetNumZeroed(VectorSize);
    for(int32 Idx = 0; Idx < VectorSize; ++Idx)
    {
        UT_String RawValue("");
        Node->evalString(RawValue, Name.c_str(), Idx, Time);

        FString AttributeValue = UTF8_TO_TCHAR(RawValue.c_str());
        Values[Idx] = AttributeValue;
    }

    if(bAssign)
    {
        Property->ArrayDim = Values.Num();

        if(bComputeOffset)
        {
            const uint32 PropertyValueOffset = Component->SetScratchSpaceValues(Values);
            AssignPropertyOffset(PropertyValueOffset);
        }
        else
        {
            const uint32 PropertyValueOffset = GetPropertyOffset();
            Component->SetScratchSpaceValuesAtOffset(Values, PropertyValueOffset);
        }
    }

    return true;
}


bool
FHoudiniNodePropertyCommon::UploadValues(OP_Node* Node, UHoudiniNodeComponent* Component, float Time) const
{
    if(!Node || !Template || !Property || !Component)
    {
        return false;
    }

    const PRM_Name* TemplateName = Template->getNamePtr();
    if(!TemplateName)
    {
        return false;
    }

    const UT_String& Name = TemplateName->getToken();

    const uint32 Offset = GetPropertyOffset();
    const int32 NumEntries = GetPropertyDim();

    switch(PropertyType)
    {
        case EHoudiniNodePropertyType::Integer:
        {
            TArray<int32> Values;
            Component->GetScratchSpaceValuesAtOffset(Offset, NumEntries, Values);

            for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
            {
                const int32 Value = Values[Idx];
                Node->setInt(Name.c_str(), Idx, Time, Value);
            }

            break;
        }

        case EHoudiniNodePropertyType::Float:
        {
            TArray<float> Values;
            Component->GetScratchSpaceValuesAtOffset(Offset, NumEntries, Values);

            for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
            {
                const float Value = Values[Idx];
                Node->setFloat(Name.c_str(), Idx, Time, Value);
            }

            break;
        }

        case EHoudiniNodePropertyType::String:
        {
            TArray<FString> Values;
            Component->GetScratchSpaceValuesAtOffset(Offset, NumEntries, Values);

            for(int32 Idx = 0; Idx < Values.Num(); ++Idx)
            {
                const FString& Value = Values[Idx];
                UT_String RawValue = TCHAR_TO_UTF8(*Value);

                Node->setString(RawValue.c_str(), CH_STRING_LITERAL, Name.c_str(), Idx, Time);
            }

            break;
        }

        default:
        {
            break;
        }
    }

    return true;
}





