// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WideMovieActor.generated.h"

UCLASS()
class MYVRPROJECT_API AWideMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWideMovieActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
UPROPERTY(EditAnywhere, Category = "MySettings")
	USceneComponent* RootComp;
	
UPROPERTY(EditAnywhere, Category = "MySettings")
	class UWidgetComponent* MovieWidget;
	
UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaSource* MovieSource;
	
UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaPlayer* MoviePlayer;

	void Back();
	void Forward();
	void Stop();
	void Play();
};
