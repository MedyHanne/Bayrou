#include "JadeChallengeWidget.h"

void UJadeChallengeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJadeChallengeWidget::SetTimeLimitText(FText _text)
{
	timeLimitText->SetText(_text);
}

void UJadeChallengeWidget::SetCurrentTimetText(FText _text)
{
	currentTimeText->SetText(_text);
}

