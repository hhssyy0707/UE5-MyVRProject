// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCarActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyCarActor::AMyCarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetWorldScale3D(FVector(2,0.8f,1.0f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AMyCarActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCarActor::RotateCar(float Angle)
{
	//SetActorRotation(GetActorRotation() + FRotator(0, Angle, 0));
	SetActorRotation( FRotator(0, Angle, 0));
}

