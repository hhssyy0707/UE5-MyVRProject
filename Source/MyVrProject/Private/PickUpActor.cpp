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
	// ������ ���� �ڵ� �޽ÿ� �����ȴ�.
	boxComp->SetSimulatePhysics(false);

	if (attachmentRules == EAttachmentRule::KeepWorld)
	{
		FAttachmentTransformRules rules = FAttachmentTransformRules::KeepWorldTransform;
		// ��� ������ ������(���� ��ǥ ����) �����ϸ鼭 ���δ�.
		AttachToComponent(handMesh, rules);
	}
	// ������ ��ġ�� �̵��ؼ� ���δ�.
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

	// ������� ����� �ӵ��� ���ӵ��� �߰����ش�.
	if(deltaPosition.Size() > 0.05f)
	{
		boxComp->AddImpulse(deltaPosition * throwPower);
		boxComp->AddTorqueInRadians(deltaRotaion.GetRotationAxis() * rotPower);
	}
}

