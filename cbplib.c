#include <Python.h>
#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "tft.h"
#include "RAIO8870.h"
#include "bmp.h"

static PyObject *py_init(PyObject *self) {
	if (!bcm2835_init()) {
		return NULL;
	}

	TFT_init_board();
	TFT_hard_reset();
	RAIO_init();

	return Py_BuildValue("i", 1);
}

static PyObject *py_backlight(PyObject *self, PyObject *args) {
	
	uint8_t pwm;
	
	if (!PyArg_ParseTuple(args,"B", &pwm)){
		return NULL;
	}
	
	if (!bcm2835_init()) {
		return NULL;
	}

	RAIO_SetBacklightPWMValue(pwm);
	
	return Py_BuildValue("i", 1);
}

static PyObject *py_test(PyObject *self) {
	if (!bcm2835_init()) {
		return NULL;
	}

	// rectangle
	Draw_Square(0, 0, 319, 239);
	Text_Foreground_Color( COLOR_BLUE );
	RAIO_StartDrawing( SQUARE_FILL );

	return Py_BuildValue("i", 1);
}

static PyObject *py_clear(PyObject *self) {
	if (!bcm2835_init()) {
		return NULL;
	}

	// rectangle
	Draw_Square(0, 0, 319, 239);
	Text_Foreground_Color( COLOR_BLACK );
	RAIO_StartDrawing( SQUARE_FILL );

	return Py_BuildValue("i", 1);
}


static PyObject *py_image(PyObject *self, PyObject *args) {
	char *file_name;
	
	if (!PyArg_ParseTuple(args,"s", &file_name)){
		return NULL;
	}

	uint16_t picture[1][ PICTURE_PIXELS ];

	if (!bcm2835_init()) {
		return NULL;
	}

	Read_bmp2memory ( &file_name[0], &picture[0][ PICTURE_PIXELS-1 ] );
	RAIO_Write_Picture( &picture[0][0], PICTURE_PIXELS );
	return Py_BuildValue("i", 1);
}


static PyMethodDef tft_python_methods[] = {
	{"init", (PyCFunction)py_init, METH_NOARGS, NULL },
	{"backlight", (PyCFunction)py_backlight, METH_VARARGS, NULL },
	{"clear", (PyCFunction)py_clear, METH_NOARGS, NULL },
	{"test", (PyCFunction)py_test, METH_NOARGS, NULL },
	{"image", (PyCFunction)py_image, METH_VARARGS, NULL },
	{NULL, NULL, 0, NULL }
};

void initcbplib(void) {
	(void) Py_InitModule("cbplib", tft_python_methods);
}

