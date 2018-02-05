#include "HoudiniNodeComponent.h"
#include "HoudiniNodePrivatePCH.h"
#include "HoudiniNodeActor.h"


UHoudiniNodeComponent::UHoudiniNodeComponent(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    ScratchSpaceBufferOffset(0u)
{

}


UHoudiniNodeComponent::~UHoudiniNodeComponent()
{

}


void
UHoudiniNodeComponent::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);

    uint32 ScratchSpaceSize = HOUDINI_NODE_SCRATCH_SPACE_BUFFER_SIZE;
    Ar << ScratchSpaceSize;

    Ar << ScratchSpaceBufferOffset;

    Ar.Serialize(&ScratchSpaceBuffer[0], ScratchSpaceSize);
}


#if WITH_EDITOR

void
UHoudiniNodeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    UProperty* Property = PropertyChangedEvent.MemberProperty;
    if(Property)
    {
        const FString& Category = Property->GetMetaData(TEXT("Category"));
        if(Category.Equals(TEXT("HoudiniProperties"), ESearchCase::IgnoreCase))
        {
            if(EPropertyChangeType::ValueSet == PropertyChangedEvent.ChangeType)
            {
                UHoudiniNodeClass* HoudiniNodeClass = Cast<UHoudiniNodeClass>(GetClass());
                if(HoudiniNodeClass)
                {
                    HoudiniNodeClass->OnParameterChanged(Property);
                }
            }
        }
    }
}

#endif


