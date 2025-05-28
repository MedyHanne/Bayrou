#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainWidget.h"
#include "Player_HUD.generated.h"


UCLASS()
class BAYROU_API APlayer_HUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<UMainWidget> mainWidgetRef;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess)) TObjectPtr<UMainWidget> mainWidget;

public:
	FORCEINLINE TObjectPtr<UMainWidget> GetMainWidget() const { return mainWidget; }

private:
	virtual void BeginPlay() override;
	
};
