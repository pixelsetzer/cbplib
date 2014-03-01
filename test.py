import cbplib
import sys

print cbplib.init()
print cbplib.clear()
print cbplib.backlight(70)

print cbplib.image("berry.bmp")

sys.exit()