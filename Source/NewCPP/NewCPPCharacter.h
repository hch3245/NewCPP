// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "MyAbilitySystemComponent.h"	// 어빌리티 시스템 컴포넌트
#include "MyAttributeSet.h"		// 속성 데이터 테이블

#include "NewCPPCharacter.generated.h"


class UMyAbilitySystemComponent;	// 클래스 전방선언
class UMyAttributeSet;

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ANewCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ANewCPPCharacter();
	
public:

	// 어빌리티 시스템 컴포넌트 추가
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASGamePlayAbility")
	class UMyAbilitySystemComponent* AbilitySystemComponent;
	// Gas 함수
	virtual class UMyAbilitySystemComponent* GetAblitySystemComponent() const;

	// 캐릭터 관련 정보 보관(HP,MP,Damage 그런거) 데이터 셋
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GASGamePlayAbility")
	const class UMyAttributeSet* AttributeSetVar;

	// EditAnywhere 에디터에서 초기에 캐릭터 스킬 변경 가능하도록
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GASGamePlayAbility")
	TArray<TSubclassOf<class UGameplayAbility>> InitialAbilities;

	// 초기 능력치 세팅, Maxhealth, MaxMana 처음에 세팅
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASGamePlayAbility")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

public: // 스킬 관련 함수
	
	// 스킬 어빌리티 하나 추가
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilitySkill")
	void InitializeAbility(
		TSubclassOf<UGameplayAbility> AbilityToGet,
		int32 AbilityLevel);
	
	// 스킬 어빌리티 여러개 추가
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilitySkill")
	void InitializeAbilityMulti(
		TArray<TSubclassOf<UGameplayAbility>> AbilityToAcquire,
		int32 AbilityLevel);

	// 플레이어가 해당 캐릭터 권한 얻었을 때
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override; // 온라인에서 캐릭터 상태 변경시


public: // 어빌리티 태그 시스템
	
	// 태그 여러 개 삭제 FGameplayTagContainer가 태그 여러개 담음
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityTag")
	void RemoveAbilityWithTags(FGameplayTagContainer TagContainer);

	// 태그 레벨 변경 LOL 스킬 레벨
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityTag")
	void ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 level);

	// 태그 중간취소
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityTag")
	void CancelAbilityWithTags(FGameplayTagContainer WithTag,
								FGameplayTagContainer WithOutTags);

	// 태그 추가
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityTag")
	void AddLooseGameplayTag(FGameplayTag TagToAdd);

	// 태그 하나 삭제
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityTag")
	void RemoveLooseGameplayTag(FGameplayTag TagToRemove);



public:	// 캐릭터 속성 관련

	UFUNCTION() // 체력 변경시 호출, C++로 구현 블루프린트도 부름
	virtual void OnHealthChangeNative(float Health, int32 StackCount);

	// 블프에서 이벤트 발생 시켜서 블루프린트에서 기능 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "GASGamePlayAbilityAttribute") // 체력
	void OnHealthChange(float Health, int32 StackCount);

	// 현재 체력을 블루프린트에서 바로 확인 s
	UFUNCTION(BlueprintPure, Category = "GASGamePlayAbilityAttribute")
	void HealthValues(float& Health, float& MaxHealth);

	// 블루프린트에서 호출 가능
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityAttribute")
	float GetHealth() const;
	
	// 블루프린트에서 호출 가능
	UFUNCTION(BlueprintCallable, Category = "GASGamePlayAbilityAttribute")
	float GetMaxHealth() const;


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:

	virtual void BeginPlay();

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

