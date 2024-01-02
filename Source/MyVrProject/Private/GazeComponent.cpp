                               // Fill out your copyright notice in the Description page of Project Settings.


#include "GazeComponent.h"
#include "VR_Player.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UGazeComponent::UGazeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGazeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = GetOwner<AVR_Player>();
	BaseSize = Player->GazeMeshComp->GetComponentScale();
}


// Called every frame
void UGazeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//240102
	//����, �ü� ���⿡ ��ü�� �ִٸ� ������ �������� ũ�⸦ ������Ų��. (MaxSize������)
	//�׷��� �ʴٸ� ������ �������� ũ�⸦ ���ҽ�Ų��. (MinSize������),


	float Speed = 2.0f;

	if (GazeCheck())
	{
		currentSize+=DeltaTime;

		//���3. VInterpTo ���
		//Player->GazeMeshComp->SetRelativeScale3D(FMath::VInterpTo(Player->GazeMeshComp->GetRelativeScale3D(), maxSize , DeltaTime, Speed));
		//DrawDebugLine(GetWorld(), startVec, hitInfo.ImpactPoint, FColor::Red);
	}
	else
	{
		currentSize -= DeltaTime;
		
		//���3. VInterpTo ���
		//Player->GazeMeshComp->SetRelativeScale3D(FMath::VInterpTo(Player->GazeMeshComp->GetRelativeScale3D(), minSize, DeltaTime, Speed));
		//DrawDebugLine(GetWorld(), startVec, endVec, FColor::Red);
	}

	// ���1. Clamp ���
	//currentSize = FMath::Clamp(currentSize, 0.1f, 1.0f);
	//Player->GazeMeshComp->SetWorldScale3D(BaseSize * currentSize);

	// ���2. Lerp ���
	currentSize = FMath::Clamp(currentSize, 0.1f, 1.0f);
	FVector NewSize = FMath::Lerp(minSize,maxSize,currentSize);
	Player->GazeMeshComp->SetWorldScale3D(BaseSize.X * NewSize);

}

bool UGazeComponent::GazeCheck()
{
	FHitResult hitInfo;
	FVector startVec = Player->cameraComp->GetComponentLocation();
	FVector endVec = startVec + Player->cameraComp->GetForwardVector() * 2500;
	FCollisionQueryParams params;
	params.AddIgnoredActor(Player);
	
	bool bIsCollide = GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endVec, ECC_Visibility, params);


	return bIsCollide;
}

