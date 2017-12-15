// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class TencentVoiceForUnreal : ModuleRules
{
    private string ModulePath
    {
        get { return Path.GetDirectoryName(ModuleDirectory); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "TencentVoiceForUnreal/ThirdParty")); }
    }

	public TencentVoiceForUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"TencentVoiceForUnreal/Public",
				// ... add public include paths required here ...
                Path.Combine(ThirdPartyPath,"include")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"TencentVoiceForUnreal/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib", "GCloudVoice.lib"));
        PublicDelayLoadDLLs.Add(Path.Combine(ThirdPartyPath, "lib", "GCloudVoice.dll"));

    }
}
