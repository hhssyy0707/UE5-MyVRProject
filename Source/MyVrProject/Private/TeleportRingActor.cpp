// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportRingActor.h"
#include "NiagaraComponent.h"


ATeleportRingActor::ATeleportRingActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ring_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Ring Effect"));
	ring_FX->SetupAttachment(RootComponent);
}

void ATeleportRingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportRingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

