// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "FPSscene.h"
#include "EngineUtils.h"
#include <string>
#include "JsonObjectConverter.h"



void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnableInput(this);

	InputComponent->BindAction("PrintMap", IE_Pressed, this, &AMyPlayerController::PrintMap);

}

void AMyPlayerController::PrintMap()
{
	UE_LOG(LogTemp, Warning, TEXT("->Launch"));
	//    TestWrite();
	//    return;

	UWorld* world = GetWorld();
	TActorIterator<AActor> Iterator(world, AActor::StaticClass());
	FILE * pFile = 0;
	pFile = fopen("C:\\Users\\haytamhuang\\Documents\\Unreal Projects\\a.txt", "w");

	FStage Stage;
	Stage.name = "stage1";

	for (; Iterator; ++Iterator)
	{
		AActor* Actor = Cast<AActor>(*Iterator);
		auto actor_name = Actor->GetFName().ToString();
		if (actor_name.Contains("wall") || actor_name.Contains("Box") || actor_name.Contains("Floor") || actor_name.Contains("Cube"))
		{
			FTransform trans = Actor->GetTransform();
			FVector scale = trans.GetScale3D();
			FVector pos = trans.GetLocation();
			FQuat rotation = trans.GetRotation();

			FBox bounding_box = Actor->CalculateComponentsBoundingBoxInLocalSpace(true);

			FBlock Person;
			Person.name = actor_name;
			Person.pos = pos;
			Person.rotation = rotation;
			Person.scale = scale;
			Person.extent = bounding_box.GetExtent();


			Stage.actors.Add(Person);

			TArray< FStringFormatArg > args;
			args.Add(FStringFormatArg(actor_name));
			args.Add(FStringFormatArg(scale.X));
			args.Add(FStringFormatArg(scale.Y));
			args.Add(FStringFormatArg(scale.Z));

			args.Add(FStringFormatArg(pos.X));
			args.Add(FStringFormatArg(pos.Y));
			args.Add(FStringFormatArg(pos.Z));

			args.Add(FStringFormatArg(bounding_box.GetExtent().X));
			args.Add(FStringFormatArg(bounding_box.GetExtent().Y));
			args.Add(FStringFormatArg(bounding_box.GetExtent().Z));

			args.Add(FStringFormatArg(bounding_box.GetSize().X));
			args.Add(FStringFormatArg(bounding_box.GetSize().Y));
			args.Add(FStringFormatArg(bounding_box.GetSize().Z));

			args.Add(FStringFormatArg(rotation.W));
			args.Add(FStringFormatArg(rotation.X));
			args.Add(FStringFormatArg(rotation.Y));
			args.Add(FStringFormatArg(rotation.Z));

			FString log_str = FString::Format(TEXT("Name = {0} scale=({1}, {2}, {3}), pos={{4}, {5}, {6}}, ext_bbox={{7}, {8}, {9}}, size_bbox={{10}, {11}, {12}}, quaternion={{13}, {14}, {15}, {16}}  "), args);
			GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Yellow, log_str);  //Print name of the Actor
	  //      std::string MyStdString = TCHAR_TO_ANSI(*log_str);
	  //      fwrite(MyStdString.c_str(), 1, MyStdString.length(), pFile);
	  //      fwrite("\n", 1, 1, pFile);
		}
	}

	FString Blah;
	FJsonObjectConverter::UStructToJsonObjectString(Stage, Blah);
	std::string MyStdString = TCHAR_TO_ANSI(*Blah);
	fwrite(MyStdString.c_str(), 1, MyStdString.length(), pFile);

	fclose(pFile);
	pFile = 0;


}
