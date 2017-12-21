// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyBase.h"

UNotifyBase::UNotifyBase(const FObjectInitializer& ObjectInitializer) : UObject(ObjectInitializer)
{

}

UNotifyBase::~UNotifyBase()
{

}

void UNotifyBase::OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnJoinRoom"));
}

void UNotifyBase::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnStatusUpdate"));
}

void UNotifyBase::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnQuitRoom"));
}

void UNotifyBase::OnMemberVoice(const unsigned int *members, int count)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnMemberVoice"));
}

void UNotifyBase::OnMemberVoice(const char *roomName, unsigned int member, int status)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnMemberVoice"));
}

void UNotifyBase::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnUploadFile"));
}

void UNotifyBase::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnDownloadFile"));
}

void UNotifyBase::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnPlayRecordedFile"));
}

void UNotifyBase::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnApplyMessageKey"));
}

void UNotifyBase::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnSpeechToText"));
}

void UNotifyBase::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnRecording"));
}

void UNotifyBase::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnStreamSpeechToText"));
}

void UNotifyBase::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnRoleChanged"));
}
