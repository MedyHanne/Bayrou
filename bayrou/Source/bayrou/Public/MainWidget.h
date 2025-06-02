#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JadeChallengeWidget.h"
#include "WinPopupWidget.h"
#include "MainWidget.generated.h"

class ACharacter;

UCLASS()
class BAYROU_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<ACharacter> playerRef = nullptr;
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UJadeChallengeWidget> jadeChallengeWidget;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UWinPopupWidget> winPopupWidget;

public:
	FORCEINLINE TObjectPtr<UJadeChallengeWidget> GetJadeChallengeWidget() { return jadeChallengeWidget; }
	FORCEINLINE TObjectPtr<UWinPopupWidget> GetWinPopupWidget() { return winPopupWidget; }

protected:
	virtual void NativeConstruct() override;
	
};
