#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "SpiritualArtefact.generated.h"

class ASpiritualNode;

UCLASS()
class BAYROU_API ASpiritualArtefact : public AActor
{
	GENERATED_BODY()
protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopNS);
	UPROPERTY(BlueprintAssignable, BlueprintType) FOnStopNS onStopNS;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenDoor);
	UPROPERTY(BlueprintAssignable, BlueprintType) FOnOpenDoor onOpenDoor;
protected:
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<TObjectPtr<ASpiritualNode>> nodesToDestroy;
	UPROPERTY(EditAnywhere) int maxCount = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool canBeRecover;

	UPROPERTY(EditAnywhere) FString name;

	UPROPERTY(EditAnywhere) TObjectPtr<USphereComponent> interactionZone;
	UPROPERTY(EditAnywhere) float interactionDistance = 200.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)bool isPlayerInRange = false;

public:
	FORCEINLINE FOnStopNS& OnStopNS() { return onStopNS; }
	FORCEINLINE FOnOpenDoor& OnOpenDoor() { return onOpenDoor; }
	FORCEINLINE int Count() { return nodesToDestroy.Num(); }
	FORCEINLINE bool CanAdd() { return Count() <= maxCount; }
	FORCEINLINE bool CanBeRecover() { return canBeRecover = Count() == 0; }

public:
	ASpiritualArtefact();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	void AddNode(ASpiritualNode* _nodeToAdd);
	void RemoveDestroyedNode(ASpiritualNode* _nodeToAdd);
private:
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void CheckRecover();
	void Reward(ACharacter* _player);
	void Check();

};
