from distutils.core import setup, Extension

module1 = Extension('cbplib',
	libraries = ['bcm2835'],
	include_dirs = ['/usr/local/include', '/home/pi/cbplib'],
	library_dirs = ['/usr/local/lib'],
	sources = ['cbplib.c', 'tft.c', 'RAIO8870.c', 'bmp.c'])

setup(name='cbplib',
	version='1.0',
	description = 'C-Berry Lib for Python',
	author = 'pixelsetzer',
	ext_modules=[module1])
