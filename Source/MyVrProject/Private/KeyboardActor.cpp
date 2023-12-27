// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


AKeyboardActor::AKeyboardActor()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel3);
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(0.2f, 0.05f, 0.05f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
}

void AKeyboardActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Box Component에 충돌 이벤트 함수 바인딩하기
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKeyboardActor::OnHitKey);

	keyMat = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);
	meshComp->SetMaterial(0, keyMat);
}

void AKeyboardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 키보드에 충돌 시 실행될 함수
void AKeyboardActor::OnHitKey(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), keySound, GetActorLocation());

	keyMat->SetVectorParameterValue(FName("EmissiveColor"), FVector4(0.414330, 0.984375, 0.139687, 1.0));
	keyMat->SetScalarParameterValue(FName("Intensity"), 5.0f);

	FTimerHandle resetHandler;
	GetWorldTimerManager().ClearTimer(resetHandler);
	GetWorldTimerManager().SetTimer(resetHandler, this, &AKeyboardActor::ResetKeyColor, 0.5f, false);
}

void AKeyboardActor::ResetKeyColor()
{
	keyMat->SetVectorParameterValue(FName("EmissiveColor"), FVector4(1.0, 1.0, 1.0, 1.0));
	keyMat->SetScalarParameterValue(FName("Intensity"), 1.0f);
}

