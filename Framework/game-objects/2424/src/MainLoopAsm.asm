.586
.model	flat
.code

MyEntryPointMainLoop PROTO C
MainLoop PROTO C

MyEntryPointMainLoopAsm proc C
    call MainLoop
    call MyEntryPointMainLoop
    ret
MyEntryPointMainLoopAsm endp
public MyEntryPointMainLoopAsm
END