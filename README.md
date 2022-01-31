# nt61
kernel update for windows 7 (nt 6.1)

### YOU MUST!!! USE "recoveryenabled=No" and "nointegritychecks=Yes" OPTION IN BCDEDIT! system recovery will mess up your kernel, and integrity checks will prevent patched winload from loading. so we disable them for this reason.

## how to patch winload.exe, winload.efi, ci.dll:
open the binary with ida pro, find every `mov whatever, 0xc0000428` and replace it with `mov whatever, 0x0` (replacing `whatever` with whatever operand the instruction is using)
