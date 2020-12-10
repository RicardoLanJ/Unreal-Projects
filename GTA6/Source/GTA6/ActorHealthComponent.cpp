// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorHealthComponent.h"

#include "GTA6Character.h"


// Sets default values for this component's properties
UActorHealthComponent::UActorHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);

	DefaultHealth = 1;
	Health = DefaultHealth;
	// ...
}

void UActorHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UActorHealthComponent, Health);
}

// Called when the game starts
void UActorHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UActorHealthComponent::TakeDamage_OnServer);
	}

}

void UActorHealthComponent::TakeDamage_OnServer(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigateBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Take Damage"));
	if (Damage < 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if (Health == 0)
	{
		AGTA6Character* MyOwner = Cast<AGTA6Character>(GetOwner());
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("I am dead!"));
		MyOwner->Dead_OnServer(InstigateBy, DamageCauser);
	}
}

// Called every frame
//void UActorHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

