#include "RestLibrary.h"

DEFINE_LOG_CATEGORY(RestLibrary);

URestLibrary::URestLibrary(const FObjectInitializer& init)
	:Super(init)
{

}

float URestLibrary::RestPluginSampleFunction(float Param)
{
	return Param * 100;
}

void URestLibrary::ProcessRequestGet(FString URL, FString botmanSession)
{
	UE_LOG(RestLibrary, Log, TEXT("Process GET request for : %s"), *URL);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URestLibrary::OnResponseReceived);

	HttpRequest->SetURL(URL);

	HttpRequest->SetVerb("Get");

	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader(TEXT("initialBotId"), "DJINGO_ACCUEIL");
	HttpRequest->SetHeader(TEXT("Content-Type"), "application/json");
	HttpRequest->SetHeader(TEXT("x-orange-callerid"), "fwc");
	HttpRequest->SetHeader(TEXT("botmanSession"), botmanSession);

	HttpRequest->ProcessRequest();
}

void URestLibrary::ProcessRequestPost(FString URL, FString body, FString botmanSession)
{
	UE_LOG(RestLibrary, Log, TEXT("Process POST request for : %s"), *URL);
	UE_LOG(RestLibrary, Log, TEXT("Process POST request with body : %s"), *body);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URestLibrary::OnResponseReceived);

	HttpRequest->SetURL(URL);

	HttpRequest->SetVerb("Post");

	HttpRequest->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	HttpRequest->SetHeader(TEXT("initialBotId"), "DJINGO_ACCUEIL");
	HttpRequest->SetHeader(TEXT("Content-Type"), "application/json");

    HttpRequest->SetHeader(TEXT("botmanSession"), botmanSession);
    HttpRequest->SetHeader(TEXT("messageType"), "user_message");
    HttpRequest->SetHeader(TEXT("x-orange-callerid"), "fwc");

	HttpRequest->SetContentAsString(body);

	HttpRequest->ProcessRequest();
}

void URestLibrary::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(RestLibrary, Log, TEXT("GET RESPONSE : %s"), *Response->GetContentAsString());
		GLog->Log(TEXT("END REQUEST"));
		FString JSONString = Response->GetContentAsString();
		onRequestComplete.Broadcast(JSONString);
	}
}
