#include "Player_HUD.h"

void APlayer_HUD::BeginPlay()
{
	Super::BeginPlay();

	mainWidget = CreateWidget<UMainWidget>(GetWorld(), mainWidgetRef);
}

