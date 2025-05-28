#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "JadeChallengeWidget.generated.h"


UCLASS()
class BAYROU_API UJadeChallengeWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UImage> timeLimitImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UImage> currentTimeImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> timeLimitText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> currentTimeText;
public:
	FORCEINLINE TObjectPtr<UImage> GetTimeLimitImage() { return timeLimitImage; }
	FORCEINLINE TObjectPtr<UImage> GetCurrentTimeImage() { return currentTimeImage; }
	FORCEINLINE TObjectPtr<UTextBlock> GetTimeLimitText() { return timeLimitText; }
	FORCEINLINE TObjectPtr<UTextBlock> GetCurrentTimeText() { return currentTimeText; }

protected:
	virtual void NativeConstruct() override;

public:
	void SetTimeLimitText(FText _text);
	void SetCurrentTimetText(FText _text);
	
};
