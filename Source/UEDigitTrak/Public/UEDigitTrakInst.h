#pragma once
#include "UEDigitTrakInst.generated.h"



UCLASS(ClassGroup = UEDigitTrak, Blueprintable)
class UUEDigitTrakInst : public UObject
{
	GENERATED_BODY()

		UUEDigitTrakInst(const class FObjectInitializer& PCIP);

public:


	// Initialize function, should be called after properties are set 
	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak", meta = (WorldContext = "WorldContextObject"))
		void Init(UObject* WorldContextObject);




};
