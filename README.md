# nt61: kernel update for windows 7 (nt 6.1) [work in progress]

### YOU MUST!!! USE "recoveryenabled=No" and "nointegritychecks=Yes" OPTION IN BCDEDIT! system recovery will mess up your kernel, and integrity checks will prevent patched winload from loading. so we disable them for this reason.

## how to patch winload.exe, winload.efi, ci.dll:
open the binary with ida pro, find every `mov whatever, 0xc0000428` and replace it with `mov whatever, 0x0` (replacing `whatever` with whatever operand the instruction is using)

`c0000428h` is the NTSTATUS value for invalid image hash, so we replace that with 0x0 so that it doesn't look for that value, thus disabling code integrity.

you must also use "update checksums" option in cff explorer after patching or windows will refuse to load it.

## winhttp

winhttp wrapper, to run elden ring game without any game mods (only needing dxvk for directx 12) source can be found in the winhttp folder. prebuilt binaries are available on my Windows 7 Development discord (for link, PM me on discord: dotexe1337)

## KernelBase
WIP kernelbase extension can be found in kernelbase folder, this is the first dll i am working on

WARNING: KernelBase CAN NOT import kernel32 or any dependant of kernel32!!! you will cause circular dependencies & crash the system

for future reference: kernelbase stuff will more than likely be moved into kernel32 as it is easier to work with that way (exports from just about any system dll can be moved into kernel32 pretty easily)
