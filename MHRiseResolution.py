from keystone import *
import struct

Height_dock = int(input("Write height of docked resolution you want to use:\n"))

if (Height_dock > 1080):
    print ("Height cannot be bigger than 1080!")
    exit()
    
if (Height_dock <= 0):
    print ("Height cannot be equal or lower than 0!")
    exit()

Height_handheld = int(input("Write height of handheld resolution you want to use:\n"))

if (Height_handheld > 720):
    print ("Height cannot be bigger than 720!")
    exit()
    
if (Height_handheld <= 0):
    print ("Height cannot be equal or lower than 0!")
    exit()

if (Height_handheld % 45 != 0):
    print ("Height for handheld must be dividable by 45!")
    exit()


Ratio_dock = Height_dock / 1080
Ratio_handheld = Height_handheld / 720
Ratio_dock_byted = bytearray(struct.pack("!f", Ratio_dock))
Ratio_handheld_byted = bytearray(struct.pack("!f", Ratio_handheld))

Instructions_dock = b"MOVK x9, #0x%x%x, lsl#32; MOVK x9, #0x%x%x, lsl#48" % (Ratio_dock_byted[2], Ratio_dock_byted[3], Ratio_dock_byted[0], Ratio_dock_byted[1])
Instructions_handheld = b"MOV x9, #0x%x%x0000" % (Ratio_handheld_byted[0], Ratio_handheld_byted[1])

ks = Ks(KS_ARCH_ARM64, KS_MODE_LITTLE_ENDIAN)
encoding_dock, count_dock = ks.asm(Instructions_dock)
encoding_handheld, count_handheld = ks.asm(Instructions_handheld)

file = open("0100B04011742000/exefs/subsdk9_unc", "rb")
temp = file.read()
file.close()
temp = temp.replace(b"\x09\xF0\xA7\xD2", bytes(encoding_handheld))
temp = temp.replace(b"\x09\x00\xC0\xF2\x09\xF0\xE7\xF2", bytes(encoding_dock))
file = open("0100B04011742000/exefs/subsdk9_unc", "wb")
file.write(temp)
file.close()
