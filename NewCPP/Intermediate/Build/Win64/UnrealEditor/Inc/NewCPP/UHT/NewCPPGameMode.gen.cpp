// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NewCPP/NewCPPGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNewCPPGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
NEWCPP_API UClass* Z_Construct_UClass_ANewCPPGameMode();
NEWCPP_API UClass* Z_Construct_UClass_ANewCPPGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_NewCPP();
// End Cross Module References

// Begin Class ANewCPPGameMode
void ANewCPPGameMode::StaticRegisterNativesANewCPPGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ANewCPPGameMode);
UClass* Z_Construct_UClass_ANewCPPGameMode_NoRegister()
{
	return ANewCPPGameMode::StaticClass();
}
struct Z_Construct_UClass_ANewCPPGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "NewCPPGameMode.h" },
		{ "ModuleRelativePath", "NewCPPGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANewCPPGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ANewCPPGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_NewCPP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ANewCPPGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ANewCPPGameMode_Statics::ClassParams = {
	&ANewCPPGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ANewCPPGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ANewCPPGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ANewCPPGameMode()
{
	if (!Z_Registration_Info_UClass_ANewCPPGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANewCPPGameMode.OuterSingleton, Z_Construct_UClass_ANewCPPGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ANewCPPGameMode.OuterSingleton;
}
template<> NEWCPP_API UClass* StaticClass<ANewCPPGameMode>()
{
	return ANewCPPGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ANewCPPGameMode);
ANewCPPGameMode::~ANewCPPGameMode() {}
// End Class ANewCPPGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_UEProjects_GitProject_NewCPP_NewCPP_Source_NewCPP_NewCPPGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANewCPPGameMode, ANewCPPGameMode::StaticClass, TEXT("ANewCPPGameMode"), &Z_Registration_Info_UClass_ANewCPPGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANewCPPGameMode), 384740251U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UEProjects_GitProject_NewCPP_NewCPP_Source_NewCPP_NewCPPGameMode_h_1731761731(TEXT("/Script/NewCPP"),
	Z_CompiledInDeferFile_FID_UEProjects_GitProject_NewCPP_NewCPP_Source_NewCPP_NewCPPGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UEProjects_GitProject_NewCPP_NewCPP_Source_NewCPP_NewCPPGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
