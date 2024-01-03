// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereMovieActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MediaSoundComponent.h"
#include "MediaSource.h"
#include "MediaPlayer.h"


// Sets default values
ASphereMovieActor::ASphereMovieActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);
	RootComp->SetWorldScale3D(FVector(3.f));


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SoundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Sound Comp"));
	SoundComp->SetupAttachment(RootComp);

	if (MovieSource != nullptr) {
		SoundComp->SetMediaPlayer(MoviePlayer);
		//SoundComp->Activate(true);
		//SoundComp->SetVolumeMultiplier(2.f);
	}

}

// Called when the game starts or when spawned
void ASphereMovieActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (MoviePlayer != nullptr && MovieSource != nullptr) {
		MoviePlayer->OpenSource(MovieSource);
	}
}

// Called every frame
void ASphereMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

