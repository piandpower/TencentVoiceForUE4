// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class TencentVoiceForUnreal : ModuleRules
{
	public TencentVoiceForUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"TencentVoiceForUnreal/Public",
                Path.Combine(ThirdPartyPath,"include")
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"TencentVoiceForUnreal/Private",
				// ... add other private include paths required here ...
                Path.Combine(ThirdPartyPath,"include")
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
                "Projects"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        LoadThirdParty(Target);
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
    }

    private bool LoadThirdParty(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            isLibrarySupported = true;

            string LibPath = Path.Combine(ThirdPartyPath, "lib");
            string DllPath = Path.Combine(ThirdPartyPath, "dll");
            System.Console.WriteLine(Path.Combine(DllPath, "GCloudVoice.dll"));

            // Add Library Path 
            PublicLibraryPaths.Add(LibPath);

            //Add Static Libraries
            PublicAdditionalLibraries.Add("GCloudVoice.lib");

            //Add Dynamic Libraries
            PublicDelayLoadDLLs.Add("GCloudVoice.dll");

            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(DllPath, "GCloudVoice.dll")));
        }
        return isLibrarySupported;
    }
}
