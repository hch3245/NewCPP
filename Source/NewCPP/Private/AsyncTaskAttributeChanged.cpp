// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskAttributeChanged.h"

UAsyncTaskAttributeChanged* UAsyncTaskAttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
    // Static �Լ��� ȣ�� �� UAsyncTaskAttributeChanged������ ����
    UAsyncTaskAttributeChanged* WaitforAttributeChangeTask = NewObject<UAsyncTaskAttributeChanged>();

    // �������Ʈ���� ���� ���� ����
    WaitforAttributeChangeTask->ASC = AbilitySystemComponent;
    WaitforAttributeChangeTask->AttributeToListenFor = Attribute;

    // �Ķ���� ���� �̻��� ���
    if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid()) {
        
        // ������ ������Ʈ �ٽ� �����.
        WaitforAttributeChangeTask->RemoveFromRoot();
        return nullptr;
    }

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
    (Attribute).AddUObject(WaitforAttributeChangeTask, &UAsyncTaskAttributeChanged::AttributeChanged);

    return WaitforAttributeChangeTask;
}

UAsyncTaskAttributeChanged* UAsyncTaskAttributeChanged::ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
    // Static �Լ��� ȣ�� �� UAsyncTaskAttributeChanged������ ����
    UAsyncTaskAttributeChanged* WaitforAttributeChangeTask = NewObject<UAsyncTaskAttributeChanged>();

    // �������Ʈ���� ���� ���� ����
    WaitforAttributeChangeTask->ASC = AbilitySystemComponent;
    WaitforAttributeChangeTask->AttributesToListenFor = Attributes;

    // �Ķ���� ���� �̻��� ���
    if (!IsValid(AbilitySystemComponent) || !(Attributes.Num() < 1)) {

        // ������ ������Ʈ �ٽ� �����.
        WaitforAttributeChangeTask->RemoveFromRoot();
        return nullptr;
    }

    for (FGameplayAttribute Attribute : Attributes) {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
        (Attribute).AddUObject(WaitforAttributeChangeTask, 
            &UAsyncTaskAttributeChanged::AttributeChanged);
    }
    

    return nullptr;
}

void UAsyncTaskAttributeChanged::EndTask()
{
    if (IsValid(ASC)) {
        // �ȿ� �ִ°� ��������Ʈ Ȯ���ؼ� �� �����
        ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

        for (FGameplayAttribute Attribute : AttributesToListenFor) {
            ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
        }
    }

    SetReadyToDestroy(); //�׽�ũ ����
    MarkAsGarbage(); // GC���� �ش� Ŭ���� ���� ��û
}

void UAsyncTaskAttributeChanged::AttributeChanged(const FOnAttributeChangeData& Data)
{
    // ����Ȱ� �Լ� ����, �Ӽ�, ���ο� ������, ���� ������
    OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
