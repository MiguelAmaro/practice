#include "types.h"
#include "stdio.h"
#include "windows.h"

#define Assert(expression) if(!(expression)){__debugbreak();}
#define Max(a, b) (a>b?a:b)
#define Min(a, b) (a<b?a:b)

void MemCopy(u8 *Src, u64 SrcSize, u8 *Dest, u64 DestSize)
{
  u64 MaxSize = Min(SrcSize, DestSize);
  for(u64 At=0; At<MaxSize;At++) {Dest[At] = Src[At];}
  return;
}

void PrintProcAddress(u8 *Label, void* Address)
{
  printf("%s: %#llx\n", Label, (u64)Address);
  return;
}

void PrintOffset(u8 *Label, u8 *TargetLabel, u64 Offset)
{
  printf("%s To %s Offset: %#llx\n", Label, TargetLabel, Offset);
  return;
}

void PrintInstruction(u8 *Label, void* Address)
{
  // TODO(MIGUEL): Get instruction size some how...
  printf("%s Intsruction: %#llx\n", Label, *((u64 *)Address));
  return;
}

typedef u32 hooker(u32 a, u32 b, u32 c, u32 d);

u32 HookMe(u32 a, u32 b, u32 c, u32 d)
{
  printf("Not Hooked!");
  u32 Result = 0;
  u32 Padding = a+b;
  u32 More = Padding+c+d;
  Result = a+b*c+d;
  return Result + More* 0;
}

void Hooker(void)
{
  printf("You're Hooked!");
  
  return;
}

void MakeJumpInstruction(u8 *JmpMem, u32 Offset)
{
  u8  *JmpOpCode = JmpMem;
  u32 *JmpOffset = (u32 *)(JmpMem+1);
  *JmpOpCode = 0xe9;
  *JmpOffset = Offset;
  return;
}

u64 GetAddressOffset(void *AddressA, void *AddressB, u64 InstructionLength)
{
  u64 Result = 0;
  u64 a = Max((u64)AddressA, (u64)AddressB);
  u64 b = Min((u64)AddressA, (u64)AddressB);
  Result = (a - b) - InstructionLength;
  return Result;
}

void Hook(void *HookAddress, void *HookedAddress)
{
  u8 JmpMem[5] = {0};
  u64 ProcOffset =  GetAddressOffset(HookAddress, HookedAddress, 5);
  Assert(ProcOffset<UINT32_MAX);
  MakeJumpInstruction(JmpMem, (u32)ProcOffset);
  
  DWORD OldProtect = 0;
  VirtualProtect(HookedAddress, 5, PAGE_EXECUTE_READWRITE, &OldProtect);
  MemCopy(JmpMem, 5, (u8 *)HookedAddress, 5);
  VirtualProtect(HookedAddress, 5, OldProtect, &OldProtect);
  return;
}

u32 TrampJump(u32 ArgCount, u8 *Args[])
{
  u8 GString[256] = {0};
  PrintProcAddress("HookMe", HookMe);
  PrintProcAddress("Hooker", Hooker);
  
  MemCopy((u8 *)HookMe, sizeof(u64), GString, 256);
  PrintInstruction("HookMe ", HookMe);
  PrintInstruction("GString", GString);
  
  Hook(Hooker, HookMe);
  PrintInstruction("HookMe", HookMe);
  u32 Result = HookMe(0, 1, 2, 3);
  
  PrintInstruction("Hooker", Hooker);
  printf("Hook Result: %d\n", Result);
  return 0;
}

u32 main(u32 ArgCount, u8 *Args[])
{
  //~ TRAMPOLINE JUMP
  TrampJump(ArgCount, Args);
  
  PrintProcAddress("TrampJump", TrampJump);
  
  return 0;
}