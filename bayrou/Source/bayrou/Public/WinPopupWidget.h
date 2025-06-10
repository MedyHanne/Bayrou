#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include "WinPopupWidget.generated.h"


UCLASS()
class BAYROU_API UWinPopupWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget)) TObjectPtr<UImage> winImage;

public:
	FORCEINLINE TObjectPtr<UImage> GetWinImage() { return winImage; }

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)void SetWinImage(UImage* _image);
	
};
