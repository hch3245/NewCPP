// Copyright Epic Games, Inc. All Rights Reserved.

#include "NewCPPCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ANewCPPCharacter

ANewCPPCharacter::ANewCPPCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// 어빌리티 시스템 컴포넌트 생성해서 추가
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	// 온라인 연동 사용 여부 true 온라인 하겠다.
	AbilitySystemComponent->SetIsReplicated(true);

	// 능력치 변동시 이벤트를 호출할지 여부
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


}

//////////////////////////////////////////////////////////////////////////
// Input

void ANewCPPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySystemComponent)) {
		// AblitySystemComponent안에 있는 데이터 에셋을 UmyAttributeSet타입으로 가져온다.
		// 데이터 에셋은 언리얼 에디터에서 우리가 만들어서 넣어줌
		AttributeSetVar = AbilitySystemComponent->GetSet<UMyAttributeSet>();
		if (AttributeSetVar != nullptr) {

			// HealthChangeDelegate에 바인딩
			const_cast<UMyAttributeSet*>(AttributeSetVar)->HealthChangeDelegate.AddDynamic(this,
				&ANewCPPCharacter::OnHealthChangeNative);

			InitializeAttribute();
			AddStartUpEffects();

		}
	}
	else {
		// 호출한 함수 이름으로 에러메시지 출력
		UE_LOG(LogTemp, Error, TEXT("%s()Missing AbilitySystemComponent"), *FString(__FUNCTION__));
	}
}

void ANewCPPCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ANewCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANewCPPCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANewCPPCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

UMyAbilitySystemComponent* ANewCPPCharacter::GetAblitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ANewCPPCharacter::InitializeAttribute()
{
	if (!IsValid(AbilitySystemComponent)) {
		return;
	}

	if (!IsValid(DefaultAttributes)) {
		// 호출한 함수 이름으로 에러메시지 출력
		UE_LOG(LogTemp, Error, TEXT("%s()Missing DefaultAttributes"), *FString(__FUNCTION__));
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();

	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(
		DefaultAttributes, 0, EffectContext);

	if (NewHandle.IsValid()) {
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*NewHandle.Data.Get(), AbilitySystemComponent);
	}


}

void ANewCPPCharacter::AddStartUpEffects()
{
	if (!IsValid(AbilitySystemComponent)) {
		return;
	}


	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();

	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartUpEffects) {

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(
			GameplayEffect, 0, EffectContext);

		if (NewHandle.IsValid()) {
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
				*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}

void ANewCPPCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{

	// 온라인일때 서버만 능력치 관리하므로 서버일 때만 추가
	if (HasAuthority()) {
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(AbilityToGet, AbilityLevel));
	}
	
}

void ANewCPPCharacter::InitializeAbilityMulti(TArray<TSubclassOf<UGameplayAbility>> AbilityToAcquire, int32 AbilityLevel)
{
	if (HasAuthority()) {
		// 배열로 초기화
		for (TSubclassOf<UGameplayAbility> AbilityItem : AbilityToAcquire) {
			InitializeAbility(AbilityItem, AbilityLevel);
		}
	}
}

void ANewCPPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (IsValid(AbilitySystemComponent)) {

		// 어빌리티 시스템에 시스템을 사용하는 액터를 전달해서
		// 어빌리티 시스템 컴포넌트에서 내 액터를 찾아올 수 있도록 전달
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		// 에디터에서 전달해준 스킬 어빌리티 레벨은 전부 1
		InitializeAbilityMulti(InitialAbilities, 1); 
	}

}

void ANewCPPCharacter::OnRep_PlayerState()
{
	if (IsValid(AbilitySystemComponent)) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ANewCPPCharacter::RemoveAbilityWithTags(FGameplayTagContainer TagContainer)
{
	// 가져올 태그 담을 임시 배열
	TArray<struct FGameplayAbilitySpec*> MatchingAbilities;

	// AbilitySystemComponent안에 있는 활성화 된 TagContainer이랑 동일한 애들 가져온다.
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags
	(TagContainer, MatchingAbilities, true);

	for (FGameplayAbilitySpec* spec : MatchingAbilities) {
		AbilitySystemComponent->ClearAbility(spec->Handle);
	}


}

void ANewCPPCharacter::ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 level)
{

	// 가져올 태그 담을 임시 배열
	TArray<struct FGameplayAbilitySpec*> MatchingAbilities;

	// AbilitySystemComponent안에 있는 활성화 된 TagContainer이랑 동일한 애들 가져온다.
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags
	(TagContainer, MatchingAbilities, true);

	for (FGameplayAbilitySpec* spec : MatchingAbilities) {
		
		// 레벨만 변경
		spec->Level = level;
	}
}

void ANewCPPCharacter::CancelAbilityWithTags(FGameplayTagContainer WithTag, FGameplayTagContainer WithOutTags)
{
	AbilitySystemComponent->CancelAbilities(&WithTag, &WithOutTags);
}

void ANewCPPCharacter::AddLooseGameplayTag(FGameplayTag TagToAdd)
{
	AbilitySystemComponent->AddLooseGameplayTag(TagToAdd);
	AbilitySystemComponent->SetTagMapCount(TagToAdd, 1);
}

void ANewCPPCharacter::RemoveLooseGameplayTag(FGameplayTag TagToRemove)
{
	AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
}

void ANewCPPCharacter::OnHealthChangeNative(float Health, int32 StackCount)
{
	// 블루프린트 함수 호출, 블루프린트에서 기능 구현
	OnHealthChange(Health, StackCount);
	if (Health <= 0) {
		Die();
	}
}

void ANewCPPCharacter::HealthValues(float& Health, float& MaxHealth)
{
	if (IsValid(AttributeSetVar)) {
		Health = AttributeSetVar->GetHealth();
		MaxHealth = 1000.f; // 아직 없어서 그냥 1000
	}
	
}

float ANewCPPCharacter::GetHealth() const
{
	if (IsValid(AttributeSetVar))
		return AttributeSetVar->GetHealth();
	else {
		UE_LOG(LogTemp, Error, TEXT("%s()Not Valid AttributeSetVar"), *FString(__FUNCTION__));
		return 100.f;	// 현재는 AttributeSetVar이 만들어지기 전에 불리면 100을 임의로 넣도록 처리
	}
}

float ANewCPPCharacter::GetMaxHealth() const
{
	return 100.0f; // Max 값 없어서 현재 100
}

void ANewCPPCharacter::Die()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	if (IsValid(AbilitySystemComponent)) {
		// 현재 실행중인 어빌리티 모두 취소
		AbilitySystemComponent->CancelAbilities();

		// Die 태그를 만들어서 붙이기
		FGameplayTag DieEffectTag = FGameplayTag::RequestGameplayTag(FName("Die"));


		FGameplayTagContainer gameplayTag{ DieEffectTag };

		// 내 어빌리티 중에 Die 태그가 붙은 어빌리티가 있으면 그걸 실행
		bool isSuccess = AbilitySystemComponent->TryActivateAbilitiesByTag(gameplayTag);

		if (!isSuccess) {
			
			// 태그만 넣어주기.
			AbilitySystemComponent->AddLooseGameplayTag(DieEffectTag);
			FinishDying();	// 블루프린트에 이벤트 전달
		}
	}
}

void ANewCPPCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ANewCPPCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
