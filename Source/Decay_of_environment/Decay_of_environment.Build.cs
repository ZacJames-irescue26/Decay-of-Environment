// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Decay_of_environment : ModuleRules
{
	public Decay_of_environment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "GameplayTasks", "Niagara", "UMG", "OnlineSubsystem", "OnlineSubsystemSteam", "Navmesh" });
    }
}
