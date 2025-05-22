#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetArrow.generated.h"

UCLASS()
class BAYROU_API ATargetArrow : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)	TObjectPtr<UStaticMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere) float rotationSpeed = 250.0f;
	UPROPERTY(EditAnywhere) float levitateSpeed = 250.0f;
	UPROPERTY(EditAnywhere) float levitateAmplitude = 250.0f;

	float runningTime = 0.0f;

public:
	ATargetArrow();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void Levitate(float _delta);
	void Rotate(float _delta);
public:
	void SetArrowVisibility(bool _isVisible);

};
