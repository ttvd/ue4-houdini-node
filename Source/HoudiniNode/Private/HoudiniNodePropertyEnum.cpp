#include "HoudiniNodePropertyEnum.h"
#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"


UHoudiniNodePropertyEnum::UHoudiniNodePropertyEnum(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{

}


UHoudiniNodePropertyEnum::~UHoudiniNodePropertyEnum()
{

}


bool
UHoudiniNodePropertyEnum::Construct(const PRM_Template* Template, UHoudiniNodeComponent* Component)
{
    if(!Template || !Component)
    {
        return false;
    }

    InitializeProperty(this, Component, Template, EHoudiniNodePropertyType::Integer);

    if(!ConstructProperty<int>(true, true))
    {
        return false;
    }

    TArray<TPair<FName, int64> > EnumValues;
    if(!GetEnumValues(EnumValues))
    {
        return false;
    }

    UClass* ComponentClass = Component->GetClass();
    const FString& ComponentClassName = ComponentClass->GetName();

    const FString& PropertyName = GetName();
    FString EnumName = FString::Printf(TEXT("%s_%s_enum"), *ComponentClassName, *PropertyName);

    static const EObjectFlags ObjectFlags = RF_Public | RF_Transient;
    UEnum* Enum = NewObject<UEnum>(this, *EnumName, ObjectFlags);
    if(!Enum)
    {
        return false;
    }

    Enum->CppType = TEXT("ERegularEnum");
    const UEnum::ECppForm EnumType = Enum->GetCppForm();

    if(!Enum->SetEnums(EnumValues, EnumType, true))
    {
        return false;
    }

    SetEnum(Enum);

    FString UnderlyingName = FString::Printf(TEXT("%s_%s_underlying"), *ComponentClassName, *PropertyName);
    UNumericProperty* UnderlyingProperty = NewObject<UByteProperty>(this, *UnderlyingName, ObjectFlags);
    AddCppProperty(UnderlyingProperty);

    return true;
}


bool
UHoudiniNodePropertyEnum::Update()
{
    if(!Template || !Component)
    {
        return false;
    }

    if(!ConstructProperty<int>(true, false))
    {
        return false;
    }

    TArray<TPair<FName, int64> > EnumValues;
    if(!GetEnumValues(EnumValues))
    {
        return false;
    }

    UEnum* Enum = GetEnum();
    if(!Enum)
    {
        return false;
    }

    const UEnum::ECppForm EnumType = Enum->GetCppForm();
    if(!Enum->SetEnums(EnumValues, EnumType, true))
    {
        return false;
    }

    return true;
}


bool
UHoudiniNodePropertyEnum::GetEnumValues(TArray<TPair<FName, int64> >& EnumValues) const
{
    EnumValues.Empty();

    if(!Template)
    {
        return false;
    }

    TArray<TPair<FString, int64> > ChoiceValues;
    if(!GetChoiceValues(ChoiceValues))
    {
        return false;
    }

    for(int32 Idx = 0; Idx < ChoiceValues.Num(); ++Idx)
    {
        const TPair<FString, int64>& ChoiceValue = ChoiceValues[Idx];

        TPair<FName, int64> EnumEntry(FName(*ChoiceValue.Key), ChoiceValue.Value);
        EnumValues.Add(EnumEntry);
    }

    return EnumValues.Num() > 0;
}


bool
UHoudiniNodePropertyEnum::Upload()
{
    if(!Template || !Component || !Property)
    {
        return false;
    }

    return UploadValues();
}

