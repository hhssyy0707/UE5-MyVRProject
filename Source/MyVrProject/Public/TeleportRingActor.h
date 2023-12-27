// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportRingActor.generated.h"

UCLASS()
class MYVRPROJECT_API ATeleportRingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportRingActor();

	UPROPERTY(EditAnywhere, Category=MySettings)
	class UNiagaraComponent* ring_FX;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
