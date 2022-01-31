# nt61
kernel update for windows 7 (nt 6.1)

+++ YOU MUST!!! USE "norecovery" OPTION IN EASYBCD OR ELSE WINDOWS WILL MESS UP YOUR KERNEL! YOU HAVE BEEN WARNED. +++

# how to patch winload.exe, winload.efi, ci.dll:
open the binary with ida pro, find every `mov whatever, 0xc0000428` and replace it with `mov whatever, 0x0` (replacing `whatever` with whatever operand the instruction is using)
