#pragma once

#include "UEDigitTrakBlueprintFunctionLibrary.generated.h"

UCLASS(ClassGroup = UEDigitTrak, Blueprintable)
class UUEDigitTrakBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{

    GENERATED_UCLASS_BODY()

    UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create DigitTrak", CompactNodeTitle = "DigitTrak", Keywords = "new create DigitTrak"), Category = UEDigitTrak)
        static UUEDigitTrakInst* NewDigitTrak(UObject* WorldContextObject);



};

