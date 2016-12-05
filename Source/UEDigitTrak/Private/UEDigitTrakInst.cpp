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
	JsonReader = TJsonReaderFactory<TCHAR>::Create(data);

	if (!FJsonSerializer::Deserialize(JsonReader.ToSharedRef(), JsonParsed))
	{
		UE_LOG(LogUEDigitTrak, Warning, TEXT("JSON STRING FAILED TO PARSE!"));
		return;
	}

	if (JsonParsed->HasField("data"))
	{
		int type = JsonParsed->GetNumberField("type");
		if (type == 0)//ball data
		{
			TSharedPtr<FJsonObject> jdata = JsonParsed->GetObjectField("data");
			float backspin = jdata->GetNumberField("backspin");
			float sidespin = jdata->GetNumberField("sidespin");
			float pitch = jdata->GetNumberField("pitch");
			float yaw = jdata->GetNumberField("yaw");
			float velocity = jdata->GetNumberField("velocity");
			float confidence = jdata->GetNumberField("confidence");
			BallCallBack.Broadcast(backspin, sidespin, pitch, yaw, velocity, confidence);
		}
		else if (type == 1)//club data
		{
			TSharedPtr<FJsonObject> jdata = JsonParsed->GetObjectField("data");
			float club_velocity = jdata->GetNumberField("club_velocity");
			float club_horiz = jdata->GetNumberField("club_horiz");
			float club_vert = jdata->GetNumberField("club_vert");
			float ball_offset = jdata->GetNumberField("ball_offset");
			ClubCallBack.Broadcast(club_velocity, club_horiz, club_vert, ball_offset);

		}

	}
	else if (JsonParsed->HasField("state"))
	{
		int state = JsonParsed->GetNumberField("state");
		if (state == 0)
		{
			WaitCallBack.Broadcast();
		}
		else if (state == 1)
		{
			ReadyCallBack.Broadcast();
		}
		else if (state == 2)
		{
			HitCallBack.Broadcast();
		}
		else if (state == 3)
		{
			AccomplishCallBack.Broadcast();
		}
	}
	else if (JsonParsed->HasField("device_status"))
	{
		int state = JsonParsed->GetNumberField("device_status");
		if (state == 0)
		{
			device_status = 0;
		}
		else if (state == 1)
		{
			device_status = 1;
		}
		else if (state == 2)
		{
			device_status = 2;
		}
	}
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
	websocket->Send("{cmd:0}");
}

void UUEDigitTrakInst::Suspend()
{
	websocket->Send("{cmd:1}");
}

void UUEDigitTrakInst::Shutdown()
{
	websocket->Send("{cmd:2}");
}


void UUEDigitTrakInst::SetPuttMode()
{
	websocket->Send("{cmd:3}");
}


void UUEDigitTrakInst::SetSwingMode()
{
	websocket->Send("{cmd:4}");
}


int UUEDigitTrakInst::GetDeviceStatus()
{
	return device_status;
}

