// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FightingGame : ModuleRules
{
	public FightingGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ "GameplayAbilities", 
		"GameplayTags", 
		"GameplayTasks" ,
		"Core",
		"CoreUObject",
		"Engine",
		"InputCore",
		"HeadMountedDisplay",
		"EnhancedInput",
        "NavigationSystem",
        "AIModule"
		});
        PublicIncludePaths.AddRange(new string[] { "FightingGame" });
    }
}
