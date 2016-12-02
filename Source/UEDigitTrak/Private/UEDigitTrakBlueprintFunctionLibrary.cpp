#include "UEDigitTrakPrivatePCH.h"


UUEDigitTrakBlueprintFunctionLibrary::UUEDigitTrakBlueprintFunctionLibrary(const class FObjectInitializer& PCIP)
: Super(PCIP)
{

}

UUEDigitTrakInst* UUEDigitTrakBlueprintFunctionLibrary::NewDigitTrak(UObject* WorldContextObject)
{

    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	UUEDigitTrakInst* tempObject = Cast<UUEDigitTrakInst>(StaticConstructObject_Internal(UUEDigitTrakInst::StaticClass()));


    return tempObject;

}
