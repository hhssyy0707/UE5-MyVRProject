// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "WideMovieActor.h"

void UMovieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼을 클릭하는 이벤트틀
	Btn_back->OnClicked.AddDynamic(this, &UMovieWidget::Back10Seconds);
	Btn_stop->OnClicked.AddDynamic(this, &UMovieWidget::StopMovie);
	Btn_play->OnClicked.AddDynamic(this, &UMovieWidget::PlayMovie);
	Btn_forward->OnClicked.AddDynamic(this, &UMovieWidget::Forward10Seconds);
}

void UMovieWidget::Back10Seconds()
{
	if (MovieActor != nullptr) {
		MovieActor->Back();
}
}

void UMovieWidget::StopMovie()
{
	if (MovieActor != nullptr) {
		MovieActor->Stop();
	}

}

void UMovieWidget::PlayMovie()
{
	if (MovieActor != nullptr) {
		MovieActor->Play();
	}
}

void UMovieWidget::Forward10Seconds()
{
	if (MovieActor != nullptr) {
		MovieActor->Forward();
	}
}
