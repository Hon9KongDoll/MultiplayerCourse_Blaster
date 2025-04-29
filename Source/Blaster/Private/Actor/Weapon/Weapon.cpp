#include "Actor/Weapon/Weapon.h"

// Engine
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	// ���ö�������ײͨ������Ӧ��ʽ ���赲��ͨ���ϵ���������
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	// ���ö� ECC_Pawn ����Ӧ��ʽ �����Ը�ͨ���ϵ����壬��������ײ���ص�
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// ������ײ�Ŀ���״̬ ����ȫ��������ײ�������赲���ص���
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AreaSphere->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())  // GetLocalRole() == ENetRole::ROLE_Authority
	{
		// ������������ײ : ���ڲ�ѯ������ģ��
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// ������������ײͨ����Ӧ �����ͨ���ϵ� Pawn �ص�
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}