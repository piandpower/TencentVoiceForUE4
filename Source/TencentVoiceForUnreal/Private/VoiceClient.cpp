// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceClient.h"

UVoiceClient* UVoiceClient::VoiceClient = nullptr;

UVoiceClient::UVoiceClient()
{
	m_voiceengine = gcloud_voice::GetVoiceEngine();
}

UVoiceClient::~UVoiceClient()
{

}

void UVoiceClient::Tick(float DeltaTime)
{
	m_voiceengine->Poll();
}

FORCEINLINE bool UVoiceClient::IsTickable() const
{
	return true;
}

FORCEINLINE TStatId UVoiceClient::GetStatId() const
{
	return TStatId();
}

UVoiceClient * UVoiceClient::GetVoiceClient()
{
	if (nullptr == VoiceClient)
	{
		VoiceClient = NewObject<UVoiceClient>();
		VoiceClient->AddToRoot();
	}
	return VoiceClient;
}

bool UVoiceClient::SetAppInfo(const FString& appID, const FString& appKey, int32 RoleID)
{
	//UE_LOG(LogTemp, Error, TEXT("SetAppInfo return code %d!"), static_cast<int32>(m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*FString::FromInt(RoleID)))));

	if ((nullptr != m_voiceengine)
		&& (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*FString::FromInt(RoleID)))))
	{
		return true;
	}
	return false;
}

void UVoiceClient::InitEngine()
{
	m_voiceengine->Init();
	//UE_LOG(LogTemp, Error, TEXT("Init return code %d"), static_cast<int32>(m_voiceengine->Init()));
	m_voiceengine->SetMode(gcloud_voice::IGCloudVoiceEngine::RealTime);
	m_voiceengine->SetServerInfo("udp://cn.voice.gcloudcs.com:10001");
}

bool UVoiceClient::SetNotify(UObject * NotifyToUse)
{
	class UTeamRoomNotify* TempNotify = NewObject<UTeamRoomNotify>();
	//UE_LOG(LogTemp, Error, TEXT("SetNotify return code %d"), static_cast<int32>(m_voiceengine->SetNotify(TempNotify)));
	//class MessageNotify* TempNotify = new class MessageNotify();
	
	if ((nullptr != TempNotify)
		&& (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->SetNotify(TempNotify)))
	{
		CurrentNotify = TempNotify;
		return true;
	}
	return false;
}

UObject * UVoiceClient::GetNotify()
{
	return CurrentNotify;
}

bool UVoiceClient::JoinTeamRoom(const FString & RoomName, int32 msTimeout)
{
	//UE_LOG(LogTemp, Error, TEXT("JoinTeamRoom return code %d"), static_cast<int32>(m_voiceengine->JoinTeamRoom(TCHAR_TO_ANSI(*RoomName), msTimeout)));

	if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->JoinTeamRoom(TCHAR_TO_ANSI(*RoomName), msTimeout))
	{
		return true;
	}
	return false;
}

bool UVoiceClient::OpenMic()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenMic return code %d"), static_cast<int32>(m_voiceengine->OpenMic()));

	/*if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->OpenMic())
	{
		return true;
	}*/
	return false;
}

bool UVoiceClient::CloseMic()
{
	UE_LOG(LogTemp, Warning, TEXT("CloseMic return code %d"), static_cast<int32>(m_voiceengine->CloseMic()));

	/*if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->CloseMic())
	{
		return true;
	}*/
	return false;
}

bool UVoiceClient::OpenSpeaker()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenSpeaker return code %d"), static_cast<int32>(m_voiceengine->OpenSpeaker()));

	/*if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->OpenSpeaker())
	{
		return true;
	}*/
	return false;
}

bool UVoiceClient::CloseSpeaker()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenSpeaker return code %d"), static_cast<int32>(m_voiceengine->CloseSpeaker()));

	/*if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->CloseSpeaker())
	{
		return true;
	}*/
	return false;
}

bool UVoiceClient::QuitRoom(const FString & RoomName, int32 msTimeout)
{
	/*UE_LOG(LogTemp, Error, TEXT("QuitRoom return code %d"), static_cast<int32>(m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*RoomName), msTimeout)));*/

	if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*RoomName), msTimeout))
	{
		return true;
	}
	return false;
}
