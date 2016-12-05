#pragma once

#include "WebSocketWrap.h"

#include "UEDigitTrakInst.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDigitTrakInfoCallBack);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FDigitTrakBallCallBack, float, backspin, float, sidespin, float, pitch, float, yaw, float, velocity, float, confidence);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FDigitTrakClubCallBack, float, club_velocity, float, club_horiz, float, club_vert, float, ball_offset);

UCLASS(ClassGroup = UEDigitTrak, Blueprintable)
class UUEDigitTrakInst : public UObject
{
	GENERATED_BODY()

		UUEDigitTrakInst(const class FObjectInitializer& PCIP);

public:


	// Initialize function, should be called after properties are set 
	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak", meta = (WorldContext = "WorldContextObject"))
		void Init(UObject* WorldContextObject,const FString& url,int port);

	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak")
		void Standby();

	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak")
		void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak")
		void SetPuttMode();

	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak")
		void SetSwingMode();

	/**
	0 : the initialization of 'DigitTrak' is ok and the connection is successful.
	1 : the initialization of 'DigitTrak' is underway.
	2 : inner exception
	*/
	UFUNCTION(BlueprintCallable, Category = "UEDigitTrak")
		int GetDeviceStatus();

	UPROPERTY(BlueprintAssignable)
		FDigitTrakInfoCallBack WaitCallBack;

	UPROPERTY(BlueprintAssignable)
		FDigitTrakInfoCallBack ReadyCallBack;

	UPROPERTY(BlueprintAssignable)
		FDigitTrakInfoCallBack HitCallBack;

	UPROPERTY(BlueprintAssignable)
		FDigitTrakInfoCallBack AccomplishCallBack;

	UPROPERTY(BlueprintAssignable)
		FDigitTrakBallCallBack kBallCallBack;

	UPROPERTY(BlueprintAssignable)
		FDigitTrakClubCallBack ClubCallBack;
	


private:

	//if I don't use TWeakObjectPtr .to see the ue4 gc whether freed this object *
	UPROPERTY(Transient)
	UWebSocketWrap* websocket;
	
	void OnPacketRecievedCallBack(const FString& data);

	void OnWebsocketConnectedCallBack();

	void OnWebsocketErrorCallBack();

	void FinishDestroy() override;

	int device_status;

};
