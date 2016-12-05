#include "UEDigitTrakPrivatePCH.h"


UUEDigitTrakInst::UUEDigitTrakInst(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{


}
void UUEDigitTrakInst::FinishDestroy()
{
	Super::FinishDestroy();

}

void UUEDigitTrakInst::Init(UObject* WorldContextObject,const FString& url, int port)
{

	websocket = Cast<UWebSocketWrap>(StaticConstructObject_Internal(UWebSocketWrap::StaticClass()));
	websocket->URL = url;
	websocket->Port = port;
	websocket->ConnectedCallBack.AddDynamic(this, &UUEDigitTrakInst::OnWebsocketConnectedCallBack);
	websocket->ErrorCallBack.AddDynamic(this, &UUEDigitTrakInst::OnWebsocketErrorCallBack);

	websocket->PacketRecievedCallBackCPP.BindUObject(this, &UUEDigitTrakInst::OnPacketRecievedCallBack);

	websocket->Init();
	
	device_status = -1;
}

void UUEDigitTrakInst::OnPacketRecievedCallBack(const FString& data)
{

}

void UUEDigitTrakInst::OnWebsocketConnectedCallBack()
{

}
void UUEDigitTrakInst::OnWebsocketErrorCallBack()
{
	device_status = 2;
}

void UUEDigitTrakInst::Standby()
{

}


void UUEDigitTrakInst::Shutdown()
{

}


void UUEDigitTrakInst::SetPuttMode()
{

}


void UUEDigitTrakInst::SetSwingMode()
{

}


int UUEDigitTrakInst::GetDeviceStatus()
{
	return device_status;
}

