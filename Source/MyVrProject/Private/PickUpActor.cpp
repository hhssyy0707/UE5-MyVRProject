// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"


APickUpActor::APickUpActor()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionProfileName(FName("PickUpPreset"));
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);
	boxComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.3f));
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));
}

void APickUpActor::BeginPlay()
{
	Super::BeginPlay();

}

void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpActor::Grabbed(USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules)
{
	// 잡혔을 때의 핸드 메시에 부착된다.
	boxComp->SetSimulatePhysics(false);

	if (attachmentRules == EAttachmentRule::KeepWorld)
	{
		FAttachmentTransformRules rules = FAttachmentTransformRules::KeepWorldTransform;
		// 잡는 순간의 간격을(월드 좌표 기준) 유지하면서 붙인다.
		AttachToComponent(handMesh, rules);
	}
	// 지정된 위치로 이동해서 붙인다.
	else if (attachmentRules == EAttachmentRule::SnapToTarget)
	{
		FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		AttachToComponent(handMesh, rules, FName("GrabSocket"));
		SetActorRelativeLocation(locationOffset);
	}
}

void APickUpActor::Released(FVector deltaPosition, FQuat deltaRotaion)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	boxComp->SetSimulatePhysics(true);

	// 릴리즈될 당시의 속도와 각속도를 추가해준다.
	if(deltaPosition.Size() > 0.05f)
	{
		boxComp->AddImpulse(deltaPosition * throwPower);
		boxComp->AddTorqueInRadians(deltaRotaion.GetRotationAxis() * rotPower);
	}
}

