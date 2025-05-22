#pragma once

#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "CoreMinimal.h"

#define PRINT_MSG(Message) \
    if (GetWorld()) UKismetSystemLibrary::PrintString(GetWorld(), Message, true, true, FLinearColor::White, 2.0f)

#define PRINT_MSG_COLOR(Message, Color) \
    if (GetWorld()) UKismetSystemLibrary::PrintString(GetWorld(), Message, true, true, Color, 2.0f)

#define PRINT_MSG_TIME(Message, Duration) \
    if (GetWorld()) UKismetSystemLibrary::PrintString(GetWorld(), Message, true, true, FLinearColor::Red, Duration)

#define PRINT_MSG_ALL(Message, Duration, Color) \
    if (GetWorld()) UKismetSystemLibrary::PrintString(GetWorld(), Message, true, true, Color, Duration)


