.586
.model	flat
.code

MyTGalaxyNextDay PROTO C

MyTGalaxyNextDayAsm proc C
    push eax
    call MyTGalaxyNextDay
    add esp, 4
    ret
MyTGalaxyNextDayAsm endp
public MyTGalaxyNextDayAsm
END