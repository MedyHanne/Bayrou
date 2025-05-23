#include "SpiritualArtefact.h"
#include "SpiritualNode.h"
#include "GameFramework/Character.h"
#include "OurMacros.h"

ASpiritualArtefact::ASpiritualArtefact()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = mesh;
}

void ASpiritualArtefact::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpiritualArtefact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpiritualArtefact::AddNode(ASpiritualNode* _nodeToAdd)
{
	if (!_nodeToAdd || nodesToDestroy.Contains(_nodeToAdd))return;
	if (!CanAdd())return;
	nodesToDestroy.Add(_nodeToAdd);
}

void ASpiritualArtefact::RemoveDestroyedNode(ASpiritualNode* _nodeToAdd)
{
	if (!_nodeToAdd || !nodesToDestroy.Contains(_nodeToAdd))return;
	nodesToDestroy.Remove(_nodeToAdd);
	CheckRecover();
}

void ASpiritualArtefact::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor || !CanBeRecover())return;

	ACharacter* _player = Cast<ACharacter>(OtherActor);
	if (!_player)return;
	onOpenDoor.Broadcast();
	//Add skin to player

	Destroy();
}

void ASpiritualArtefact::CheckRecover()
{
	if (CanBeRecover())
	{
		PRINT_MSG("Can be recover !");
		onStopNS.Broadcast();
		mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

