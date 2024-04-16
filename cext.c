#include </usr/include/python3.10/Python.h>
#include <python3.10/ceval.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

long starting_value, elapsed_ticks;

static int _sleep(int milli)
{
    #ifdef _WIN32
    Sleep(milli);
    #else
    usleep(milli*1000);  /* sleep for 100 milliSeconds */
    #endif
    return 0;
}

static void _beat() {
    starting_value = (long)clock();
    int i;
    for (i = 0; i < 10; i++) {
        elapsed_ticks = clock() - starting_value; 
        printf("BEAT: %ld\n", elapsed_ticks);
        // printf("BEAT: %ld\n", difftime(time(NULL), *_start));
        _sleep(1000);
    }
}

static PyObject *method_get_elapsed(PyObject *self, PyObject *args) {
    return PyLong_FromLong(elapsed_ticks);
}

static PyObject *method_beat(PyObject *self, PyObject *args) {
    bool _blah;

    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "b", &_blah)) {
        return NULL;
    }
    if (_blah) {
        Py_BEGIN_ALLOW_THREADS;
        _beat();
        Py_END_ALLOW_THREADS;
    } else {
        _beat();
    }


    return PyLong_FromLong(0);
}


static PyMethodDef CextMethods[] = {
    {"beat", method_beat, METH_VARARGS, "Method will release its thread from the gil"},
    {"get_elapsed", method_get_elapsed, METH_VARARGS, "Get elapsed ticks"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef cextmodule = {
    PyModuleDef_HEAD_INIT,
    "cext",
    "Python interface for the fputs C library function",
    -1,
    CextMethods
};


PyMODINIT_FUNC PyInit_cext(void) {
    starting_value = 0;
    elapsed_ticks = 0;
    return PyModule_Create(&cextmodule);
}
