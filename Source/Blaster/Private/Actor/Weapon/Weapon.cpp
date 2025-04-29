#include "Actor/Weapon/Weapon.h"

// Engine
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	// 设置对所有碰撞通道的响应方式 ：阻挡该通道上的其他物体
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	// 设置对 ECC_Pawn 的响应方式 ：忽略该通道上的物体，不发生碰撞或重叠
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// 设置碰撞的开启状态 ：完全不参与碰撞（不能阻挡或重叠）
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
		// 服务器开启碰撞 : 用于查询和物理模拟
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// 服务器设置碰撞通道响应 ：与该通道上的 Pawn 重叠
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}