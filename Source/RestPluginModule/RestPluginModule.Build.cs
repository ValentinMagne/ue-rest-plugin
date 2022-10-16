using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class RestPluginModule : ModuleRules
	{
		public RestPluginModule(ReadOnlyTargetRules Target) : base(Target)
		{
            PublicIncludePaths.AddRange(
            new string[] {
            }
            );

			PublicDependencyModuleNames.AddRange(
			new string[] {
			    "Core",
                "CoreUObject",
				"Engine",
                "Http",
                "Json",
                "JsonUtilities",
                "Slate",
				"SlateCore"
			}
			);

            PrivateIncludePaths.AddRange(
            new string[] {
                "RestPlugin/Private"
            }
            );

            PublicIncludePathModuleNames.Add("RestPluginModule");
		}
	}
}
