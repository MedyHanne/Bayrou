#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConfusiusRetreat.generated.h"

class ACharacter;
class USpotLightComponent;

UCLASS()
class BAYROU_API AConfusiusRetreat : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) FText name;
	UPROPERTY(EditAnywhere) FText description;
	UPROPERTY(EditAnywhere) float interactionDistance = 200.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)bool isPlayerInRange = false;
	
public:	
	AConfusiusRetreat();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	void Reward(ACharacter* _player);
	void Check();

};
