// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovieWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYVRPROJECT_API UMovieWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
virtual void NativeConstruct() override;

public:
UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UImage* Screen;
	
UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	class UButton* Btn_back;
	
UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	UButton* Btn_stop;
	
UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	UButton* Btn_play;
	
UPROPERTY(EditAnywhere, Category = "MySettings", meta = (BindWidget))
	UButton* Btn_forward;

	class AWideMovieActor* MovieActor;

private:
UFUNCTION()
	void Back10Seconds();

UFUNCTION()
	void StopMovie();

UFUNCTION()
	void PlayMovie();

UFUNCTION()
	void Forward10Seconds();
};
