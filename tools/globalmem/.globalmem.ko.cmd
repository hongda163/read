cmd_/home/user1/tools/globalmem/globalmem.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/user1/tools/globalmem/globalmem.ko /home/user1/tools/globalmem/globalmem.o /home/user1/tools/globalmem/globalmem.mod.o ;  true
