#include "JadeChallengeWidget.h"

void UJadeChallengeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJadeChallengeWidget::SetTimeLimitText(FString _text)
{
	timeLimitText->SetText(FText::FromString(_text));
}

void UJadeChallengeWidget::SetCurrentTimetText(FString _text)
{
	currentTimeText->SetText(FText::FromString(_text));
}

