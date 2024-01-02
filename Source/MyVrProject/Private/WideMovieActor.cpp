// Fill out your copyright notice in the Description page of Project Settings.


#include "WideMovieActor.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "MovieWidget.h"
#include "MediaPlayer.h"

//include "Runtime/MediaAssets/Public/MediaSource.h"

// Sets default values
AWideMovieActor::AWideMovieActor()
:
	RootComp(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"))),
	MovieWidget(CreateDefaultSubobject<UWidgetComponent>(TEXT("Movie Widget")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//MovieWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Movie Widget"));
	//MovieSource = CreateDefaultSubobject<UMediaSource>(TEXT("Movie Source"));
	//MoviePlayer = CreateDefaultSubobject<UMediaPlayer>(TEXT("Movie Player"));

	SetRootComponent(RootComp);
	MovieWidget->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AWideMovieActor::BeginPlay()
{
	Super::BeginPlay();

	if (MoviePlayer != nullptr) {
		// 미디어 소스를 미디어 플레이어에 넣는다.
		MoviePlayer->OpenSource(MovieSource);
	}
	Cast<UMovieWidget>(MovieWidget->GetWidget())->MovieActor = this;

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

// Called every frame
void AWideMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWideMovieActor::Back()
{
	if (MoviePlayer->IsPlaying() || MoviePlayer->IsPaused()) {
		if (MoviePlayer->GetTime().GetTotalSeconds() > 10) {
			FTimespan NewTime = MoviePlayer->GetTime() + FTimespan(0,0,10);
			MoviePlayer->Seek(NewTime);
		}
	}
}

void AWideMovieActor::Forward()
{
	if (MoviePlayer->IsPlaying() || MoviePlayer->IsPaused()) {
		FTimespan NewTime = MoviePlayer->GetTime() + FTimespan(0,0, 10);
		MoviePlayer->Seek(NewTime);
	}
}

void AWideMovieActor::Stop()
{
	if (MoviePlayer->IsPlaying()) {
		MoviePlayer->Close();
	}	
}

void AWideMovieActor::Play()
{
	if (MoviePlayer->IsClosed()) {
		MoviePlayer->OpenSource(MovieSource);
	}
	else if (MoviePlayer->IsPlaying()) {
		MoviePlayer->Pause();
	}
	else if (MoviePlayer->IsPaused()) {
		MoviePlayer->Play();
	}
}

