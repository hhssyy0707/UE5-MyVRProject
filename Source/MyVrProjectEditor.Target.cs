// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyVrProjectEditorTarget : TargetRules
{
	public MyVrProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "MyVrProject" } );
	}
}
