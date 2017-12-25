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
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnJoinRoom return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_JOINROOM_SUCC == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnJoinRoom);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

void UNotifyBase::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnStatusUpdate return code %d!"), *(this->GetName()), static_cast<int32>(status));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnStatusUpdate);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnQuitRoom return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_QUITROOM_SUCC == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnQuitRoom);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

// This function deprecate from GVoice 1.1.14
//void UNotifyBase::OnMemberVoice(const unsigned int *members, int count)
//{
//	UE_LOG(TencentVoicePlugin, Display, TEXT("UNotifyBase::OnMemberVoice"));
//}

void UNotifyBase::OnMemberVoice(const char *roomName, unsigned int member, int status)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnMemberVoice report member:%d with status:%d in room:%s"), *(this->GetName()), static_cast<int32>(member), static_cast<int32>(status), *roomName);

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnMemberVoice);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnUploadFile return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_UPLOAD_RECORD_DONE == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnUploadFile);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

void UNotifyBase::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnDownloadFile return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_DOWNLOAD_RECORD_DONE == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnDownloadFile);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

void UNotifyBase::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnPlayRecordedFile return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_PLAYFILE_DONE == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnPlayRecordedFile);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

void UNotifyBase::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnApplyMessageKey return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_MESSAGE_KEY_APPLIED_SUCC == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnApplyMessageKey);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

void UNotifyBase::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnSpeechToText return code %d!"), *(this->GetName()), static_cast<int32>(code));

	/*if (gcloud_voice::GV_ON_STT_SUCC == code)
	{*/
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnSpeechToText);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	//}
}

void UNotifyBase::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnRecording"), *(this->GetName()));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnRecording);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnStreamSpeechToText return code %d!"), *(this->GetName()), static_cast<int32>(code));

	FEventCallback *TCallback = mapCallback.Find(FuncName::_OnStreamSpeechToText);
	if (nullptr != TCallback)
	{
		TCallback->ExecuteIfBound();
	}
}

void UNotifyBase::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnRoleChanged return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_ROLE_SUCC == code)
	{
		FEventCallback *TCallback = mapCallback.Find(FuncName::_OnRoleChanged);
		if (nullptr != TCallback)
		{
			TCallback->ExecuteIfBound();
		}
	}
}

UNotifyBase * UNotifyBase::GetNotifyInstance(TSubclassOf<UNotifyBase> NotifyClass)
{
	return NewObject<UNotifyBase>(NotifyClass->GetClass());
}

void UNotifyBase::SetEventForFunctionName(FuncName FunctionName, FEventCallback Delegate)
{
	if (mapCallback.Find(FunctionName) == NULL)
	{
		mapCallback.Add(FunctionName, Delegate);
		UE_LOG(TencentVoicePlugin, Display, TEXT("%s, %d delegate added!"), *(this->GetName()), static_cast<int32>(FunctionName));
	}
}

void UNotifyBase::RemoveEventForFunctionName(FuncName FunctionName)
{
	mapCallback.Remove(FunctionName);
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s remove event by %d!"), *(this->GetName()), static_cast<int32>(FunctionName));
}