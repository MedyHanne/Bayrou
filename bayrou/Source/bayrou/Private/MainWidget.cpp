#include "MainWidget.h"

#include "GameFramework/Character.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	playerRef = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

